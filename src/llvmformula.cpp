/*
  Copyright (C) 2010  Charles Pence <charles@charlespence.net>
  
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
#include <aformula.h>
#include "llvmformula.h"
#include "parsetree.h"

#include <llvm/GlobalVariable.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Function.h>

// For this file, I want to import this namespace
using namespace llvm;

namespace AFormula
{

namespace Private
{

LLVMFormula::LLVMFormula () : builder (getGlobalContext ())
{
}


bool LLVMFormula::buildFunction ()
{
	// First, build a prototype for the nullary function we're about to define.
	// FIXME: For some reason that I don't understand, "using namespace llvm" doesn't
	// import FunctionType?
	llvm::FunctionType *FT = llvm::FunctionType::get (Type::getDoubleTy (getGlobalContext ()), false);

	// Make a function
	Function *F = Function::Create (FT, Function::ExternalLinkage, "", theModule);

	// Make a basic block to start insertion into
	BasicBlock *BB = BasicBlock::Create (getGlobalContext (), "entry", F);
	builder.SetInsertPoint (BB);

	// And spit the body into it
	Value *val = parseTree->generate (this);
	if (val == NULL)
	{
		// Clean up and bail
		F->eraseFromParent ();
		return false;
	}

	// Create a return statement, and check that the function makes sense
	builder.CreateRet (val);
	verifyFunction (*F);

	// DEBUG: PRINT GENERATED CODE
	theModule->dump ();
			
	return false;
}


Value *LLVMFormula::emit (NumberExprAST<Value *> *expr)
{
	return ConstantFP::get (getGlobalContext (), APFloat (expr->val));
}

Value *LLVMFormula::emit (VariableExprAST<Value *> *expr)
{
	// Set the intial value to the correct pointer
	Type *pointerToDoubleType = 
		PointerType::getUnqual (Type::getDoubleTy (getGlobalContext ()));
	Constant *initialValue =
		ConstantInt::get (pointerToDoubleType, (uint64_t)expr->pointer);
	
	// Make a global variable of that type with that value
	GlobalVariable *var = new GlobalVariable (getGlobalContext (),
	                                          pointerToDoubleType, false,
	                                          GlobalVariable::InternalLinkage,
	                                          initialValue);
	
	// Now, we need a dereference-this-pointer instruction
	return builder.CreateLoad (var);
}

Value *LLVMFormula::emit (UnaryMinusExprAST<Value *> *expr)
{
	// Get a constant -1
	Value *minusOne = ConstantFP::get (getGlobalContext (), APFloat (-1.0));

	// Emit a multiply
	Value *C = expr->child->generate (this);
	if (C == NULL) return NULL;
	
	return builder.CreateFMul (minusOne, C, "mulnegtmp");
}

Value *LLVMFormula::emit (BinaryExprAST<Value *> *expr)
{
	if (expr->op == "=")
	{
		// The assign function has to be dealt with specially, we *do not*
		// want to emit the LHS code (the load-from-memory instruction)!
		VariableExprAST<Value *> *var = dynamic_cast<VariableExprAST<Value *> *>(expr->LHS);
		if (!var) return NULL;
				
		Value *val = expr->RHS->generate (this);
		if (!val) return NULL;
		
		// Set the intial value to the correct pointer
		Type *pointerToDoubleType = 
			PointerType::getUnqual (Type::getDoubleTy (getGlobalContext ()));
		Constant *initialValue =
			ConstantInt::get (pointerToDoubleType, (uint64_t)var->pointer);
		
		// Make a global variable of that type with that value
		GlobalVariable *global = new GlobalVariable (getGlobalContext (),
		                                             pointerToDoubleType, false,
		                                             GlobalVariable::InternalLinkage,
		                                             initialValue);

		// Emit a store-to-pointer instruction
		return builder.CreateStore (val, global, "storetmp");
	}

	// The rest of the operators function normally
	Value *L = expr->LHS->generate (this);
	Value *R = expr->RHS->generate (this);
	if (L == NULL || R == NULL) return NULL;

	if (expr->op == "<=")
	{
		L = builder.CreateFCmpULE (L, R, "letmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == ">=")
	{
		L = builder.CreateFCmpUGE (L, R, "getmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == "!=")
	{
		L = builder.CreateFCmpUNE (L, R, "neqtmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == "==")
	{
		L = builder.CreateFCmpUEQ (L, R, "eqtmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == "<")
	{
		L = builder.CreateFCmpULT (L, R, "lttmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == ">")
	{
		L = builder.CreateFCmpUGT (L, R, "gttmp");
		return builder.CreateUIToFP (L, Type::getDoubleTy (getGlobalContext ()),
		                             "booltmp");
	}
	else if (expr->op == "+")
		return builder.CreateFAdd (L, R, "addtmp");
	else if (expr->op == "-")
		return builder.CreateFSub (L, R, "subtmp");
	else if (expr->op == "*")
		return builder.CreateFMul (L, R, "multmp");
	else if (expr->op == "/")
		return builder.CreateFDiv (L, R, "divtmp");
	else if (expr->op == "^")
	{
		// Call pow (L, R)
		Module *M = builder.GetInsertBlock ()->getParent ()->getParent ();
		Value *Callee = M->getOrInsertFunction ("pow",
		                                        Type::getDoubleTy (getGlobalContext ()),
		                                        Type::getDoubleTy (getGlobalContext ()),
		                                        Type::getDoubleTy (getGlobalContext ()),
		                                        NULL);
		CallInst *CI = builder.CreateCall2 (Callee, L, R, "pow");
		if (const Function *F = dyn_cast<Function>(Callee->stripPointerCasts ()))
			CI->setCallingConv (F->getCallingConv ());

		return CI;
	}
	else
		return NULL;
}

Value *LLVMFormula::emit (CallExprAST<Value *> *expr)
{
	// Deal with the if-instruction first, specially
	if (expr->function == "if")
	{
		Value *cond = expr->args[0]->generate (this);
		Value *t = expr->args[1]->generate (this);
		Value *f = expr->args[2]->generate (this);
		if (cond == NULL || t == NULL || f == NULL) return NULL;
		
		Value *one = ConstantFP::get (getGlobalContext (), APFloat (1.0));
		Value *cmp = builder.CreateFCmpOEQ (cond, one, "ifcmptmp");

		return builder.CreateSelect (cmp, t, f, "ifelsetmp");
	}

	// Sign isn't a standard-library function, implement it with a compare
	if (expr->function == "sign")
	{
		Value *v = expr->args[0]->generate (this);
		if (!v) return NULL;
		
		Value *zero = ConstantFP::get (getGlobalContext (), APFloat (0.0));
		Value *one = ConstantFP::get (getGlobalContext (), APFloat (1.0));
		Value *none = ConstantFP::get (getGlobalContext (), APFloat (-1.0));

		Value *cmpgzero = builder.CreateFCmpOGT (v, zero, "sgncmpgzero");
		Value *cmplzero = builder.CreateFCmpOLT (v, zero, "sgncmplzero");

		Value *fselect = builder.CreateSelect (cmplzero, none, zero, "sgnsellzero");
		return builder.CreateSelect (cmpgzero, one, fselect, "sgnselgzero");
	}
	
	// The rest of these are calls to stdlib floating point math
	// functions.

	// If we're calling "log", we want "log10"
	if (expr->function == "log")
		expr->function = "log10";
	// If we're calling "ln", we want "log"
	if (expr->function == "ln")
		expr->function = "log";
	// If we're calling "abs", we want "fabs"
	if (expr->function == "abs")
		expr->function = "fabs";

	// Emit a call to function (arg)
	Value *arg = expr->args[0]->generate (this);
	if (!arg) return NULL;
	
	Module *M = builder.GetInsertBlock ()->getParent ()->getParent ();
	Value *Callee = M->getOrInsertFunction (expr->function,
	                                        Type::getDoubleTy (getGlobalContext ()),
	                                        Type::getDoubleTy (getGlobalContext ()),
	                                        NULL);
	CallInst *CI = builder.CreateCall (Callee, arg, expr->function);
	if (const Function *F = dyn_cast<Function>(Callee->stripPointerCasts ()))
		CI->setCallingConv (F->getCallingConv ());
	
	return CI;
}


};
};

