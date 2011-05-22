/*
  Copyright (C) 2010-2011  Charles Pence <charles@charlespence.net>
  
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
/// @file formula.cpp
/// @brief Implementation of the @c Formula class.

#include <aformula.h>
#include <config.h>

#include <csignal>
#include <boost/thread/tss.hpp>

#include "muparserformula.h"

#ifdef HAVE_LLVM
#  include "llvmformula.h"
#endif
#ifdef HAVE_LIBJIT
#  include "libjitformula.h"
#endif

namespace AFormula
{

/// @namespace AFormula::Private
/// @brief Namespace containing code private to the AFormula implementation.
///
/// No code in the Private namespace should be visible to users of the
/// AFormula library, nor should it be usable.
namespace Private
{
/// @brief Global storage for current error string.
///
/// Our library code sets error messages in this variable.  It is returned and
/// then cleared by Formula::errorString().
boost::thread_specific_ptr<std::string> errorMessage;

/// @brief Current backend which will be used if @c BACKEND_DEFAULT
/// is specified.
int defaultBackend = BACKEND_MUPARSER;
};

//
// Error message support
//
std::string Formula::errorString ()
{
	if (!Private::errorMessage.get ())
		return std::string ("");
		
	std::string copy (*Private::errorMessage);
	Private::errorMessage.reset ();
	
	return copy;
}


//
// Backend selection
//

Formula *Formula::createFormula (int withBackend)
{
	// Check input
	if (withBackend < 0 || withBackend > NUM_BACKENDS)
	{
		Private::errorMessage.reset (new std::string ("Formula::createFormula: Invalid backend requested"));
		return NULL;
	}
	
	// Take the default backend if requested
	if (withBackend == BACKEND_DEFAULT)
		withBackend = Private::defaultBackend;

	Formula *formula = NULL;
	
	switch (withBackend)
	{
#ifdef HAVE_LLVM
	case BACKEND_LLVM:
		formula = new Private::LLVMFormula;
		break;
#endif

#ifdef HAVE_LIBJIT
	case BACKEND_LIBJIT:
		formula = new Private::LibJITFormula;
		break;
#endif
		
	case BACKEND_MUPARSER:
	default:
		formula = new Private::MuParserFormula;
		break;
	};
	
	return formula;
}



//
// Constructor / Destructor
//

Formula::Formula ()
{
}


Formula::~Formula ()
{
}


};
