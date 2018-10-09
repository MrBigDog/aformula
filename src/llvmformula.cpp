/*
  Copyright (C) 2010-2011  Charles Pence <charles@charlespence.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/// @file llvmformula.cpp
/// @brief Implementation of the @c LLVMFormula class.

#include <aformula.h>
#include <boost/thread/tss.hpp>

#include "llvmformula.h"
#include "parsetree.h"

// LLVM imports its config.h into the global namespace, which means we have to do this
// (naughty LLVM!)
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Transforms/Scalar.h>

// For this file, I want to import this namespace
using namespace llvm;

namespace AFormula
{

namespace Private
{
extern boost::thread_specific_ptr<std::string> errorMessage;



LLVMFormula::LLVMFormula ()
{
	// We need to initialize the native target info, once.
	static bool initializeNative = false;
	if (!initializeNative)
	{
		InitializeNativeTarget ();
		initializeNative = true;
	}

	// Build a module and a JIT engine
	module = llvm::make_unique<Module>("AFormula JIT", globalContext);

	// The Engine is going to take control of this module,
	// don't delete them later.
	std::string errorString;
	engine = EngineBuilder (std::move(module)).setErrorStr (&errorString).create ();
	if (!engine)
	{
		// We won't let you call buildFunction if you catch this error
		errorMessage.reset (new std::string ("LLVM Error: " + errorString));
		return;
	}

	// Create an IRBuilder
	builder = new IRBuilder<> (globalContext);

	// Build an optimizer.  We're going to get default optimization settings
    // in the same way that LLVM does.
	FPM = new legacy::FunctionPassManager (module.get());

	FPM->add (createVerifierPass());

    PassManagerBuilder builder;
    builder.OptLevel = 3;
    builder.populateFunctionPassManager (*FPM);

	FPM->doInitialization ();
}

LLVMFormula::~LLVMFormula ()
{
	delete FPM;
	delete builder;
	delete engine;
}


bool LLVMFormula::buildFunction ()
{
	if (!engine)
		return false;

	// First, build a prototype for the nullary function we're about to define.
	FunctionType *FT = FunctionType::get (Type::getDoubleTy (globalContext), false);

	// Make a function
	Function *F = Function::Create (FT, Function::ExternalLinkage, "", module.get());

	// Make a basic block to start insertion into
	BasicBlock *BB = BasicBlock::Create (globalContext, "entry", F);
	builder->SetInsertPoint (BB);

	// And spit the body into it
	Value *val = (Value *)parseTree->generate (this);
	if (val == NULL)
	{
		// Clean up and bail
		F->eraseFromParent ();
		return false;
	}

	// Create a return statement, and check that the function makes sense
	builder->CreateRet (val);

	// Optimize and verify
	FPM->run (*F);

	void *fptr = engine->getPointerToFunction (F);
	func = (FunctionPointer)(intptr_t)fptr;

	return true;
}


void *LLVMFormula::emit (NumberExprAST *expr)
{
	return ConstantFP::get (globalContext, APFloat (expr->val));
}

Constant *LLVMFormula::getGlobalVariableFor (double *ptr)
{
	// Thanks to the unladen-swallow project for this snippet, which was almost
	// impossible to figure out from the LLVM docs!

	// See if the JIT already knows about this global
	GlobalVariable *result = const_cast<GlobalVariable *>(
		cast_or_null<GlobalVariable>(
			engine->getGlobalValueAtAddress (ptr)));
	if (result && result->hasInitializer ())
		return result;

	Constant *initializer = ConstantFP::get (Type::getDoubleTy (globalContext), *ptr);
	if (result == NULL)
	{
		// Make a global variable
		result = new GlobalVariable (*module, initializer->getType (),
		                             false, GlobalVariable::InternalLinkage,
		                             NULL, "");

		// Link the global variable to the right address
		engine->addGlobalMapping (result, ptr);
	}
	assert (!result->hasInitializer ());

	// Add the initial value
	result->setInitializer (initializer);

	return result;
}

void *LLVMFormula::emit (VariableExprAST *expr)
{
	// This is just "dereference expr->pointer"
	return builder->CreateLoad (getGlobalVariableFor (expr->pointer));
}

void *LLVMFormula::emit (UnaryMinusExprAST *expr)
{
	// Get a constant -1
	Value *minusOne = ConstantFP::get (globalContext, APFloat (-1.0));

	// Emit a multiply
	Value *C = (Value *)expr->child->generate (this);
	if (C == NULL) return NULL;

	return builder->CreateFMul (minusOne, C, "mulnegtmp");
}

void *LLVMFormula::emit (BinaryExprAST *expr)
{
	if (expr->op == "=")
	{
		// The assign function has to be dealt with specially, we *do not*
		// want to emit the LHS code (the load-from-memory instruction)!
		VariableExprAST *var = dynamic_cast<VariableExprAST *>(expr->LHS);
		if (!var) return NULL;

		Value *val = (Value *)expr->RHS->generate (this);
		if (!val) return NULL;

		// Emit a store-to-pointer instruction
		builder->CreateStore (val, getGlobalVariableFor (var->pointer), "storetmp");
		return val;
	}

	// The rest of the operators function normally
	Value *L = (Value *)expr->LHS->generate (this);
	Value *R = (Value *)expr->RHS->generate (this);
	if (L == NULL || R == NULL) return NULL;

	if (expr->op == "<=")
	{
		L = builder->CreateFCmpULE (L, R, "letmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == ">=")
	{
		L = builder->CreateFCmpUGE (L, R, "getmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == "!=")
	{
		L = builder->CreateFCmpUNE (L, R, "neqtmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == "==")
	{
		L = builder->CreateFCmpUEQ (L, R, "eqtmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == "<")
	{
		L = builder->CreateFCmpULT (L, R, "lttmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == ">")
	{
		L = builder->CreateFCmpUGT (L, R, "gttmp");
		return builder->CreateUIToFP (L, Type::getDoubleTy (globalContext),
		                              "booltmp");
	}
	else if (expr->op == "+")
		return builder->CreateFAdd (L, R, "addtmp");
	else if (expr->op == "-")
		return builder->CreateFSub (L, R, "subtmp");
	else if (expr->op == "*")
		return builder->CreateFMul (L, R, "multmp");
	else if (expr->op == "/")
		return builder->CreateFDiv (L, R, "divtmp");
	else if (expr->op == "^")
	{
		// The floating-point intrinsics are overloaded for multiple types
		Type *types[1] = { Type::getDoubleTy (globalContext) };
        ArrayRef<Type *> type_array(types, 1);

		Value *func = Intrinsic::getDeclaration (module.get(), Intrinsic::pow, type_array);
		return builder->CreateCall (func, {L, R}, "pow");
	}
	else
		return NULL;
}

void *LLVMFormula::emit (CallExprAST *expr)
{
	// Deal with the if-instruction first, specially
	if (expr->function == "if")
	{
		Value *cond = (Value *)expr->args[0]->generate (this);
		Value *t = (Value *)expr->args[1]->generate (this);
		Value *f = (Value *)expr->args[2]->generate (this);
		if (cond == NULL || t == NULL || f == NULL) return NULL;

		Value *one = ConstantFP::get (globalContext, APFloat (1.0));
		Value *cmp = builder->CreateFCmpOEQ (cond, one, "ifcmptmp");

		return builder->CreateSelect (cmp, t, f, "ifelsetmp");
	}

	// Sign isn't a standard-library function, implement it with a compare
	if (expr->function == "sign")
	{
		Value *v = (Value *)expr->args[0]->generate (this);
		if (!v) return NULL;

		Value *zero = ConstantFP::get (globalContext, APFloat (0.0));
		Value *one = ConstantFP::get (globalContext, APFloat (1.0));
		Value *none = ConstantFP::get (globalContext, APFloat (-1.0));

		Value *cmpgzero = builder->CreateFCmpOGT (v, zero, "sgncmpgzero");
		Value *cmplzero = builder->CreateFCmpOLT (v, zero, "sgncmplzero");

		Value *fselect = builder->CreateSelect (cmplzero, none, zero, "sgnsellzero");
		return builder->CreateSelect (cmpgzero, one, fselect, "sgnselgzero");
	}

	//
	// Map our function names to standard libm names
	//

	// If we're calling "log", we want "log10"
	if (expr->function == "log")
		expr->function = "log10";
	// If we're calling "ln", we want "log"
	if (expr->function == "ln")
		expr->function = "log";
	// If we're calling "abs", we want "fabs"
	if (expr->function == "abs")
		expr->function = "fabs";

	// The following are available as LLVM intrinsics, and we should emit them
	// specially without calling out to libm:
	Intrinsic::ID intrinsicID = Intrinsic::not_intrinsic;

	if (expr->function == "cos")
		intrinsicID = Intrinsic::cos;
	else if (expr->function == "exp")
		intrinsicID = Intrinsic::exp;
	else if (expr->function == "log")
		intrinsicID = Intrinsic::log;
	else if (expr->function == "log10")
		intrinsicID = Intrinsic::log10;
	else if (expr->function == "sin")
		intrinsicID = Intrinsic::sin;
	else if (expr->function == "sqrt")
		intrinsicID = Intrinsic::sqrt;

	if (intrinsicID != Intrinsic::not_intrinsic)
	{
		// Most of the floating-point intrinsics are overloaded for multiple types
		Type *types[1] = { Type::getDoubleTy (globalContext) };
        ArrayRef<Type *> type_array(types, 1);

		Value *arg = (Value *)expr->args[0]->generate (this);
		if (!arg) return NULL;

		Value *func = Intrinsic::getDeclaration (module.get(), intrinsicID, type_array);
		return builder->CreateCall (func, arg, expr->function);
	}

	// The rest of these are calls to stdlib floating point math
	// functions.

	// atan2 is special, because it has two arguments
	if (expr->function == "atan2")
	{
        Value *arg1 = (Value *)expr->args[0]->generate (this);
        Value *arg2 = (Value *)expr->args[1]->generate (this);
        if (!arg1 || !arg2) return NULL;

        Module *M = builder->GetInsertBlock ()->getParent ()->getParent ();
        Value *Callee = M->getOrInsertFunction (expr->function,
                                                Type::getDoubleTy (globalContext),
    	                                        Type::getDoubleTy (globalContext),
    	                                        Type::getDoubleTy (globalContext));
        return builder->CreateCall (Callee, {arg1, arg2}, expr->function);
	}
	else
	{
    	// Emit a call to function (arg)
    	Value *arg = (Value *)expr->args[0]->generate (this);
    	if (!arg) return NULL;

    	Module *M = builder->GetInsertBlock ()->getParent ()->getParent ();
    	Value *Callee = M->getOrInsertFunction (expr->function,
    	                                        Type::getDoubleTy (globalContext),
    	                                        Type::getDoubleTy (globalContext));
    	return builder->CreateCall (Callee, arg, expr->function);
    }
}


};
};

