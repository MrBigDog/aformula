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
#include <boost/thread/tss.hpp>

#include "jitformula.h"
#include "parsetree.h"

namespace AFormula
{

namespace Private
{
extern boost::thread_specific_ptr<std::string> errorMessage;


JITFormula::JITFormula () : func (NULL), parseTree (NULL)
{ }

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
	
	// Build the parse tree for the expression
	parseTree = parser.parseString (expr);
	if (!parseTree)
		return false;
	
	// Generate the code for the function
	if (!buildFunction ())
		return false;
	if (!func)
		return false;
	
	return true;
}

std::string JITFormula::expression () const
{
	return expr;
}

bool JITFormula::setVariable (const std::string &variable, double *pointer)
{
	return parser.setVariable (variable, pointer);
}

double JITFormula::evaluate ()
{
	if (!func)
	{
		errorMessage.reset (new std::string ("JITFormula: attempted to evaluate a function before compiling it successfully!"));
		return std::numeric_limits<double>::quiet_NaN ();
	}
	
	return func ();
}


};
};

