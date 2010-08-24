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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//
// Test parsing of all sorts of formulas.  The bulk of this test
// is borrowed from the muParser syntax checker.
//

AFormula::Formula *f;

void CHECK_EQUATION(const char *formula, bool pass)
{
	bool error = !f->setExpression (formula);
	
	if (pass)
	{
		// Expected pass
		if (error)
		{
			fprintf (stderr, "FAIL (fail, expected pass): %s does not parse\n", formula);
			fprintf (stderr, "%s\n", f->errorString ().c_str ());			
			exit (1);
		}
		else
			fprintf (stdout, "PASS (pass, expected pass): %s parses\n", formula);
	}
	else
	{
		// Expected fail
		if (!error)
		{
			fprintf (stderr, "FAIL (pass, expected fail): %s does parse, should not\n", formula);			
			exit (1);
		}
		else
		{
			fprintf (stdout, "FAIL (fail, expected fail): %s does not parse\n", formula);
		}
	}
}


int main (int argc, char *argv[])
{
	for (int i = 1 ; i < AFormula::Formula::NUM_BACKENDS ; i++)
	{
		double a = 1.0;

		fprintf (stdout, "\n*** Begin testing backend number %d:\n\n", i);

		f = AFormula::Formula::createFormula (i);
		if (!f)
		{
			fprintf (stderr, "FAIL: Could not create formula for backend %d\n", i);
			return 1;
		}

		if (!f->setVariable ("a", &a))
		{
			fprintf (stderr, "FAIL: Could not set variable for backend %d\n", i);
			delete f;
			return 1;
		}
				
		CHECK_EQUATION ("(1+ 2*a)", true);   // Spaces within formula
		CHECK_EQUATION ("sqrt((4))", true);  // Multiple brackets
		CHECK_EQUATION ("sqrt((2)+2)", true);// Multiple brackets
		CHECK_EQUATION ("sqrt(2+(2))", true);// Multiple brackets
		CHECK_EQUATION ("sqrt(a+(3))", true);// Multiple brackets
		CHECK_EQUATION ("sqrt((3)+a)", true);// Multiple brackets
		CHECK_EQUATION ("(2+", false);       // missing closing bracket 
		CHECK_EQUATION ("2++4", false);      // unexpected operator
		CHECK_EQUATION ("(2+)", false);      // unexpected closing bracket
		CHECK_EQUATION ("--2", false);       // double sign
		CHECK_EQUATION ("ksdfj", false);     // unknown token
		CHECK_EQUATION ("()", false);        // empty bracket without a function
		CHECK_EQUATION ("5+()", false);      // empty bracket without a function
		CHECK_EQUATION ("sin(cos)", false);  // unexpected function
		CHECK_EQUATION ("5t6", false);       // unknown token
		CHECK_EQUATION ("5 t 6", false);     // unknown token
		CHECK_EQUATION ("8*", false);        // unexpected end of formula
		CHECK_EQUATION (",3", false);        // unexpected comma
		CHECK_EQUATION ("3,5", false);       // unexpected comma
		CHECK_EQUATION ("sin(8,8)", false);  // too many function args
		CHECK_EQUATION ("(7,8)", false);     // too many function args
		CHECK_EQUATION ("sin)", false);      // unexpected closing bracket
		CHECK_EQUATION ("a)", false);        // unexpected closing bracket
		CHECK_EQUATION ("pi)", false);       // unexpected closing bracket
		CHECK_EQUATION ("sin(())", false);   // unexpected closing bracket
		CHECK_EQUATION ("sin()", false);     // unexpected closing bracket
		
		delete f;
	}
	
	return 0;
}
