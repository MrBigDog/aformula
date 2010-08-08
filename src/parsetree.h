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

template<typename T> class CodeGenerator;

//
// Thanks to the LLVM docs for this easy-to-use parser setup, which
// I've hacked and simplified even more for our case.
//

template<typename T>
class ExprAST
{
public:
	virtual ~ExprAST () 
	{
	}

	virtual T generate (CodeGenerator<T> *) = 0;
};

template<typename T>
class NumberExprAST : public ExprAST<T>
{
public:
	NumberExprAST (double d) : val (d)
	{
	}

	double val;

	virtual T generate (CodeGenerator<T> *gen)
	{ return gen->emit (this); }
};

template<typename T>
class VariableExprAST : public ExprAST<T>
{
public:
	VariableExprAST (const std::string &n, double *p) : name (n), pointer (p)
	{
	}

	std::string name;
	double *pointer;
	
	virtual T generate (CodeGenerator<T> *gen)
	{ return gen->emit (this); }
};

template<typename T>
class UnaryMinusExprAST : public ExprAST<T>
{
public:
	UnaryMinusExprAST (ExprAST<T> *c) : child (c)
	{
	}
	virtual ~UnaryMinusExprAST ()
	{
		if (child)
			delete child;
	}

	ExprAST<T> *child;

	virtual T generate (CodeGenerator<T> *gen)
	{ return gen->emit (this); }
};

template<typename T>
class BinaryExprAST : public ExprAST<T>
{
public:
	BinaryExprAST (const std::string &o, ExprAST<T> *l, ExprAST<T> *r) :
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
	ExprAST<T> *LHS, *RHS;

	virtual T generate (CodeGenerator<T> *gen)
	{ return gen->emit (this); }
};

template<typename T>
class CallExprAST : public ExprAST<T>
{
public:
	CallExprAST (const std::string &fun, const std::vector<ExprAST<T> *> &a) :
		function (fun), args (a)
	{
	}
	virtual ~CallExprAST ()
	{
		for (typename std::vector<ExprAST<T> *>::iterator iter = args.begin () ;
		     iter != args.end () ; ++iter)
			delete (*iter);
	}

	std::string function;
	std::vector<ExprAST<T> *> args;

	virtual T generate (CodeGenerator<T> *gen)
	{ return gen->emit (this); }
};

};
};

#endif /* PARSETREE_H__ */

// Local Variables:
// mode: c++
// End:
