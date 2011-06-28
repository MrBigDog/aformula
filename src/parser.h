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
/// @file parser.h
/// @brief Definition of the @c Parser class.

#ifndef PARSER_H__
#define PARSER_H__

#include <string>
#include <vector>
#include <boost/format.hpp>
#include <math.h>

#include <config.h>

namespace AFormula
{

namespace Private
{
class ExprAST;


/// @class Parser
/// @brief Class which parses a string formula into an abstract
/// syntax tree.
///
/// This class keeps track of registering variables and parsing a
/// formula into the various @c ExprAST classes.
class Parser
{
public:

	/// @brief Clear registered variables.
	void clearVariables ();

	/// @brief Set a variable to a given pointer.
	///
	/// @param[in] name Name of the variable to be set.
	/// @param[in] pointer Pointer to the double value for this variable.
	/// @return True if the variable could be properly registered, false
	/// otherwise.
	///
	/// This function registers a variable into an internal list kept
	/// by the parser.  This list is used to create @c VariableExprAST
	/// classes when variable references are found in the formula
	/// string.
	bool setVariable (const std::string &name, double *pointer);
	
private:

	/// @brief Pretty error message parsing.
	///
	/// @param[in] err Base message for error.
	///
	/// This function sets the string returned by @c Formula::errorString
	/// to a consistently formatted parser error.
	void error (const std::string &err) const;

	/// @brief Pretty error message parsing from a Boost Format object.
	///
	/// @param[in] fmt Base message for error.
	///
	/// This function sets the string returned by @c Formula::errorString
	/// to a consistently formatted parser error.
	inline void error (const boost::format &fmt) const
	{ error (boost::str (fmt)); }

	/// @brief Pretty-print the current token.
	///
	/// @return A nicely formatted representation of the current token
	/// (stored in @c currentToken, @c numToken, and @c strToken).
	std::string formatToken () const;
	

	//
	// Functions, constants, operators, and variables
	//
	
	/// @struct Function
	/// @brief Details of a hard-coded function identifier.
	///
	/// Our accepted functions are hard-coded at compile-time as a
	/// constant array of these structures.
	struct Function
	{
		/// @brief Name of this function.
		const char *name;
		/// @brief Number of arguments this function takes.
		unsigned int numArgs;
	};

	/// @brief Number of functions.
	static const int NUM_FUNCTIONS = 23;
	/// @brief List of hard-coded functions.
	static const Function functions[NUM_FUNCTIONS];

	/// @struct Constant
	/// @brief Details of a hard-coded mathematical constant.
	///
	/// Our accepted mathematical constants are hard-coded at
	/// compile-time as a constant array of these structures.
	struct Constant
	{
		/// @brief Name of this constant.
		const char *name;
		/// @brief The mathematical constant.
		double val;
	};
	
	/// @brief Number of constants.
	static const int NUM_CONSTANTS = 2;
	/// @brief List of hard-coded constants.
	static const Constant constants[NUM_CONSTANTS];
	
	/// @struct Operator
	/// @brief Details of a hard-coded binary operator.
	///
	/// Our accepted binary operators are hard-coded at compile-time
	/// as a constant array of these structures.
	struct Operator
	{
		/// @brief String for this binary operator ("=", "<", etc.).
		const char *name;
		/// @brief Precedence of this operator for order-of-operations.
		int precedence;
	};

	/// @brief Number of binary operators.
	static const int NUM_OPERATORS = 12;
	/// @brief List of binary operators.
	static const Operator operators[NUM_OPERATORS];
	
	/// @struct Variable
	/// @brief Details of a user-registered variable.
	struct Variable
	{
		/// @brief Name of this variable ("x", "y", etc.).
		std::string name;
		/// @brief Pointer to the double value which this variable
		/// represents.
		double *pointer;
	};

	/// @brief List of currently-registered variables.
	std::vector<Variable> variables;
	
	
	//
	// Token parsing
	//
	
	/// @brief Types of tokens returned by the token parser.
	enum
	{
		/// @brief Bad token (none of the below).
		TOKEN_BAD = 0,
		/// @brief End of string.
		TOKEN_END,
		/// @brief Function-name string.
		TOKEN_IDENTIFIER_FUNCTION,
		/// @brief Constant-name string.
		TOKEN_IDENTIFIER_CONSTANT,
		/// @brief Variable-name string.
		TOKEN_IDENTIFIER_VARIABLE,
		/// @brief Binary operator.
		TOKEN_OPERATOR,
		/// @brief Constant number.
		TOKEN_NUMBER,
		/// @brief Open parenthesis.
		TOKEN_PAREN_OPEN,
		/// @brief Close parenthesis.
		TOKEN_PAREN_CLOSE,
		/// @brief Comma (for function argument lists).
		TOKEN_COMMA
	};


	/// @brief String format token.
	///
	/// If @c currentToken is anything but @c TOKEN_END, @c TOKEN_BAD,
	/// or @c TOKEN_NUMBER, this variable will hold a string representation
	/// of the token.
	std::string strToken;

	/// @brief Numerical-format token.
	///
	/// If @c currentToken is @c TOKEN_NUMBER, this variable will hold a
	/// @c double version of the token.
	double numToken;

	/// @brief Type of current token (TOKEN_*).
	int currentToken;

	
	/// @brief The complete formula which is being parsed.
	std::string formula;
	
	/// @brief The remaining parts of the formula to be parsed.
	///
	/// This string gets shorter as the token parser consumes tokens out of
	/// the buffer.
	std::string parseBuffer;

	/// @brief Get a token from the parse buffer.
	/// @return The token type (@c TOKEN_*).
	///
	/// This function is not called directly -- we use @c getNextToken to
	/// store the results into the @c currentToken variable.
	int getToken ();

	/// @brief Get the next token, updating @c currentToken.
	/// @return The token type (@c TOKEN_*).
	///
	/// This function updates @c currentToken, @c strToken, and @c numToken
	/// to the next token in the parsing stream.
	///
	/// @note Call this instead of @c getToken()!
	int getNextToken ();

	
	/// @brief Get the type of a string identifier.
	///
	/// @param[in] ident The identifier to be checked.
	/// @return The identifer type (@c TOKEN_IDENT_*) or @c TOKEN_BAD.
	///
	/// This function classifies a generic string identifier into the
	/// @c TOKEN_IDENT_* categories.  If the identifier doesn't match any
	/// of the registered variables, functions, constants, or operators,
	/// @c TOKEN_BAD is returned.
	int getIdentifierType (const std::string &ident) const;


	//
	// Parse tokens into expression objects
	//

	/// @brief Parse a constant number into an @c ExprAST.
	/// @return A new @c NumberExprAST corresponding to @c numToken, or
	/// @c NULL on failure.
	ExprAST *parseNumberExpr ();
	
	/// @brief Parse an open parenthesis into an @c ExprAST.
	/// @return A new @c ExprAST corresponding to the contents of the
	/// parenthesis-expression, or @c NULL on failure.
	ExprAST *parseOpenParenExpr ();
	
	/// @brief Parse a function identifier into an @c ExprAST.
	/// @return A new @c CallExprAST corresponding to the correct function
	/// call, or @c NULL on failure.
	ExprAST *parseFunctionIdentifierExpr ();
	
	/// @brief Parse a constant-identifier into an @c ExprAST.
	/// @return A new @c NumberExprAST corresponding to the constant 
	/// identifier in @c strToken, or @c NULL on failure.
	ExprAST *parseConstantIdentifierExpr ();
	
	/// @brief Parse a variable-identifier into an @c ExprAST.
	/// @return A new @c VariableExprAST corresponding to the variable
	/// identifier in @c strToken, or @c NULL on failure.
	ExprAST *parseVariableIdentifierExpr ();
	
	/// @brief Parse a constant number into an @c ExprAST.
	/// @return A new @c NumberExprAST corresponding to @c numToken, or
	/// @c NULL on failure.
	ExprAST *parseUnaryMinusExpr ();
	
	/// @brief Parse a primary expression into an @c ExprAST.
	/// @return A new @c ExprAST corresponding to a primary expression, or
	/// @c NULL on failure.
	///
	/// A "primary expression" is anything which could be the left-hand
	/// side of a binary operator.
	ExprAST *parsePrimary ();

	/// @brief Parse a binary-operator expression into an @c ExprAST.
	/// @return A new @c BinaryExprAST corresponding to the current
	/// binary expression, or @c NULL on failure.
	///
	/// This function is called when we have already parsed a primary
	/// expression (the left-hand side of the operator), and @c currentToken
	/// is @c TOKEN_OPERATOR.
	ExprAST *parseBinOpRHS (int exprPrecedence, ExprAST *LHS);

	
	/// @brief Parse a complete expression.
	/// @return An @c ExprAST corresponding to a complete expression, or
	/// @c NULL on failure.
	///
	/// A complete expression is an LHS (a primary expression), optionally
	/// followed by a binary operator and a bin-op RHS.
	ExprAST *parseExpression ();

public:
	/// @brief Parse a complete formula string.
	/// @return An @c ExprAST corresponding to the compelte expression, or
	/// @c NULL on failure.
	///
	/// This function parses a complete formula into an expression tree.
	/// This is the primary entry point for the @c Parser class.
	///
	/// If a @c NULL value is returned, the function did not parse.  A fairly
	/// informative error message will be stored in @c Formula::errorString,
	/// suitable for display to the user.
	ExprAST *parseString (const std::string &f);
};


};
};


#endif /* PARSER_H__ */

// Local Variables:
// mode: c++
// End:
