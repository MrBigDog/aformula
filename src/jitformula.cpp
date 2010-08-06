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
#include "jitformula.h"
#include "parser.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;


JITFormula::JITFormula () : parseTree (NULL)
{
}

JITFormula::~JITFormula ()
{
	if (parseTree)
		delete parseTree;
}


bool JITFormula::setExpression (const std::string &str)
{
	if (parseTree)
		delete parseTree;
	
	expr = str;

	parseTree = Parser::parseString (expr);
	if (!parseTree)
		return false;
	
	return true;
}

std::string JITFormula::expression () const
{
	return expr;
}

bool JITFormula::setVariable (const std::string &variable, double *pointer)
{
	return Parser::setVariable (variable, pointer);
}

double JITFormula::evaluate ()
{
	// teehee woo
	errorMessage = "not implemented";
	
	return 0.0;
}

};
};
