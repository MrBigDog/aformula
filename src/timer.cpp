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

#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/time.h>
#endif

#include <stdint.h>
#include <limits.h>


namespace AFormula
{

namespace Private
{


//
// I hate this platform-specific hackery, but we have to get a sufficiently
// high-resolution timer on Win32, and this is the only way.
//
#ifdef _WIN32

uint64_t timerFrequency ()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency (&ticksPerSecond);
	return ticksPerSecond.QuadPart;
}

uint64_t timerTime ()
{
	LARGE_INTEGER ticks;
	QueryPerformanceCounter (&ticks);
	return ticks.QuadPart;
}

#else

uint64_t timerFrequency ()
{
	return 1000000;
}

uint64_t timerTime ()
{
	struct timeval tp;
	if (gettimeofday (&tp, NULL) != 0)
		return 0.0f;
	
	return tp.tv_sec * 1000000 + tp.tv_usec;
}

#endif

};
};
