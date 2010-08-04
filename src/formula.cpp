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
#ifdef _WIN32
#include <windows.h>
#endif

#include <aformula.h>
#include <csignal>
#include <sys/time.h>
#include "muparserformula.h"

namespace AFormula
{

//
// Error message support
//
namespace Private
{
std::string errorMessage;
};

std::string Formula::errorString ()
{
	std::string copy (Private::errorMessage);
	Private::errorMessage.clear ();
	
	return copy;
}


//
// Backend Selection
//
static int defaultBackend = Formula::BACKEND_MUPARSER;

Formula *Formula::createFormula (int withBackend)
{
	// Check input
	if (withBackend < 0 || withBackend > NUM_BACKENDS)
	{
		Private::errorMessage = "Formula::createFormula: Invalid backend requested";
		return NULL;
	}
	
	// Take the default backend if requested
	if (withBackend == BACKEND_DEFAULT)
		withBackend = defaultBackend;


	// Create a new formula (FIXME: backend)
	Formula *formula = new Private::MuParserFormula;
	return formula;
}


//
// I hate this platform-specific hackery, but we have to get a sufficiently
// high-resolution timer on Win32, and this is the only way.
//
#ifdef _WIN32

static double timerFrequency ()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency (&ticksPerSecond);
	return 1.0 / (double)ticksPerSecond.QuadPart;
}

static double timerTime ()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter (&ticks);
	return (double)ticks.QuadPart;
}

#else

static double timerFrequency ()
{
	return 1e-6;
}

static double timerTime ()
{
	struct timeval tp;
	if (gettimeofday (&tp, NULL) != 0)
		return 0.0f;
	
	return tp.tv_sec * 1000000.0 + tp.tv_usec;
}

#endif

extern "C"
{
	volatile sig_atomic_t errorflag = 0;
	
	void signal_handler (int signum)
	{
		// One of the backends went down, let everybody know
		errorflag = 1;
	}
};

int Formula::fastestBackend (bool setAsDefault)
{
	int bestBackend = BACKEND_MUPARSER;
	double bestBackendTime = 9999999.0;

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
		
		double timeStart = timerTime ();
		
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

		if (errorflag)
			continue;
		
		delete formula;
		
		double timeEnd = timerTime ();

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
