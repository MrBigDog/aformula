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
#ifndef LLVMFORMULA_H__
#define LLVMFORMULA_H__

#include "jitformula.h"

#include <llvm/Module.h>
#include <llvm/IRBuilder.h>

namespace AFormula
{

namespace Private
{

class LLVMFormula : public JITFormula
{
protected:
	virtual bool buildFunction ();

private:
	// yadda
};

};
};

#endif /* LLVMFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
