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
/// @file parsetree.h
/// @brief Definition of the various @c ExprAST classes.

#ifndef PARSETREE_H__
#define PARSETREE_H__

#include <vector>
#include "codegenerator.h"

namespace AFormula
{

namespace Private
{

class CodeGenerator;

//
// Thanks to the LLVM docs for this easy-to-use parser setup, which
// I've hacked and simplified even more for our case.
//

/// @class ExprAST
/// @brief Base class for all expressions in our syntax tree.
class ExprAST
{
public:
	/// @brief Destructor.
	virtual ~ExprAST () { }

	/// @brief Double-dispatch code generation method.
	///
	/// @param[in] gen Code generator to call for emitting code.
	/// @return Result of @c CodeGenerator::emit, see documentation
	/// for that function for information about this pointer type.
	///
	/// This method is overridden to call the appropriate @c
	/// CodeGenerator::emit method 
	virtual void *generate (CodeGenerator *gen) = 0;
};


/// @class NumberExprAST
/// @brief Syntax tree element for a constant number.
class NumberExprAST : public ExprAST
{
public:
	/// @brief Constructor.
	/// @param[in] d Number which this element represents.
	NumberExprAST (double d) : val (d) { }

	/// @brief Number which this element represents.
	double val;

	virtual void *generate (CodeGenerator *gen)
	{ return gen->emit (this); }
};


/// @class VariableExprAST
/// @brief Syntax tree element for a reference to a variable.
class VariableExprAST : public ExprAST
{
public:
	/// @brief Constructor.
	/// @param[in] n Name of the variable which this element represents.
	/// @param[in] p Pointer to the double value for this variable.
	VariableExprAST (const std::string &n, double *p) : name (n), pointer (p) { }

	/// @brief Name of the variable which this element represents.
	std::string name;
	/// @brief Pointer to the double value for this variable.
	double *pointer;
	
	virtual void *generate (CodeGenerator *gen)
	{ return gen->emit (this); }
};


/// @class UnaryMinusExprAST
/// @brief Syntax tree element for a unary minus operator.
class UnaryMinusExprAST : public ExprAST
{
public:
	/// @brief Constructor.
	/// @param[in] c Expression which this operator negates.
	UnaryMinusExprAST (ExprAST *c) : child (c) { }

	/// @brief Destructor.
	virtual ~UnaryMinusExprAST ()
	{
		if (child)
			delete child;
	}

	/// @brief Expression which this operator negates.
	ExprAST *child;

	virtual void *generate (CodeGenerator *gen)
	{ return gen->emit (this); }
};


/// @class BinaryExprAST
/// @brief Syntax tree element representing a binary-operator expression.
class BinaryExprAST : public ExprAST
{
public:
	/// @brief Constructor.
	/// @param[in] o String for the binary operator in this expression.
	/// @param[in] l Left-hand side of this expression.
	/// @param[in] r Right-hand side of this expression.
	BinaryExprAST (const std::string &o, ExprAST *l, ExprAST *r) :
		op (o), LHS (l), RHS (r) { }

	/// @brief Destructor.
	virtual ~BinaryExprAST ()
	{
		if (LHS)
			delete LHS;
		if (RHS)
			delete RHS;
	}

	/// @brief String for the binary operator in this expression.
	std::string op;
	/// @brief Left-hand side of this expression.
	ExprAST *LHS;
	/// @brief Right-hand side of this expression.
	ExprAST *RHS;

	virtual void *generate (CodeGenerator *gen)
	{ return gen->emit (this); }
};


/// @class CallExprAST
/// @brief Syntax tree element representing a function call.
class CallExprAST : public ExprAST
{
public:
	/// @brief Constructor.
	/// @param[in] fun Function name to be called.
	/// @param[in] a List of function arguments.
	CallExprAST (const std::string &fun, const std::vector<ExprAST *> &a) :
		function (fun), args (a) { }
	
	/// @brief Destructor.
	virtual ~CallExprAST ()
	{
		for (std::vector<ExprAST *>::iterator iter = args.begin () ;
		     iter != args.end () ; ++iter)
			delete (*iter);
	}

	/// @brief Function name to be called.
	std::string function;
	/// @brief List of function arguments.
	std::vector<ExprAST *> args;

	virtual void *generate (CodeGenerator *gen)
	{ return gen->emit (this); }
};

};
};

#endif /* PARSETREE_H__ */

// Local Variables:
// mode: c++
// End:
