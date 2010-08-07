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
#ifndef PARSER_H__
#define PARSER_H__

#include <string>
#include <vector>

namespace AFormula
{

namespace Private
{
class ExprAST;

class Parser
{
public:
	void clearVariables ();
	bool setVariable (const std::string &name, double *pointer);

	ExprAST *parseString (const std::string &formula);

private:

	// Variable registration
	struct Variable
	{
		std::string name;
		double *pointer;
	};

	std::vector<Variable> variables;

	// Token types
	enum
	{
		TOKEN_BAD = 0,
		TOKEN_END,
		TOKEN_IDENTIFIER_FUNCTION,
		TOKEN_IDENTIFIER_CONSTANT,
		TOKEN_IDENTIFIER_VARIABLE,
		TOKEN_OPERATOR,
		TOKEN_NUMBER,
		TOKEN_PAREN_OPEN,
		TOKEN_PAREN_CLOSE,
		TOKEN_COMMA
	};

	// These will be filled in if the token is an IDENT_* (strToken, operator)
	// or a NUMBER (numToken), respectively.
	std::string strToken;
	double numToken;
	int currentToken;

	// What's left of the string being parsed
	std::string parseBuffer;

	// Get another token out of the parse buffer
	int getToken ();
	int getNextToken ();

	// Get the type of an identifier
	int getIdentifierType (const std::string &ident) const;

	// Parsing for all the various sorts of expression pieces.
	ExprAST *parseNumberExpr ();
	ExprAST *parseOpenParenExpr ();
	ExprAST *parseFunctionIdentifierExpr ();
	ExprAST *parseConstantIdentifierExpr ();
	ExprAST *parseVariableIdentifierExpr ();
	ExprAST *parseUnaryMinusExpr ();
	ExprAST *parsePrimary ();
	ExprAST *parseBinOpRHS (int exprPrecedence, ExprAST *LHS);

	// Parse a complete expression
	ExprAST *parseExpression ();
};

};
};

#endif /* PARSER_H__ */

// Local Variables:
// mode: c++
// End:
