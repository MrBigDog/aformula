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
/// @file c_api.cpp
/// @brief Implementation of C API wrappers.

#include <aformula.h>
#include <config.h>

extern "C" {

int af_fastest_backend(int set_as_default, int print_timings)
{ return AFormula::Formula::fastestBackend((set_as_default != 0), (print_timings != 0)); }

aformula_t af_create_formula(int backend)
{ return (aformula_t *)AFormula::Formula::createFormula(backend); }

const char *af_formula_errstr(aformula_t formula)
{ return ((AFormula::Formula *)formula)->errorString().c_str(); }

int af_formula_setexpr(aformula_t formula, const char *expr)
{ return ((AFormula::Formula *)formula)->setExpression(expr); }

const char *af_formula_getexpr(aformula_t formula)
{ return ((AFormula::Formula *)formula)->expression().c_str(); }

int af_formula_setvariable(aformula_t formula, const char *variable, double *pointer)
{ return ((AFormula::Formula *)formula)->setVariable(variable, pointer) ? 1 : 0; }

double af_formula_evaluate(aformula_t formula)
{ return ((AFormula::Formula *)formula)->evaluate(); }

}
