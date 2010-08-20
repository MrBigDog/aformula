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


/// @brief Base class for JIT formula compilers.
///
/// This class implements the basic parsing infrastructure for all JIT
/// compiling formula classes.  Any specific generator class needs to
/// implement the @c CodeGenerator interface and then override the @c
/// buildFunction method.
class JITFormula : public Formula
{
public:
	/// @brief Constructor.
	JITFormula ();
	/// @brief Destructor.
	virtual ~JITFormula ();

	/// @brief Set expression, parse, and compile.
	///
	/// @param[in] str Function to evaluate.
	/// @return True if function parses and compiles successfully,
	/// false otherwise.
	///
	/// This function sets the new expression and parses it into the
	/// @c parseTree variable.  Finally, it calls the @c buildFunction
	/// method and checks to make sure the @c func variable was
	/// properly initialized.
	virtual bool setExpression (const std::string &str);

	virtual std::string expression () const;
	virtual bool setVariable (const std::string &variable, double *pointer);
	virtual double evaluate ();

protected:
	
	/// @brief Compile JIT code for parsed formula.
	///
	/// When this function is called, the @c parseTree member has been set
	/// to the root of the parsed expression.  This function sets up a new
	/// compilation environment, and generates the code for the formula by
	/// double dispatch (calling @c ExprAST::generate which will in turn
	/// call @c CodeGenerator::emit).  Finally, it finalizes the code and
	/// builds the function pointer to @c func.
	virtual bool buildFunction () = 0;


	/// @brief Function type for compiled function.
	typedef double (*FunctionPointer)(void);
	
	/// @brief Compiled function pointer.
	///
	/// After @c buildFunction is called, this variable will point to the
	/// compiled machine code function.
	FunctionPointer func;


	/// @brief String-format formula to be evaluated.
	std::string expr;

	/// @brief Parser object.
	///
	/// This parser is kept in order to keep track of registered
	/// variables.
	Parser parser;
	
	/// @brief Root node of parsed formula.
	ExprAST *parseTree;
};

};

};


#endif /* LLVMFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
