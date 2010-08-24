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
#include <boost/format.hpp>
#include <math.h>

#include "timer.h"

namespace AFormula
{

namespace Private
{
extern int defaultBackend;


/// @brief Compiled-C++ version of our fastestBackend benchmark, for
/// comparison testing.
static double compiledCppBenchmark (float x, float y)
{
	return (atan(sin((((((((((((((((M_PI/cos((x/((((0.53-y)-M_PI)*M_E)/y))))
	        +2.51)+x)-0.54)/0.98)+y)*y)+M_E)/x)+y)+x)+y)+M_PI)/M_E)+x)))*2.77);
}

};


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
		fprintf (stderr, "ERROR: Backend raised signal in AFormula::Formula::fastestBackend(), aborting test for this backend\n");
		errorflag = 1;
	}
};

int Formula::fastestBackend (bool setAsDefault, bool printTimings)
{
	int bestBackend = BACKEND_MUPARSER;
	uint64_t bestBackendTime = UINT64_MAX;
	
	// Trap SIGABRT, SIGFPE, SIGILL, SIGSEGV, and don't let a rogue
	// backend bring down the entire system
	signal (SIGABRT, signal_handler);
	signal (SIGFPE, signal_handler);
	signal (SIGILL, signal_handler);
	signal (SIGSEGV, signal_handler);

	if (printTimings)
		printf ("\nBackend benchmark:\n\n");
	
	for (int backend = 1 ; backend < NUM_BACKENDS ; backend++)
	{
		const char *backendName;

		// These enumeration values aren't constant (!) so we have to
		// check this specially.
		if (backend == BACKEND_MUPARSER)
			backendName = "muParser";
#ifdef HAVE_LLVM
		else if (backend == BACKEND_LLVM)
			backendName = "LLVM";
#endif
#ifdef HAVE_LIBJIT
		else if (backend == BACKEND_LIBJIT)
			backendName = "libjit";
#endif
		
		// Reset the signal error flag
		errorflag = 0;
		
		Formula *formula = Formula::createFormula (backend);
		if (!formula || errorflag)
			continue;
		
		static double x;
		static double y;
		if (!formula->setVariable ("x", &x) || !formula->setVariable ("y", &y))
			continue;
		if (errorflag)
			continue;

		const char *str =
			"(atan(sin((((((((((((((((pi/cos((x/((((0.53-y)-pi)*e)/y))))"
			"+2.51)+x)-0.54)/0.98)+y)*y)+e)/x)+y)+x)+y)+pi)/e)+x)))*2.77)";
		if (!formula->setExpression (str))
			continue;
		if (errorflag)
			continue;
		
		uint64_t timeStart = Private::timerTime ();
		
		for (int i = 0 ; i < 500000 ; i++)
		{
			x = (double)i;
			y = x / 2;
			double ret = formula->evaluate ();
			
			if (errorflag)
				break;
			
			double gd = (atan(sin((((((((((((((((M_PI/cos((x/((((0.53-y)-M_PI)*M_E)/y))))
			    +2.51)+x)-0.54)/0.98)+y)*y)+M_E)/x)+y)+x)+y)+M_PI)/M_E)+x)))*2.77);

			if (fabs (ret - gd) > 0.0001)
			{
				fprintf (stderr, "ERROR: Backend reported invalid result in AFormula::Formula::fastestBackend, aborting test for this backend\n");
				errorflag = 1;
				break;
			}
		}

		// We leak memory here on purpose, because we don't know whether
		// the crash has broken state in such a way that deleting the formula
		// variable will cause another crash.
		if (errorflag)
			continue;
				
		uint64_t timeEnd = Private::timerTime ();
		
		delete formula;

		if (timeEnd - timeStart < bestBackendTime)
		{
			bestBackendTime = timeEnd - timeStart;
			bestBackend = backend;
		}

		if (printTimings)
		{
			uint64_t frequency = Private::timerFrequency ();
			uint64_t delta = timeEnd - timeStart;
			double seconds = (double)delta / (double)frequency;
			std::string res = boost::str (
				boost::format ("Backend %1% (%2%): %3% seconds (%4% ticks)\n") %
				backend % backendName % seconds % delta);
			
			printf ("%s", res.c_str ());
		}
	}

	if (printTimings)
	{
		// Run a compiled C++ benchmark for comparison
		uint64_t timeStart = Private::timerTime ();
		errorflag = 0;
		
		for (int i = 0 ; i < 500000 ; i++)
		{
			double x = (double)i;
			double y = x / 2;
			double ret = Private::compiledCppBenchmark (x, y);

			// Fake the rest of what's in the inner loop, to balance
			// out the timings.
			double gd = (atan(sin((((((((((((((((M_PI/cos((x/((((0.53-y)-M_PI)*M_E)/y))))
			    +2.51)+x)-0.54)/0.98)+y)*y)+M_E)/x)+y)+x)+y)+M_PI)/M_E)+x)))*2.77);
			if (errorflag)
				break;
			if (fabs (ret - gd) > 0.0001)
				break;
		}

		uint64_t timeEnd = Private::timerTime ();
		
		uint64_t frequency = Private::timerFrequency ();
		uint64_t delta = timeEnd - timeStart;
		double seconds = (double)delta / (double)frequency;
		std::string res = boost::str (
			boost::format ("Compiled C++ (comparison): %1% seconds (%2% ticks)\n") %
			seconds % delta);
		
		printf ("%s", res.c_str ());
		
		const char *backendName;
		if (bestBackend == BACKEND_MUPARSER)
			backendName = "muParser";
#ifdef HAVE_LLVM
		else if (bestBackend == BACKEND_LLVM)
			backendName = "LLVM";
#endif
#ifdef HAVE_LIBJIT
		else if (bestBackend == BACKEND_LIBJIT)
			backendName = "libjit";
#endif

		printf ("\nFastest backend: %s\n\n", backendName);
	}

	if (setAsDefault)
		Private::defaultBackend = bestBackend;
		
	// Release the signals
	signal (SIGABRT, SIG_DFL);
	signal (SIGFPE, SIG_DFL);
	signal (SIGILL, SIG_DFL);
	signal (SIGSEGV, SIG_DFL);

	return bestBackend;
}

};
