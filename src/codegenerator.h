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
#ifndef CODEGENERATOR_H__
#define CODEGENERATOR_H__

namespace AFormula
{

namespace Private
{

//
// We implement a visitor pattern over a "code generator" class, so
// that it's easy to spin this parse tree out to whatever JIT library
// we might like.
//
class ExprAST;
class NumberExprAST;
class VariableExprAST;
class UnaryMinusExprAST;
class BinaryExprAST;
class CallExprAST;


// We need this full list of all kinds of expressions to write the
// CodeGenerator base class.

class CodeGenerator
{
public:
	virtual ~CodeGenerator ()
	{
	}

	virtual void emit (NumberExprAST *) = 0;
	virtual void emit (VariableExprAST *) = 0;
	virtual void emit (UnaryMinusExprAST *) = 0;
	virtual void emit (BinaryExprAST *) = 0;
	virtual void emit (CallExprAST *) = 0;
};

};
};

#endif /* CODEGENERATOR_H__ */

// Local Variables:
// mode: c++
// End:
