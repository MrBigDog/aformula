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
#include <config.h>

#include <csignal>
#include <boost/thread/tss.hpp>

#include "timer.h"
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

/// @brief Current backend which will be used if @c BACKEND_DEFAULT
/// is specified.
static int defaultBackend = Formula::BACKEND_MUPARSER;

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
		withBackend = defaultBackend;

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



extern "C"
{
	/// @brief Set to 1 if a backend has crashed.
	volatile sig_atomic_t errorflag = 0;

	/// @brief Trap for crash signals during backend testing.
	///
	/// On our speed test, it is possible that a given backend may simply crash
	/// entirely.  We want to try to guard against that and insulate the user,
	/// so endeavor to catch any signals, raise a flag, and abort the testing of
	/// that module.
	static void signal_handler (int signum)
	{
		// One of the backends went down, let everybody know
		errorflag = 1;
	}
};

int Formula::fastestBackend (bool setAsDefault)
{
	int bestBackend = BACKEND_MUPARSER;
	uint64_t bestBackendTime = UINT64_MAX;

	// Trap SIGABRT, SIGFPE, SIGILL, SIGSEGV, and don't let a rogue
	// backend bring down the entire system
	signal (SIGABRT, signal_handler);
	signal (SIGFPE, signal_handler);
	signal (SIGILL, signal_handler);
	signal (SIGSEGV, signal_handler);

	for (int backend = 1 ; backend < NUM_BACKENDS ; backend++)
	{
		// Reset the signal error flag
		errorflag = 0;
		
		uint64_t timeStart = Private::timerTime ();
		
		Formula *formula = Formula::createFormula (backend);
		if (!formula || errorflag)
			continue;

		double x;
		formula->setVariable ("x", &x);
		if (errorflag)
			continue;

		formula->setExpression ("x*x + 4");
		if (errorflag)
			continue;

		for (int i = 0 ; i < 1000 ; i++)
		{
			x = i;
			double ret = formula->evaluate ();
			if (errorflag)
				break;
			if (ret != i * i + 4)
			{
				errorflag = 1;
				break;
			}
		}

		// We leak memory here on purpose, because we don't know whether
		// the crash has broken state in such a way that deleting the formula
		// variable will cause another crash.
		if (errorflag)
			continue;
		
		delete formula;
		
		uint64_t timeEnd = Private::timerTime ();

		if (timeEnd - timeStart < bestBackendTime)
		{
			bestBackendTime = timeEnd - timeStart;
			bestBackend = backend;
		}
	}

	// Release the signals
	signal (SIGABRT, SIG_DFL);
	signal (SIGFPE, SIG_DFL);
	signal (SIGILL, SIG_DFL);
	signal (SIGSEGV, SIG_DFL);

	return bestBackend;
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
