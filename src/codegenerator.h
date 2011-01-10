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
/// @file codegenerator.h
/// @brief Definition of the @c CodeGenerator interface.

#ifndef CODEGENERATOR_H__
#define CODEGENERATOR_H__

namespace AFormula
{

namespace Private
{

class NumberExprAST;
class VariableExprAST;
class UnaryMinusExprAST;
class BinaryExprAST;
class CallExprAST;



/// @brief Abstract interface for code generator visitor.
///
/// We implement a visitor pattern (with double-dispatch) for
/// just-in-time code compilation with any compiler.  The parser creates a
/// recursive-descent parsing tree, and the JIT formula classes implement
/// this pattern, overriding the various @c emit() methods to produce
/// appropriate code.
///
/// All of the @c emit() methods are defined to return @c void* pointers.
/// These will in fact be whatever the appropriate class for the JIT
/// compiler at issue is.  For @c LLVMFormula class, this is an @c
/// LLVM::Value* pointer, and for the @c LibJITFormula class, this is a
/// @c jit_value_t pointer.  The ponters are defined generically here to
/// prevent the entire @c CodeGenerator, @c ExprAST, and @c Parser class
/// structure from being template classes.
class CodeGenerator
{
public:
	/// @brief Destructor.
	virtual ~CodeGenerator () { }

	/// @brief Emit the code for a constant number.
	virtual void *emit (NumberExprAST *) = 0;
	/// @brief Emit the code for a variable reference.
	virtual void *emit (VariableExprAST *) = 0;
	/// @brief Emit the code for a unary negation operator.
	virtual void *emit (UnaryMinusExprAST *) = 0;
	/// @brief Emit the code for a binary operator.
	virtual void *emit (BinaryExprAST *) = 0;
	/// @brief Emit the code for a function call.
	virtual void *emit (CallExprAST *) = 0;
};

};
};

#endif /* CODEGENERATOR_H__ */

// Local Variables:
// mode: c++
// End:
