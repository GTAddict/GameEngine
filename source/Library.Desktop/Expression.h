#pragma once
#include <string>
#include "HashMap.h"

namespace GameEngine
{
	namespace Library
	{
		template <typename T>
		class SList;

		/**
		*	\class	Expression
		*	\brief	This is a class that interprets
		*			infix notation, stores the RPN
		*			parse, and computes the result on
		*			demand.
		*/
		class Expression
		{

		private:

			/**
			*	\enum	Operators
			*	\brief	This enum defines the operators
			*			that can be parsed.
			*/
			enum class Operators
			{
				INVALID = -1,
				FIRST = 0,
				OP_PLUS = FIRST,
				OP_MINUS,
				OP_MULTIPLY,
				OP_DIVIDE,
				OP_EXPONENT,
				OP_SIN,
				OP_COS,
				OP_TAN,
				OP_ACOS,
				OP_ASIN,
				OP_ATAN,
				OP_POW,
				OP_LOG,
				OP_SQRT,
				OP_INVSQRT,
				OP_EQUALITY,
				OP_LTHAN,
				OP_GTHAN,
				OP_LOGIC_OR,
				OP_LPAREN,
				OP_RPAREN,
				OP_COMMA,
				OP_NOT,
				COUNT
			};

			/**
			*	\enum	Associativity
			*	\brief	This enum defines the possible
			*			associativities.
			*/
			enum class Associativity
			{
				INVALID,
				LEFT,
				RIGHT
			};

			/**
			*	\struct	TokenMashMapFunctor
			*	\brief	This struct, which inherits from the default
			*			HashMap provided HashFunctor, in order to
			*			provide a hash for Operator.
			*/
			struct TokenHashMapFunctor : public DefaultHashFunctor
			{
				template <typename T> std::uint32_t operator()(const T& key) const { return DefaultHashFunctor::operator()(key); }
				template <typename T> std::uint32_t operator()(const T* key) const { return DefaultHashFunctor::operator()(key); }

				template <> std::uint32_t operator()(const Operators& key)	const { return operator()(static_cast<std::int32_t>(key)); }
				template <> std::uint32_t operator()(const Operators* key)	const { THROW_IF_NULL(key); return operator()(*key); }
			};

			/* This maps each Operator to its string representation. */
			HashMap<Operators, std::string, TokenHashMapFunctor> mEnumToTokenMap =
			{
				{ Operators::OP_PLUS,		"+" },
				{ Operators::OP_MINUS,		"-" },
				{ Operators::OP_MULTIPLY,	"*" },
				{ Operators::OP_DIVIDE,		"/" },
				{ Operators::OP_EXPONENT,	"^" },
				{ Operators::OP_SIN,		"sin" },
				{ Operators::OP_COS,		"cos" },
				{ Operators::OP_TAN,		"tan" },
				{ Operators::OP_ACOS,		"acos" },
				{ Operators::OP_ASIN,		"asin" },
				{ Operators::OP_ATAN,		"atan" },
				{ Operators::OP_POW,		"pow" },
				{ Operators::OP_LOG,		"log" },
				{ Operators::OP_SQRT,		"sqrt" },
				{ Operators::OP_INVSQRT,	"invsqrt" },
				{ Operators::OP_EQUALITY,	"==" },
				{ Operators::OP_LTHAN,		"<" },
				{ Operators::OP_GTHAN,		">" },
				{ Operators::OP_LOGIC_OR,	"||" },
				{ Operators::OP_LPAREN,		"(" },
				{ Operators::OP_RPAREN,		")" },
				{ Operators::OP_COMMA,		"," },
				{ Operators::OP_NOT,		"!" }
			};

			/* This maps each string to its Operator entry. */
			HashMap<std::string, Operators, TokenHashMapFunctor> mTokenToEnumMap =
			{
				{ "+",			Operators::OP_PLUS },
				{ "-",			Operators::OP_MINUS },
				{ "*",			Operators::OP_MULTIPLY },
				{ "/",			Operators::OP_DIVIDE },
				{ "^",			Operators::OP_EXPONENT },
				{ "sin",		Operators::OP_SIN },
				{ "cos",		Operators::OP_COS },
				{ "tan",		Operators::OP_TAN },
				{ "acos",		Operators::OP_ACOS },
				{ "asin",		Operators::OP_ASIN },
				{ "atan",		Operators::OP_ATAN },
				{ "pow",		Operators::OP_POW },
				{ "log",		Operators::OP_LOG },
				{ "sqrt",		Operators::OP_SQRT },
				{ "invsqrt",	Operators::OP_INVSQRT },
				{ "==",			Operators::OP_EQUALITY },
				{ "<",			Operators::OP_LTHAN },
				{ ">",			Operators::OP_GTHAN },
				{ "||",			Operators::OP_LOGIC_OR },
				{ "(",			Operators::OP_LPAREN },
				{ ")",			Operators::OP_RPAREN },
				{ ",",			Operators::OP_COMMA },
				{ "!",			Operators::OP_NOT }
			};

			/* This maps each operator string to its precedence. */
			HashMap<std::string, std::uint32_t, TokenHashMapFunctor> mTokenToPrecedenceMap =
			{
				{ "+",			5 },
				{ "-",			5 },
				{ "*",			6 },
				{ "/",			6 },
				{ "^",			7 },
				{ "sin",		8 },
				{ "cos",		8 },
				{ "tan",		8 },
				{ "acos",		8 },
				{ "asin",		8 },
				{ "atan",		8 },
				{ "pow",		8 },
				{ "log",		8 },
				{ "sqrt",		8 },
				{ "invsqrt",	8 },
				{ "==",			4 },
				{ "<",			3 },
				{ ">",			3 },
				{ "||",			2 },
				{ "(",			0 },
				{ ")",			0 },
				{ ",",			1 },
				{ "!",			9 }
			};

			/* This maps each operator string to its associativity. */
			HashMap<std::string, Associativity, TokenHashMapFunctor> mTokenToAssocMap =
			{
				{ "+",			Associativity::LEFT },
				{ "-",			Associativity::LEFT },
				{ "*",			Associativity::LEFT },
				{ "/",			Associativity::LEFT },
				{ "^",			Associativity::RIGHT },
				{ "sin",		Associativity::LEFT },
				{ "cos",		Associativity::LEFT },
				{ "tan",		Associativity::LEFT },
				{ "acos",		Associativity::LEFT },
				{ "asin",		Associativity::LEFT },
				{ "atan",		Associativity::LEFT },
				{ "pow",		Associativity::LEFT },
				{ "log",		Associativity::LEFT },
				{ "sqrt",		Associativity::LEFT },
				{ "invsqrt",	Associativity::LEFT },
				{ "==",			Associativity::LEFT },
				{ "<",			Associativity::LEFT },
				{ ">",			Associativity::LEFT },
				{ "||",			Associativity::LEFT },
				{ "(",			Associativity::LEFT },
				{ ")",			Associativity::LEFT },
				{ ",",			Associativity::LEFT },
				{ "!",			Associativity::RIGHT }
			};

			/* This maps each operator string to the number of operands it takes. */
			HashMap<std::string, std::uint32_t> mTokenToArgCountMap =
			{
				{ "+",			2 },
				{ "-",			2 },
				{ "*",			2 },
				{ "/",			2 },
				{ "^",			2 },
				{ "sin",		1 },
				{ "cos",		1 },
				{ "tan",		1 },
				{ "acos",		1 },
				{ "asin",		1 },
				{ "atan",		1 },
				{ "pow",		2 },
				{ "log",		1 },
				{ "sqrt",		1 },
				{ "invsqrt",	1 },
				{ "==",			2 },
				{ "<",			2 },
				{ ">",			2 },
				{ "||",			2 },
				{ "!",			1 }
			};

			public:

			/**
			*	\brief				Default constructor. Does nothing.
			*/
									Expression();

			/**
			*	\brief				Parametrized constructor. You can pass
			*						in the infix expression to parse.
			*	\param expression	The expression to parse.
			*	\notes				We haven't marked this as explicit as
			*						a user could very well do something like
			*						Expression e = "sinx + 54";
			*/
									Expression(std::string expression);

			/**
			*	\brief				Returns the parsed RPN expression as a list.
			*	\return				The parsed RPN expression.
			*	\notes				Non-const as we want the user to modify this
			*						by replacing variables by actual values.
			*/
			SList<std::string>&		GetExpression();

			/**
			*	\brief				Actually evaluates the parsed expression.
			*	\return				The value of the evaluation.
			*/
			double					Compute();

			/**
			*	\brief				Checks whether the specified token is an
			*						operator or not. If it's not an operator
			*						or a number, it's a variable name.
			*	\param token		The token to check.
			*	\return				Whether the token is an operator.
			*/
			bool					IsOperator(const std::string& token) const;

		private:

			/**
			*	\brief				Actually parses the expression into RPN.
			*	\param expression	The expression to parse.
			*/
			void					ParseExpression(std::string expression);

			/**
			*	\brief				Checks whether the specified token is a
			*						function operator or not.
			*	\param token		The token to check.
			*/
			bool					IsFunctionOperator(const std::string& token) const;

			/**
			*	\brief				Tries to interpret the string beginning at
			*						the iterator as a number. Advances the iterator
			*						if a valid number is found.
			*	\param currentIt	The iterator to start looking from.
			*	\param endIt		The iterator to start looking at.
			*	\return				A string representing a number if found, an
			*						empty string otherwise.
			*/
			std::string				TryReadNumber(std::string::iterator& currentIt, const std::string::iterator& endIt) const;

			/**
			*	\brief				Tries to interpret the string beginning at
			*						the iterator as an operator. Advances the
			*						iterator if a valid operator is found.
			*	\param currentIt	The iterator to start looking from.
			*	\param endIt		The iterator to start looking at.
			*	\return				A string representing an operator if found, an
			*						empty string otherwise.
			*/
			std::string				TryReadOperator(std::string::iterator& currentIt, const std::string::iterator& endIt) const;

			/**
			*	\brief				Converts the specified tokens into RPN.
			*	\param tokens		The list of tokens to convert.
			*	\return				The list of converted tokens.
			*/
			SList<std::string>		ConvertToRPN(SList<std::string>& tokens) const;

			/**
			*	\brief				Performs the specified operation on the operands.
			*	\param op			The operation to perform.
			*	\param arguments	The array of operands.
			*	\return				The result of the evaluation.
			*/
			double					EvaluateFunction(const std::string op, double* arguments);

			SList<std::string>		mParsedExpression;		/**< This is the parsed expression that is stored for later evaluation. */
		};
	}
}