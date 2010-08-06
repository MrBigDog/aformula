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
#include <stdlib.h>
#include <math.h>
#include <aformula.h>
#include "parser.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;

namespace Parser
{

//
// Our accepted function, constant, and binary operator names are
// hard-coded at compile time.
//

static const char *functionNames[] =
{
	"sin", "cos", "tan", "asin", "acos", "atan",
	"sinh", "cosh", "tanh", "asinh", "acosh", "atanh",
	"log2", "log10", "log", "ln", "exp", "sqrt",
	"sign", "rint", "abs",
	"if", NULL
};

static const char *constantNames[] =
{
	"pi", "e", NULL
};

struct Operator
{
	const char *name;
	int precedence;
};

#define NUM_OPERATORS 12
static const Operator operators[NUM_OPERATORS] =
{
	{ "=", 1 },
	{ "<=", 10 },
	{ ">=", 10 },
	{ "!=", 10 },
	{ "==", 10 },
	{ "<", 10 },
	{ ">", 10 },
	{ "+", 20 },
	{ "-", 20 },
	{ "*", 30 },
	{ "/", 30 },
	{ "^", 40 }
};


//
// The variables, however, are registered on the fly.
//

struct Variable
{
	std::string name;
	double *pointer;
};

static std::vector<Variable> variables;


void clearVariables ()
{
	variables.clear ();
}

static int getIdentifierType (const std::string &ident);

bool setVariable (const std::string &name, double *pointer)
{
	// If this name is already some kind of identifier, you can't
	// register such a variable
	if (getIdentifierType (name) != 0)
	{
		errorMessage = "Cannot register a duplicate variable, or a variable with the same name as a built-in";
		return false;
	}
	
	Variable var;

	var.name = name;
	var.pointer = pointer;

	variables.push_back (var);
	return true;
}



//
// Token parsing
//

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
static std::string strToken;
static double numToken;
static int currentToken;

// What's left of the string being parsed
static std::string parseBuffer;


static ExprAST *ParseExpression ();


// What kind of identifier is this?
static int getIdentifierType (const std::string &ident)
{
	const char **ptr;

	ptr = functionNames;
	while (*ptr)
	{
		if (ident == *ptr)
			return TOKEN_IDENTIFIER_FUNCTION;
		++ptr;
	}

	ptr = constantNames;
	while (*ptr)
	{
		if (ident == *ptr)
			return TOKEN_IDENTIFIER_CONSTANT;
		++ptr;
	}

	std::vector<Variable>::iterator iter;
	for (iter = variables.begin () ; iter != variables.end () ; ++iter)
	{
		if ((*iter).name == ident)
			return TOKEN_IDENTIFIER_VARIABLE;
	}

	return TOKEN_BAD;
}


// Consume one more token from the string (return token type)
static int getToken ()
{
	if (!parseBuffer.length ())
		return TOKEN_END;
		
	// Eat whitespace
	while (isspace (parseBuffer[0]))
		parseBuffer.erase (0, 1);

	// If the next thing is in <>=!+-*/^, it's an operator
	static const std::string operatorChars ("<>=!+-*/^");
	if (operatorChars.find_first_of (parseBuffer[0]) != std::string::npos)
	{
		strToken.erase ();
				
		while (parseBuffer.length () &&
		       operatorChars.find_first_of (parseBuffer[0]) != std::string::npos)
		{
			strToken += parseBuffer[0];
			parseBuffer.erase (0,1);
		}

		for (int i = 0 ; i < NUM_OPERATORS ; i++)
		{
			if (strToken == operators[i].name)
				return TOKEN_OPERATOR;
		}
		return TOKEN_BAD;
	}
	
	// If the next thing begins with a letter, it's some kind of
	// identifier
	if (isalpha (parseBuffer[0]))
	{
		strToken.erase ();
				
		while (parseBuffer.length () &&
		       isalpha (parseBuffer[0]))
		{
			strToken += parseBuffer[0];
			parseBuffer.erase (0,1);
		}

		return getIdentifierType (strToken);
	}

	// Neither operator nor identifier, try number
	bool haveDot = false;
	if (isdigit (parseBuffer[0]) || parseBuffer[0] == '.')
	{
		strToken.erase ();
				
		while (parseBuffer.length () &&
		       (isdigit (parseBuffer[0]) || parseBuffer[0] == '.'))
		{
			strToken += parseBuffer[0];

			// Two decimal points?
			if (parseBuffer[0] == '.' && haveDot)
				return TOKEN_BAD;
			if (parseBuffer[0] == '.')
				haveDot = true;

			parseBuffer.erase (0, 1);
		}

		// Convert the string token to a decimal
		const char *str = strToken.c_str ();
		char *endptr;
		numToken = strtod (str, &endptr);

		// Check for failure
		if (numToken == 0.0 && endptr == str)
			return TOKEN_BAD;
				
		return TOKEN_NUMBER;
	}

	// Syntactic glue that doesn't parse into the tree
	if (parseBuffer[0] == '(')
	{
		strToken = parseBuffer[0];
		parseBuffer.erase (0,1);
		return TOKEN_PAREN_OPEN;
	}
	
	if (parseBuffer[0] == ')')
	{
		strToken = parseBuffer[0];
		parseBuffer.erase (0,1);
		return TOKEN_PAREN_CLOSE;
	}

	if (parseBuffer[0] == ',')
	{
		strToken = parseBuffer[0];
		parseBuffer.erase (0,1);
		return TOKEN_COMMA;
	}
	
	// What could that be?
	return TOKEN_BAD;
}

static int getNextToken ()
{
	return (currentToken = getToken ());
}


//
// Parse tokens into expression objects
//

static ExprAST *ParseNumberExpr ()
{
	ExprAST *ret = new NumberExprAST (numToken);

	// Eat the number
	getNextToken ();

	return ret;
}

static ExprAST *ParseOpenParenExpr ()
{
	// Eat '('
	getNextToken ();

	// Parse a complete expression
	ExprAST *expr = ParseExpression ();
	if (!expr)
		return NULL;

	// Make sure that worked
	if (currentToken != TOKEN_PAREN_CLOSE)
	{
		errorMessage = "Parsing error: expected ')'";
		return NULL;
	}

	// Eat ')'
	getNextToken ();

	// Return the whole thing
	return expr;
}

static ExprAST *ParseFunctionIdentifierExpr ()
{
	std::string function (strToken);
	getNextToken ();

	if (currentToken != TOKEN_PAREN_OPEN)
	{
		errorMessage = "Parsing error: Function call without opening parenthesis following";
		return NULL;
	}
	getNextToken ();

	std::vector<ExprAST *> args;
	if (currentToken != TOKEN_PAREN_CLOSE)
	{
		while (1)
		{
			ExprAST *arg = ParseExpression ();
			if (!arg)
				return NULL;
			args.push_back (arg);

			if (currentToken == TOKEN_PAREN_CLOSE)
				break;
			if (currentToken != TOKEN_COMMA)
			{
				errorMessage = "Parsing error: Expected ')' or ',' in argument list";
				return NULL;
			}
			getNextToken ();
		}
	}

	// Eat the ')'
	getNextToken ();

	return new CallExprAST (function, args);
}

static ExprAST *ParseConstantIdentifierExpr ()
{
	std::string name (strToken);
	getNextToken ();

	if (name == "pi")
		return new NumberExprAST (M_PI);
	else if (name == "e")
		return new NumberExprAST (M_E);
	else
	{
		errorMessage = "Parsing error: Somehow wound up with an invalid constant name";
		return NULL;
	}
}

static ExprAST *ParseVariableIdentifierExpr ()
{
	std::string name (strToken);
	getNextToken ();
	return new VariableExprAST (name);
}

static ExprAST *ParseUnaryMinusExpr ()
{
	getNextToken ();
	ExprAST *child = ParseExpression ();
	if (!child)
		return NULL;
	return new UnaryMinusExprAST (child);
}

static ExprAST *ParsePrimary ()
{
	// At the top level, we have to have either an identifier of some kind,
	// a number, or an open paren.  We might also have a unary minus sign, handle
	// that specially right here.
	switch (currentToken)
	{
	case TOKEN_IDENTIFIER_FUNCTION:
		return ParseFunctionIdentifierExpr ();
	case TOKEN_IDENTIFIER_CONSTANT:
		return ParseConstantIdentifierExpr ();
	case TOKEN_IDENTIFIER_VARIABLE:
		return ParseVariableIdentifierExpr ();
	case TOKEN_NUMBER:
		return ParseNumberExpr ();
	case TOKEN_PAREN_OPEN:
		return ParseOpenParenExpr ();
	case TOKEN_OPERATOR:
		if (strToken == "-")
			return ParseUnaryMinusExpr ();
		// Fall through for any other operator
	default:
		errorMessage = "Parsing error: unknown token when expecting an expression";
		return NULL;
	}
}

static int getTokenPrecedence ()
{
	if (currentToken != TOKEN_OPERATOR)
		return -1;

	for (int i = 0 ; i < NUM_OPERATORS ; i++)
	{
		if (strToken == operators[i].name)
			return operators[i].precedence;
	}

	return -1;
}

static ExprAST *ParseBinOpRHS (int exprPrecedence, ExprAST *LHS)
{
	while (1)
	{
		// Get the precedence
		int tokenPrecedence = getTokenPrecedence ();

		// We're done if we run into an equivalent or lower-precedence binary
		// operator
		if (tokenPrecedence < exprPrecedence)
			return LHS;

		// Pull off the operator
		std::string binOp = strToken;
		getNextToken ();

		// Parse the primary after the operator
		ExprAST *RHS = ParsePrimary ();
		if (!RHS)
			return NULL;

		// We've now parsed a full binary operator pair, "A op B".  If the next
		// thing is a binary operator (which it should be, or it should be
		// nothing at all), we need to see whether we want "(A op B) op2 ..." or
		// "A op (B op2 ...)" by precedence rules.  Look ahead:
		int nextPrecedence = getTokenPrecedence ();
		if (tokenPrecedence < nextPrecedence)
		{
			// Next precedence is greater, we want "A op (B op2 ...)".  Do that by
			// parsing B op2 ... into a new RHS.
			RHS = ParseBinOpRHS (tokenPrecedence + 1, RHS);
			if (RHS == NULL)
				return NULL;
		}

		// Next precedence is lower, we want "(A op B) op2 ...", so make a new LHS
		LHS = new BinaryExprAST (binOp, LHS, RHS);

		// And loop back to the beginning
	}
}

		

static ExprAST *ParseExpression ()
{
	ExprAST *LHS = ParsePrimary ();
	if (!LHS)
		return NULL;

	return ParseBinOpRHS (0, LHS);
}


ExprAST *parseString (const std::string &formula)
{
	parseBuffer = formula;
	getNextToken ();
		
	return ParseExpression ();
}

};
};
};
