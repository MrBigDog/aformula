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
#include "muparserformula.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;


MuParserFormula::MuParserFormula () 
{
}

MuParserFormula::~MuParserFormula ()
{
}


bool MuParserFormula::setExpression (const std::string &str)
{
	try
	{
		// Set the expression
		muParser.SetExpr (str);

		// muParser precompiles to bytecode only on the first call to Eval,
		// while we want AFormula formulas to precompile right now.
		muParser.Eval ();
		
		return true;
	}
	catch (const mu::Parser::exception_type &e)
	{
		errorMessage = "muParser: Error while setting expression to ";
		errorMessage += str;
		return false;
	}
}

std::string MuParserFormula::expression () const
{
	return muParser.GetExpr ();
}

bool MuParserFormula::setVariable (const std::string &variable, double *pointer)
{
	try
	{
		muParser.DefineVar (variable, pointer);
		return true;
	}
	catch (const mu::Parser::exception_type &e)
	{
		errorMessage = "muParser: Error while setting variable ";
		errorMessage += variable;
		return false;
	}
}

double MuParserFormula::evaluate ()
{
	try
	{
		return muParser.Eval ();
	}
	catch (mu::Parser::exception_type &e)
	{
		errorMessage = "muParser: Error evaluating expression";
		return 0.0f;
	}
}

};
};

