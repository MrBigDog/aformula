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
#ifndef AFORMULA_H__
#define AFORMULA_H__

#include <string>


namespace AFormula
{


class Formula
{
public:
	virtual ~Formula ();

	
	//
	// Available formula-execution backends
	//
	static const int BACKEND_DEFAULT = 0;
	static const int BACKEND_MUPARSER = 1;
	static const int BACKEND_LVVM = 2;
	static const int BACKEND_LIBJIT = 3;
	static const int NUM_BACKENDS = 4;
		
	
	//
	// Formula creation and backend support
	//
	
	// Create a Formula using the currently-selected backend.  The returned
	// formula should be deleted using 'delete' when it is no longer
	// needed.
	static Formula *createFormula (int withBackend = BACKEND_DEFAULT);

	// Determine using a run-time benchmark the fastest parsing backend.
	// Note that this is a blocking call that will take some time.  If
	// setAsDefault is true (the default), future calls to createFormula
	// with BACKEND_DEFAULT will use the backend that this function
	// determines to be the fastest.
	static int fastestBackend (bool setAsDefault = true);


	//
	// Error support
	//

	// FIXME: As written, this function is not thread-safe
	std::string errorString ();
	

	//
	// Formula evaluation, expressions, and variables
	//
	
	// Set and retrieve the expression to evaluate.  Return false on
	// error.
	virtual bool setExpression (const std::string &str) = 0;
	virtual std::string expression () const = 0;

	// Set a variable to a given double-pointer
	virtual bool setVariable (const std::string &variable, double *pointer) = 0;

	
	// Evaluate the formula
	virtual double evaluate () = 0;

protected:
	// Constructor is private; call the creation function above
	Formula ();

private:
	// Not implemented; this class is not copyable
	Formula (const Formula &rhs);
	Formula &operator= (const Formula &rhs);
};

};

#endif /* AFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
