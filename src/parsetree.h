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
#ifndef PARSETREE_H__
#define PARSETREE_H__

#include <vector>

#include "codegenerator.h"

namespace AFormula
{

namespace Private
{


//
// Thanks to the LLVM docs for this easy-to-use parser setup, which
// I've hacked and simplified even more for our case.
//

class ExprAST
{
public:
	virtual ~ExprAST () 
	{
	}

	virtual void generate (CodeGenerator *) = 0;
};

class NumberExprAST : public ExprAST
{
public:
	NumberExprAST (double d) : val (d)
	{
	}

	double val;

	virtual void generate (CodeGenerator *gen)
	{ gen->emit (this); }
};

class VariableExprAST : public ExprAST
{
public:
	VariableExprAST (const std::string &n) : name (n)
	{
	}

	std::string name;

	virtual void generate (CodeGenerator *gen)
	{ gen->emit (this); }
};

class UnaryMinusExprAST : public ExprAST
{
public:
	UnaryMinusExprAST (ExprAST *c) : child (c)
	{
	}
	virtual ~UnaryMinusExprAST ()
	{
		if (child)
			delete child;
	}

	ExprAST *child;

	virtual void generate (CodeGenerator *gen)
	{ gen->emit (this); }
};

class BinaryExprAST : public ExprAST
{
public:
	BinaryExprAST (const std::string &o, ExprAST *l, ExprAST *r) :
		op (o), LHS (l), RHS (r)
	{
	}
	virtual ~BinaryExprAST ()
	{
		if (LHS)
			delete LHS;
		if (RHS)
			delete RHS;
	}

	std::string op;
	ExprAST *LHS, *RHS;
	
	virtual void generate (CodeGenerator *gen)
	{ gen->emit (this); }
};

class CallExprAST : public ExprAST
{
public:
	CallExprAST (const std::string &fun, const std::vector<ExprAST *> &a) :
		function (fun), args (a)
	{
	}
	virtual ~CallExprAST ()
	{
		for (std::vector<ExprAST *>::iterator iter = args.begin () ;
		     iter != args.end () ; ++iter)
			delete (*iter);
	}

	std::string function;
	std::vector<ExprAST *> args;
	
	virtual void generate (CodeGenerator *gen)
	{ gen->emit (this); }
};

};
};

#endif /* PARSETREE_H__ */

// Local Variables:
// mode: c++
// End:
