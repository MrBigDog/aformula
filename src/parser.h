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
#ifndef PARSER_H__
#define PARSER_H__

#include <string>
#include <vector>

namespace AFormula
{

namespace Private
{

namespace Parser
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
};

class NumberExprAST : public ExprAST
{
	double val;
public:
	NumberExprAST (double d) : val (d)
	{
	}
};

class VariableExprAST : public ExprAST
{
	std::string name;
public:
	VariableExprAST (const std::string &n) : name (n)
	{
	}
};

class UnaryMinusExprAST : public ExprAST
{
	ExprAST *child;
public:
	UnaryMinusExprAST (ExprAST *c) : child (c)
	{
	}
	virtual ~UnaryMinusExprAST ()
	{
		if (child)
			delete child;
	}
};

class BinaryExprAST : public ExprAST
{
	std::string op;
	ExprAST *LHS, *RHS;
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
};

class CallExprAST : public ExprAST
{
	std::string function;
	std::vector<ExprAST *> args;
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
};


//
// Parser access functions
//

void clearVariables ();
bool setVariable (const std::string &name, double *pointer);

ExprAST *parseString (const std::string &formula);

};
};
};

#endif /* PARSER_H__ */

// Local Variables:
// mode: c++
// End:
