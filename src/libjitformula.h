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
#ifndef LIBJITFORMULA_H__
#define LIBJITFORMULA_H__

#include "jitformula.h"
#include "codegenerator.h"

#include <jit/jit.h>

namespace AFormula
{

namespace Private
{

/// @brief Formula-compiling backend using libjit.
///
/// This backed uses the libjit library to compile our parsed expressions
/// into machine code.
class LibJITFormula : public JITFormula, public CodeGenerator
{
public:
	virtual void *emit (NumberExprAST *);
	virtual void *emit (VariableExprAST *);
	virtual void *emit (UnaryMinusExprAST *);
	virtual void *emit (BinaryExprAST *);
	virtual void *emit (CallExprAST *);

protected:
	virtual bool buildFunction ();

private:
	// yadda
};

};
};

#endif /* LIBJITFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
