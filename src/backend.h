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
#ifndef BACKEND_H__
#define BACKEND_H__

namespace AFormula
{

namespace Private
{

struct FormulaBackend
{
	bool (*setExpression)(const std::string &str);
	std::string (*expression)();
	bool (*setVariable)(const std::string &variable, double *pointer);
	double (*evaluate)();
};

};

};


#endif /* BACKEND_H__ */

// Local Variables:
// mode: c++
// End:
