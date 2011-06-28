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
/// @file muparserformula.h
/// @brief Definition of the @c MuParserFormula class.

#ifndef MUPARSERFORMULA_H__
#define MUPARSERFORMULA_H__

#include <muParser.h>

namespace AFormula
{

namespace Private
{

/// @brief muParser formula backend.
///
/// This class implements formula parsing and solving essentially as a
/// pass-through to the corresponding interface elements of muParser.
class MuParserFormula : public Formula
{
public:
    MuParserFormula();
	virtual ~MuParserFormula () { }
	
	virtual bool setExpression (const std::string &str);
	virtual std::string expression () const;

	virtual bool setVariable (const std::string &variable, double *pointer);

	virtual double evaluate ();

private:
	/// @brief muParser formula object.
	mu::Parser muParser;
};

};

};


#endif /* MUPARSERFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
