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
/// @file timer.h
/// @brief Definition of private timer functions.

#include <stdint.h>

#ifndef TIMER_H__
#define TIMER_H__

namespace AFormula
{

namespace Private
{

/// @brief Return frequency of high-resolution native timer.
/// @return Frequency of timer, in seconds.
///
/// We need a platform-specific, high-resolution timer in order to
/// test which formula-compilation backend performs the fastest at
/// runtime.  This function returns that timer's frequency, in Hz.
/// (Execute <tt>timerTime() / timerFrequency()</tt> to get the
/// elapsed time in seconds.)
extern uint64_t timerFrequency ();

/// @brief Return current high-resolution system time.
/// @return Elapsed time from arbitrary basis, in units of @c
/// timerFrequency.
///
/// This function returns a system-dependent, high-precision elapsed
/// time value in units of @c timerFrequency.
extern uint64_t timerTime ();


};
};



#endif /* TIMER_H__ */

// Local Variables:
// mode: c++
// End:
