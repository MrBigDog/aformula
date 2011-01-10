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
/// @file libjitformula.cpp
/// @brief Implementation of the @c LibJITFormula class.

#include <aformula.h>
#include <jit/jit.h>
#include "libjitformula.h"
#include "parsetree.h"


namespace AFormula
{

namespace Private
{

void *LibJITFormula::emit (NumberExprAST *expr)
{
	return jit_value_create_float64_constant (function, jit_type_float64,
	                                          (jit_float64)expr->val);
}

void *LibJITFormula::emit (VariableExprAST *expr)
{
	// Create a pointer temporary with the address stored in it
	jit_value_t pointer = jit_value_create_nint_constant (function, jit_type_void_ptr,
	                                                      (jit_nint)expr->pointer);

	// Create a load instruction for this address
	return jit_insn_load_relative (function, pointer, 0, jit_type_float64);
}

void *LibJITFormula::emit (UnaryMinusExprAST *expr)
{
	// Generate the contents of the unary-minus
	jit_value_t val = (jit_value_t)expr->child->generate (this);
	if (val == NULL) return NULL;

	return jit_insn_neg (function, val);
}

void *LibJITFormula::emit (BinaryExprAST *expr)
{
	// Deal with assign separately, we don't want to compile the LHS
	if (expr->op == "=")
	{
		VariableExprAST *var = dynamic_cast<VariableExprAST *>(expr->LHS);
		if (!var) return NULL;

		jit_value_t val = (jit_value_t)expr->RHS->generate (this);
		if (!val) return NULL;

		// Get a pointer for this variable
		jit_value_t pointer = jit_value_create_nint_constant (function, jit_type_void_ptr,
		                                                      (jit_nint)var->pointer);

		// Emit a store instruction
		jit_insn_store_relative (function, pointer, 0, val);

		// Return value
		return val;
	}
		
	// Generate both sides
	jit_value_t L = (jit_value_t)expr->LHS->generate (this);
	jit_value_t R = (jit_value_t)expr->RHS->generate (this);
	if (L == NULL || R == NULL) return NULL;
	
	if (expr->op == "<=")
		return jit_insn_le (function, L, R);
	else if (expr->op == ">=")
		return jit_insn_ge (function, L, R);
	else if (expr->op == "!=")
		return jit_insn_ne (function, L, R);
	else if (expr->op == "==")
		return jit_insn_eq (function, L, R);
	else if (expr->op == "<")
		return jit_insn_lt (function, L, R);
	else if (expr->op == ">")
		return jit_insn_gt (function, L, R);
	else if (expr->op == "+")
		return jit_insn_add (function, L, R);
	else if (expr->op == "-")
		return jit_insn_sub (function, L, R);
	else if (expr->op == "*")
		return jit_insn_mul (function, L, R);
	else if (expr->op == "/")
		return jit_insn_div (function, L, R);
	else if (expr->op == "^")
	{
		// jit_insn_pow seems to give the wrong results?
		jit_type_t params[2];
		params[0] = jit_type_float64;
		params[1] = jit_type_float64;
		jit_type_t signature;
		signature = jit_type_create_signature (jit_abi_cdecl, jit_type_float64,
		                                       params, 2, 1);
		jit_value_t args[2];
		args[0] = L;
		args[1] = R;
				
		return jit_insn_call_native (function, "pow", (void *)pow, signature,
		                             args, 2, 0);
	}
	else
		return NULL;
}

void *LibJITFormula::emit (CallExprAST *expr)
{
	if (expr->function == "if")
	{
		// We're going to make a new temporary, and store a value to it depending
		// on what happens here.
		jit_value_t result = jit_value_create (function, jit_type_float64);
				
		// if (cond)
		jit_value_t cond = (jit_value_t)expr->args[0]->generate (this);
		if (!cond) return NULL;

		jit_value_t one = jit_value_create_float64_constant (function, jit_type_float64,
		                                                     1.0);
		jit_value_t comparison = jit_insn_eq (function, cond, one);
		jit_label_t label_if = jit_label_undefined;
		jit_label_t label_end = jit_label_undefined;
				
		jit_insn_branch_if_not (function, comparison, &label_if);

		// (the if-value)
		jit_value_t t = (jit_value_t)expr->args[1]->generate (this);
		jit_insn_store (function, result, t);
		jit_insn_branch (function, &label_end);
		
		// The else branches to here...
		jit_insn_label (function, &label_if);

		// (the else-value)
		jit_value_t f = (jit_value_t)expr->args[2]->generate (this);
		jit_insn_store (function, result, f);

		jit_insn_label (function, &label_end);
		
		return result;
	}
	else if (expr->function == "sign")
	{
		// Same thing as the if-function above
		jit_value_t one = jit_value_create_float64_constant (function, jit_type_float64,
		                                                     1.0);
		jit_value_t zero = jit_value_create_float64_constant (function, jit_type_float64,
		                                                      0.0);
		jit_value_t minusone = jit_value_create_float64_constant (function,
		                                                          jit_type_float64,
		                                                          -1.0);
		
		jit_value_t arg = (jit_value_t)expr->args[0]->generate (this);
		jit_value_t result = jit_value_create (function, jit_type_float64);
		jit_label_t label_end = jit_label_undefined;
		
		jit_value_t positive = jit_insn_gt (function, arg, zero);
		jit_label_t label_positive = jit_label_undefined;
		jit_insn_branch_if_not (function, positive, &label_positive);
		jit_insn_store (function, result, one);
		jit_insn_branch (function, &label_end);
		jit_insn_label (function, &label_positive);
		
		jit_value_t negative = jit_insn_lt (function, arg, zero);
		jit_label_t label_negative = jit_label_undefined;
		jit_insn_branch_if_not (function, negative, &label_negative);
		jit_insn_store (function, result, minusone);
		jit_insn_branch (function, &label_end);
		jit_insn_label (function, &label_negative);

		jit_insn_store (function, result, zero);
		jit_insn_label (function, &label_end);

		return result;
	}
	
	// Compile the arguments
	// HACK: we just assume for now that if() is the only thing with
	// more than one argument.
	jit_value_t arg = (jit_value_t)expr->args[0]->generate (this);

	// Create a native signature for our few native functions
	jit_type_t params[1];
	params[0] = jit_type_float64;
	jit_type_t signature;
	signature = jit_type_create_signature (jit_abi_cdecl, jit_type_float64,
	                                       params, 1, 1);

	// Several of the jit_insn_FUNC constructs below have been replaced
	// by jit_insn_call_native, because the intrinsic instructions seem to
	// give the wrong answers.
	if (expr->function == "sin")
		return jit_insn_call_native (function, "sin", (void *)sin, signature,
		                             &arg, 1, 0);
	else if (expr->function == "cos")
		return jit_insn_call_native (function, "cos", (void *)cos, signature,
		                             &arg, 1, 0);
	else if (expr->function == "tan")
		return jit_insn_call_native (function, "tan", (void *)tan, signature,
		                             &arg, 1, 0);
	else if (expr->function == "asin")
		return jit_insn_call_native (function, "asin", (void *)asin, signature,
		                             &arg, 1, 0);
	else if (expr->function == "acos")
		return jit_insn_call_native (function, "acos", (void *)acos, signature,
		                             &arg, 1, 0);
	else if (expr->function == "atan")
		return jit_insn_call_native (function, "atan", (void *)atan, signature,
		                             &arg, 1, 0);
	else if (expr->function == "sinh")
		return jit_insn_call_native (function, "sinh", (void *)sinh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "cosh")
		return jit_insn_call_native (function, "cosh", (void *)cosh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "tanh")
		return jit_insn_call_native (function, "tanh", (void *)tanh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "asinh")
		return jit_insn_call_native (function, "asinh", (void *)asinh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "acosh")
		return jit_insn_call_native (function, "acosh", (void *)acosh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "atanh")
		return jit_insn_call_native (function, "atanh", (void *)atanh, signature,
		                             &arg, 1, 0);
	else if (expr->function == "log2")
		return jit_insn_call_native (function, "log2", (void *)log2, signature,
		                             &arg, 1, 0);
	else if (expr->function == "log" || expr->function == "log10")
		return jit_insn_call_native (function, "log10", (void *)log10, signature,
		                             &arg, 1, 0);
	else if (expr->function == "ln")
		return jit_insn_call_native (function, "log", (void *)log, signature,
		                             &arg, 1, 0);
	else if (expr->function == "exp")
		return jit_insn_call_native (function, "exp", (void *)exp, signature,
		                             &arg, 1, 0);
	else if (expr->function == "sqrt")
		return jit_insn_sqrt (function, arg);
	else if (expr->function == "abs")
		return jit_insn_abs (function, arg);
	else if (expr->function == "rint")
		return jit_insn_call_native (function, "rint", (void *)rint, signature,
		                             &arg, 1, 0);
	else
		return NULL;
}


bool LibJITFormula::buildFunction ()
{
	// Create a context
	jit_context_t context;
	context = jit_context_create ();
	jit_context_build_start (context);

	// Create a signature for double (*func)();
	jit_type_t signature;
	signature = jit_type_create_signature (jit_abi_cdecl, jit_type_float64,
	                                       NULL, 0, 1);

	// Create a function
	function = jit_function_create (context, signature);

	// Return the result of compiling the whole mess
	jit_value_t val;
	val = (jit_value_t)parseTree->generate (this);
	if (!val)
		return false;

	jit_insn_return (function, val);
	jit_context_build_end (context);

	if (!jit_function_compile (function))
	{
		jit_function_abandon (function);
		return false;
	}

	func = (FunctionPointer)jit_function_to_closure (function);
	if (!func)
	{
		jit_function_abandon (function);
		return false;
	}
		
	return true;
}

};
};

