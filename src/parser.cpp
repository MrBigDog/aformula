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
#include "parsetree.h"

namespace AFormula
{

namespace Private
{

extern std::string errorMessage;


//
// Our accepted function, constant, and binary operator names are
// hard-coded at compile time.
//

struct Function
{
	const char *name;
	int numArgs;
};

#define NUM_FUNCTIONS 22
static const Function functions[NUM_FUNCTIONS] =
{
	{"sin", 1},
	{"cos", 1},
	{"tan", 1},
	{"asin", 1},
	{"acos", 1},
	{"atan", 1},
	{"sinh", 1},
	{"cosh", 1},
	{"tanh", 1},
	{"asinh", 1},
	{"acosh", 1},
	{"atanh", 1},
	{"log2", 1},
	{"log10", 1},
	{"log", 1},
	{"ln", 1},
	{"exp", 1},
	{"sqrt", 1},
	{"sign", 1},
	{"rint", 1},
	{"abs", 1},
	{"if", 3}
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

void Parser::clearVariables ()
{
	variables.clear ();
}

static int getIdentifierType (const std::string &ident);

bool Parser::setVariable (const std::string &name, double *pointer)
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


static ExprAST *ParseExpression ();


// What kind of identifier is this?
int Parser::getIdentifierType (const std::string &ident) const
{
	for (int i = 0 ; i < NUM_FUNCTIONS ; i++)
	{
		if (ident == functions[i].name)
			return TOKEN_IDENTIFIER_FUNCTION;
	}
	
	const char **ptr = constantNames;
	while (*ptr)
	{
		if (ident == *ptr)
			return TOKEN_IDENTIFIER_CONSTANT;
		++ptr;
	}

	std::vector<Variable>::const_iterator iter;
	for (iter = variables.begin () ; iter != variables.end () ; ++iter)
	{
		if ((*iter).name == ident)
			return TOKEN_IDENTIFIER_VARIABLE;
	}

	return TOKEN_BAD;
}



// Consume one more token from the string (return token type)
int Parser::getToken ()
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

// Implement a one-token read-ahead buffer
int Parser::getNextToken ()
{
	return (currentToken = getToken ());
}


//
// Parse tokens into expression objects
//

ExprAST *Parser::parseNumberExpr ()
{
	ExprAST *ret = new NumberExprAST (numToken);

	// Eat the number
	getNextToken ();

	return ret;
}

ExprAST *Parser::parseOpenParenExpr ()
{
	// Eat '('
	getNextToken ();

	// Parse a complete expression
	ExprAST *expr = parseExpression ();
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

ExprAST *Parser::parseFunctionIdentifierExpr ()
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
			ExprAST *arg = parseExpression ();
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

	// Look up expected number of arguments
	for (int i = 0 ; i < NUM_FUNCTIONS ; i++)
	{
		if (function == functions[i].name)
		{
			if (args.size () < functions[i].numArgs)
			{
				errorMessage = "Parsing error: Not enough arguments for function";
				return NULL;
			}
			else if (args.size () > functions[i].numArgs)
			{
				errorMessage = "Parsing error: Too many arguments for function";
				return NULL;
			}
		}
	}
		
	// Eat the ')'
	getNextToken ();

	return new CallExprAST (function, args);
}

ExprAST *Parser::parseConstantIdentifierExpr ()
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

ExprAST *Parser::parseVariableIdentifierExpr ()
{
	std::string name (strToken);
	getNextToken ();
	return new VariableExprAST (name);
}

ExprAST *Parser::parseUnaryMinusExpr ()
{
	getNextToken ();
	ExprAST *child = parseExpression ();
	if (!child)
		return NULL;
	return new UnaryMinusExprAST (child);
}

ExprAST *Parser::parsePrimary ()
{
	// At the top level, we have to have either an identifier of some kind,
	// a number, or an open paren.  We might also have a unary minus sign, handle
	// that specially right here.
	switch (currentToken)
	{
	case TOKEN_IDENTIFIER_FUNCTION:
		return parseFunctionIdentifierExpr ();
	case TOKEN_IDENTIFIER_CONSTANT:
		return parseConstantIdentifierExpr ();
	case TOKEN_IDENTIFIER_VARIABLE:
		return parseVariableIdentifierExpr ();
	case TOKEN_NUMBER:
		return parseNumberExpr ();
	case TOKEN_PAREN_OPEN:
		return parseOpenParenExpr ();
	case TOKEN_OPERATOR:
		if (strToken == "-")
			return parseUnaryMinusExpr ();
		// Fall through for any other operator
	default:
		errorMessage = "Parsing error: unknown token when expecting an expression";
		return NULL;
	}
}


ExprAST *Parser::parseBinOpRHS (int exprPrecedence, ExprAST *LHS)
{
	while (1)
	{
		// This should be either an operator, a close-paren, comma,
		// or the end of the formula.
		if (currentToken != TOKEN_OPERATOR &&
		    currentToken != TOKEN_PAREN_CLOSE &&
		    currentToken != TOKEN_COMMA &&
		    currentToken != TOKEN_END)
		{
			errorMessage = "Parsing error: found something unacceptable while parsing binop RHS";
			return NULL;
		}
		
		// Get the precedence
		int tokenPrecedence = -1;
		
		for (int i = 0 ; i < NUM_OPERATORS ; i++)
		{
			if (strToken == operators[i].name)
			{
				tokenPrecedence = operators[i].precedence;
				break;
			}
		}
		
		// We're done if we run into an equivalent or lower-precedence binary
		// operator (or, notably, something that's not an operator at all, like
		// the end of the formula)
		if (tokenPrecedence < exprPrecedence)
			return LHS;

		// Pull off the operator
		std::string binOp = strToken;
		getNextToken ();

		// Parse the primary after the operator
		ExprAST *RHS = parsePrimary ();
		if (!RHS)
			return NULL;

		// We've now parsed a full binary operator pair, "A op B".  If the next
		// thing is a binary operator (which it should be, or it should be
		// nothing at all), we need to see whether we want "(A op B) op2 ..." or
		// "A op (B op2 ...)" by precedence rules.  Look ahead:
		int nextPrecedence = -1;
		for (int i = 0 ; i < NUM_OPERATORS ; i++)
		{
			if (strToken == operators[i].name)
			{
				nextPrecedence = operators[i].precedence;
				break;
			}
		}
				
		if (tokenPrecedence < nextPrecedence)
		{
			// Next precedence is greater, we want "A op (B op2 ...)".  Do that by
			// parsing B op2 ... into a new RHS.
			RHS = parseBinOpRHS (tokenPrecedence + 1, RHS);
			if (RHS == NULL)
				return NULL;
		}

		// Next precedence is lower, we want "(A op B) op2 ...", so make a new LHS
		LHS = new BinaryExprAST (binOp, LHS, RHS);

		// And loop back to the beginning
	}
}

		

ExprAST *Parser::parseExpression ()
{
	ExprAST *LHS = parsePrimary ();
	if (!LHS)
		return NULL;

	return parseBinOpRHS (0, LHS);
}


ExprAST *Parser::parseString (const std::string &formula)
{
	parseBuffer = formula;
	getNextToken ();
		
	ExprAST *result = parseExpression ();

	// If there's any junk left over after an otherwise
	// successful parse, there's an error
	if (result && (currentToken != TOKEN_END || parseBuffer != ""))
	{
		errorMessage = "Parsing error: junk left after formula parsing";
		delete result;
		
		return NULL;
	}

	return result;
}

};
};
