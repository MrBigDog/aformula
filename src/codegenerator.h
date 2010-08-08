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

template <typename T> class NumberExprAST;
template <typename T> class VariableExprAST;
template <typename T> class UnaryMinusExprAST;
template <typename T> class BinaryExprAST;
template <typename T> class CallExprAST;


// We need this full list of all kinds of expressions to write the
// CodeGenerator base class.

template<typename T>
class CodeGenerator
{
public:
	virtual ~CodeGenerator ()
	{
	}

	virtual T emit (NumberExprAST<T> *) = 0;
	virtual T emit (VariableExprAST<T> *) = 0;
	virtual T emit (UnaryMinusExprAST<T> *) = 0;
	virtual T emit (BinaryExprAST<T> *) = 0;
	virtual T emit (CallExprAST<T> *) = 0;
};

};
};

#endif /* CODEGENERATOR_H__ */

// Local Variables:
// mode: c++
// End:
