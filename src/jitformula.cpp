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
#include <limits>
#include "jitformula.h"
#include "parser.h"
#include "parsetree.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;


JITFormula::JITFormula () : func (NULL), parseTree (NULL)
{
	parser = new Parser;
}

JITFormula::~JITFormula ()
{
	if (parser)
		delete parser;
	if (parseTree)
		delete parseTree;
}


bool JITFormula::setExpression (const std::string &str)
{
	if (parseTree)
		delete parseTree;
	
	expr = str;

	// Build the parse tree for the expression
	parseTree = parser->parseString (expr);
	if (!parseTree)
		return false;

	// Generate the code for the function (don't error on this for now, we're
	// testing the parser)
//	if (!buildFunction ())
//		return false;
//	if (!func)
//		return false;
			
	return true;
}

std::string JITFormula::expression () const
{
	return expr;
}

bool JITFormula::setVariable (const std::string &variable, double *pointer)
{
	return parser->setVariable (variable, pointer);
}

double JITFormula::evaluate ()
{
	if (!func)
	{
		errorMessage = "JITFormula: Could not build function for formula";
		return std::numeric_limits<double>::quiet_NaN ();
	}
	
	return func ();
}

};
};

