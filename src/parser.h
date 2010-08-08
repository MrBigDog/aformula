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
#include <boost/format.hpp>
#include <math.h>

#include <config.h>

#include "parsetree.h"

namespace AFormula
{

namespace Private
{
extern std::string errorMessage;


template<typename T>
class Parser
{
public:

	void clearVariables ()
	{
		variables.clear ();
	}

	bool setVariable (const std::string &name, double *pointer)
	{
		// If this name is already some kind of identifier, you can't
		// register such a variable
		int type = getIdentifierType (name);
		
		if (type != 0)
		{
			std::string str;
			
			if (type == TOKEN_IDENTIFIER_FUNCTION)
				str = "function";
			else if (type == TOKEN_IDENTIFIER_CONSTANT)
				str = "mathematical constant";
			else
				str = "variable";
			
			error (boost::format ("Cannot register variable %1%, "
			                      "a %2% with this name already exists!") %
			       name % str);
			return false;
		}
		
		Variable var;
		
		var.name = name;
		var.pointer = pointer;
		
		variables.push_back (var);
		return true;
	}

private:

	//
	// Nice error message parsing
	//

	void error (const std::string &err) const
	{
		std::string message;
		
		// If we're parsing, we'll work with the formula
		if (formula.length ())
		{
			// Figure out what character we're near
			int charIndex = formula.length () - parseBuffer.length () - 1;
			
			// Format a nice error string
			message = boost::str (boost::format ("Parser Error (around character %1%): %2%")
			                      % charIndex % err);
		}
		else
			message = boost::str (boost::format ("Parser Error: %1%") % err);
		
		errorMessage = message;
	}
	
	inline void error (const boost::format &fmt) const
	{ error (boost::str (fmt)); }

	// Utility for error messages: format the details of the current token
	static const char *tokenStrings[];
	std::string formatToken () const
	{
		// Mark up identifiers and operators with their corresponding string
		if (currentToken >= TOKEN_IDENTIFIER_FUNCTION &&
		    currentToken <= TOKEN_OPERATOR)
			return boost::str (boost::format ("%1% (\"%2%\")") %
			                   tokenStrings[currentToken] % strToken);
		
		// Mark up numbers with their number
		if (currentToken == TOKEN_NUMBER)
			return boost::str (boost::format ("%1% (%2%)") %
			                   tokenStrings[currentToken] % numToken);
		
		// Everything else is just the token name
		return std::string (tokenStrings[currentToken]);
	}


	//
	// Our accepted function, constant, and binary operator names are
	// hard-coded at compile time.
	//

	struct Function
	{
		const char *name;
		int numArgs;
	};

	static const int NUM_FUNCTIONS = 22;
	static const Function functions[NUM_FUNCTIONS];

	static const char *constantNames[];

	struct Operator
	{
		const char *name;
		int precedence;
	};

	static const int NUM_OPERATORS = 12;
	static const Operator operators[NUM_OPERATORS];
		
	// Variable registration
	struct Variable
	{
		std::string name;
		double *pointer;
	};

	std::vector<Variable> variables;

	
	//
	// Token parsing
	//
	
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

	// The full parsed formula
	std::string formula;
	
	// What's left of the string being parsed
	std::string parseBuffer;

	// Get another token out of the parse buffer
	int getToken ()
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

	int getNextToken ()
	{
		return (currentToken = getToken ());
	}

	// Get the type of an identifier
	int getIdentifierType (const std::string &ident) const
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
		
		typename std::vector<Variable>::const_iterator iter;
		for (iter = variables.begin () ; iter != variables.end () ; ++iter)
		{
			if ((*iter).name == ident)
				return TOKEN_IDENTIFIER_VARIABLE;
		}
		
		return TOKEN_BAD;
	}


	//
	// Parse tokens into expression objects
	//
	
	ExprAST<T> *parseNumberExpr ()
	{
		ExprAST<T> *ret = new NumberExprAST<T> (numToken);
		
		// Eat the number
		getNextToken ();
		
		return ret;
	}
	
	ExprAST<T> *parseOpenParenExpr ()
	{
		// Eat '('
		getNextToken ();
		
		// Parse a complete expression
		ExprAST<T> *expr = parseExpression ();
		if (!expr)
			return NULL;
		
		// Make sure that worked
		if (currentToken != TOKEN_PAREN_CLOSE)
		{
			error ("Expected ')' after '('!");
			return NULL;
		}
		
		// Eat ')'
		getNextToken ();
		
		// Return the whole thing
		return expr;
	}
	
	ExprAST<T> *parseFunctionIdentifierExpr ()
	{
		std::string function (strToken);
		getNextToken ();
		
		if (currentToken != TOKEN_PAREN_OPEN)
		{
			error (boost::format ("Call to function %1% without following opening parenthesis!")
			       % function);
			return NULL;
		}
		getNextToken ();
		
		std::vector<ExprAST<T> *> args;
		if (currentToken != TOKEN_PAREN_CLOSE)
		{
			while (1)
			{
				ExprAST<T> *arg = parseExpression ();
				if (!arg)
					return NULL;
				args.push_back (arg);
				
				if (currentToken == TOKEN_PAREN_CLOSE)
					break;
				if (currentToken != TOKEN_COMMA)
				{
					error (boost::format ("Expected ')' or ',' in argument list to function %1%!")
					       % function);
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
					error (boost::format ("Not enough arguments for function %1% (%2%, expecting %3%)!")
					       % function % args.size () % functions[i].numArgs);
					return NULL;
				}
				else if (args.size () > functions[i].numArgs)
				{
					error (boost::format ("Too many arguments for function %1% (%2%, expecting %3%)!")
					       % function % args.size () % functions[i].numArgs);
					return NULL;
				}
			}
		}
		
		// Eat the ')'
		getNextToken ();
		
		return new CallExprAST<T> (function, args);
	}
	
	ExprAST<T> *parseConstantIdentifierExpr ()
	{
		std::string name (strToken);
		getNextToken ();
		
		if (name == "pi")
			return new NumberExprAST<T> (M_PI);
		else if (name == "e")
			return new NumberExprAST<T> (M_E);
		else
		{
			error (boost::format ("Internal Error: Attempted to treat %1% "
			                      "as a constant, though it is not.  "
			                      "Report this as a bug to <" PACKAGE_BUGREPORT ">!")
			       % name);
			return NULL;
		}
	}
	
	ExprAST<T> *parseVariableIdentifierExpr ()
	{
		std::string name (strToken);
		getNextToken ();
		
		// Find this in the map
		double *ptr = NULL;
		
		typename std::vector<Variable>::const_iterator iter;
		for (iter = variables.begin () ; iter != variables.end () ; ++iter)
		{
			if ((*iter).name == name)
			{
				ptr = (*iter).pointer;
				break;
			}
		}
		
		if (iter == variables.end () || ptr == NULL)
		{
			error (boost::format ("Internal Error: Attempted to treat %1% "
			                      "as a variable, though it is not.  "
			                      "Report this as a bug to <" PACKAGE_BUGREPORT ">!")
			       % name);
			return NULL;
		}
		
		return new VariableExprAST<T> (name, ptr);
	}
	
	ExprAST<T> *parseUnaryMinusExpr ()
	{
		getNextToken ();
		ExprAST<T> *child = parseExpression ();
		if (!child)
			return NULL;
		return new UnaryMinusExprAST<T> (child);
	}
	
	ExprAST<T> *parsePrimary ()
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
			error (boost::format ("Expecting an expression, got %1% instead!") %
			       formatToken ());
			return NULL;
		}
	}
	
	ExprAST<T> *parseBinOpRHS (int exprPrecedence, ExprAST<T> *LHS)
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
				error (boost::format ("Attempting to parse the RHS of a binary operator, "
				                      "and got %1%!") % formatToken ());
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
			ExprAST<T> *RHS = parsePrimary ();
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
			LHS = new BinaryExprAST<T> (binOp, LHS, RHS);
			
			// And loop back to the beginning
		}
	}
	

	// Parse a complete expression
	ExprAST<T> *parseExpression ()
	{
		ExprAST<T> *LHS = parsePrimary ();
		if (!LHS)
			return NULL;
		
		return parseBinOpRHS (0, LHS);
	}

public:

	ExprAST<T> *parseString (const std::string &f)
	{
		formula = parseBuffer = f;
		getNextToken ();
		
		ExprAST<T> *result = parseExpression ();
		
		// If there's any junk left over after an otherwise
		// successful parse, there's an error
		if (result && (currentToken != TOKEN_END || parseBuffer != ""))
		{
			error ("Parsed a complete expression, but content still remains in the formula!");
			delete result;
			
			return NULL;
		}
		
		return result;
	}
};


template<typename T>
const char *Parser<T>::tokenStrings[] =
{
	"an invalid token",
	"end-of-formula",
	"a function name",
	"a constant name",
	"a variable name",
	"an operator",
	"a number",
	"an open parenthesis",
	"a close parenthesis",
	"a comma"
};

template<typename T>
const typename Parser<T>::Function Parser<T>::functions[NUM_FUNCTIONS] =
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

template<typename T>
const char *Parser<T>::constantNames[] =
{
	"pi", "e", NULL
};

template<typename T>
const typename Parser<T>::Operator Parser<T>::operators[NUM_OPERATORS] =
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


};
};

#endif /* PARSER_H__ */

// Local Variables:
// mode: c++
// End:
