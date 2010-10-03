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
/// @file benchmark.cpp
/// @brief Implementation of @c Formula::fastestBackend and related utilities.

#include <aformula.h>
#include <config.h>
#include <math.h>
#include <limits.h>

#ifdef HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#ifdef HAVE_SYS_WAIT_H
#  include <sys/wait.h>
#endif
#include <unistd.h>

#include <boost/format.hpp>

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

}



int Formula::fastestBackend (bool setAsDefault, bool printTimings)
{
	int bestBackend = BACKEND_MUPARSER;
	int bestBackendTime = INT_MAX;
	
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

		// Open a pipe to pass data between the parent and child threads
		int fileDescriptors[2];
		if (pipe (fileDescriptors) == -1)
		{
			fprintf (stderr, "ERROR: Cannot create pipe for IPC in benchmark, aborting\n");
			return BACKEND_MUPARSER;
		}

		// We'll put the result here when we get it from the child process
		int timeResult;
						
		// Fork the actual benchmark into another process, so that if it crashes,
		// we don't bring down the whole system
		pid_t pid = fork ();
		if (pid == 0)
		{
			// Child process -- do the test		
			Formula *formula = Formula::createFormula (backend);
			if (!formula)
			{
				close (fileDescriptors[1]);
				exit (-1);
			}
						
			static double x;
			static double y;
			if (!formula->setVariable ("x", &x) || !formula->setVariable ("y", &y))
			{
				close (fileDescriptors[1]);
				exit (-1);
			}
						
			const char *str =
				"(atan(sin((((((((((((((((pi/cos((x/((((0.53-y)-pi)*e)/y))))"
				"+2.51)+x)-0.54)/0.98)+y)*y)+e)/x)+y)+x)+y)+pi)/e)+x)))*2.77)";
			if (!formula->setExpression (str))
			{
				close (fileDescriptors[1]);
				exit (-1);
			}
						
			uint64_t timeStart = Private::timerTime ();
			
			for (int i = 0 ; i < 500000 ; i++)
			{
				x = (double)i;
				y = x / 2;
				double ret = formula->evaluate ();
				double gd = (atan(sin((((((((((((((((M_PI/cos((x/((((0.53-y)-M_PI)*M_E)/y))))
			    +2.51)+x)-0.54)/0.98)+y)*y)+M_E)/x)+y)+x)+y)+M_PI)/M_E)+x)))*2.77);
				
				if (fabs (ret - gd) > 0.0001)
				{
					fprintf (stderr, "ERROR: Backend reported invalid result in benchmark, aborting test for this backend\n");
					close (fileDescriptors[1]);
					exit (-1);
				}
			}
			
			uint64_t timeEnd = Private::timerTime ();
			
			delete formula;

			// Return (timeEnd - timeStart) in microseconds.  This will only overflow if
			// an individual test takes more than six hours (!)
			uint64_t timeDelta = timeEnd - timeStart;
			double timeSeconds = (double)timeDelta / (double)Private::timerFrequency ();
			int timeUS = (int)(timeSeconds * 100000.0);

			// Pass data back down the pipe
			if (write (fileDescriptors[1], &timeUS, sizeof(int)) < (signed)sizeof(int))
			{
				fprintf (stderr, "ERROR: Cannot pass data back to parent in benchmark, aborting\n");
				close (fileDescriptors[1]);
				exit (-1);
			}
						
			// Bail
			close (fileDescriptors[1]);
			exit (0);
		}
		else if (pid < 0)
		{
			// Failed to fork, bail out with an error
			fprintf (stderr, "ERROR: Failed to fork() in backend testing, aborting\n");
			return BACKEND_MUPARSER;
		}
		else
		{
			// Parent process, first read from the pipe
			bool gotTime = true;
			if (read (fileDescriptors[0], &timeResult, sizeof(int)) < (signed)sizeof(int))
			{
				gotTime = false;
				break;
			}
									
			// Wait for child to terminate
			int status;
			waitpid (pid, &status, 0);
			bool success = false;
			
			if (WIFEXITED (status) && (WEXITSTATUS (status) == 0))
				success = true;

			// If this test failed, skip it
			if (!success || !gotTime)
				continue;
		}
		
		if (timeResult < bestBackendTime)
		{
			bestBackendTime = timeResult;
			bestBackend = backend;
		}

		if (printTimings)
		{
			double seconds = (double)timeResult / 100000.0;
			std::string res = boost::str (
				boost::format ("Backend %1% (%2%): %3% seconds\n") %
				backend % backendName % seconds);
			
			printf ("%s", res.c_str ());
		}
	}

	if (printTimings)
	{
		// Run a compiled C++ benchmark for comparison
		uint64_t timeStart = Private::timerTime ();
		
		for (int i = 0 ; i < 500000 ; i++)
		{
			double x = (double)i;
			double y = x / 2;
			double ret = Private::compiledCppBenchmark (x, y);

			// Fake the rest of what's in the inner loop, to balance
			// out the timings.
			double gd = (atan(sin((((((((((((((((M_PI/cos((x/((((0.53-y)-M_PI)*M_E)/y))))
			    +2.51)+x)-0.54)/0.98)+y)*y)+M_E)/x)+y)+x)+y)+M_PI)/M_E)+x)))*2.77);
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
		else
			backendName = "undefined?";

		printf ("\nFastest backend: %s\n\n", backendName);
	}

	if (setAsDefault)
		Private::defaultBackend = bestBackend;
		
	return bestBackend;
}

}
