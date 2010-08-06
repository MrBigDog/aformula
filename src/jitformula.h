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
#ifndef JITFORMULA_H__
#define JITFORMULA_H__

namespace AFormula
{

namespace Private
{

namespace Parser
{
class ExprAST;
};

class JITFormula : public Formula
{
public:
	JITFormula ();
	virtual ~JITFormula ();
		
	virtual bool setExpression (const std::string &str);
	virtual std::string expression () const;

	virtual bool setVariable (const std::string &variable, double *pointer);

	virtual double evaluate ();

protected:
	std::string expr;
	Parser::ExprAST *parseTree;	
};

};

};


#endif /* LLVMFORMULA_H__ */

// Local Variables:
// mode: c++
// End:
