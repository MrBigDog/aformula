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
#ifndef JITFORMULA_H__
#define JITFORMULA_H__

#include "parser.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;


template<typename T>
class JITFormula : public Formula
{
public:
	JITFormula () : func (NULL), parseTree (NULL)
	{
		parser = new Parser<T>;
	}
	
	virtual ~JITFormula ()
	{
		if (parser)
			delete parser;
		if (parseTree)
			delete parseTree;
	}
	
	
	virtual bool setExpression (const std::string &str)
	{
		if (parseTree)
			delete parseTree;
		
		expr = str;
		
		// Build the parse tree for the expression
		parseTree = parser->parseString (expr);
		if (!parseTree)
			return false;
		
		// Generate the code for the function
		if (!buildFunction ())
			return false;
		if (!func)
			return false;
		
		return true;
	}

	virtual std::string expression () const
	{
		return expr;
	}
	
	virtual bool setVariable (const std::string &variable, double *pointer)
	{
		return parser->setVariable (variable, pointer);
	}
	
	virtual double evaluate ()
	{
		if (!func)
		{
			errorMessage = "JITFormula: Could not build function for formula";
			return std::numeric_limits<double>::quiet_NaN ();
		}
		
		return func ();
	}

protected:
	virtual bool buildFunction () = 0;

	typedef double (*FunctionPointer)(void);
	FunctionPointer func;
	
	std::string expr;
	Parser<T> *parser;
	ExprAST<T> *parseTree;
};

};

};


#endif /* LLVMFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
