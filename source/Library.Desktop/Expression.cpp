#include "pch.h"
#include "Expression.h"
#include <algorithm>
#include "Stack.h"
#include "SList.h"

namespace GameEngine
{
	namespace Library
	{
		Expression::Expression()
		{
		}

		SList<std::string> Expression::ConvertToRPN(SList<std::string>& tokens) const
		{
			SList<std::string> outputList;
			Stack<std::string> operatorStack;

			while (tokens.Size())
			{
				std::string currentToken = tokens.Front();
				tokens.PopFront();
				if (!IsOperator(currentToken))
				{
					outputList.PushBack(currentToken);
				}
				else if (IsFunctionOperator(currentToken))
				{
					operatorStack.Push(currentToken);
				}
				else if (currentToken == mEnumToTokenMap[Operators::OP_COMMA])
				{
					// Don't do anything here, just skip pushing comma.
				}
				else if (currentToken == mEnumToTokenMap[Operators::OP_LPAREN])
				{
					operatorStack.Push(currentToken);
				}
				else if (currentToken == mEnumToTokenMap[Operators::OP_RPAREN])
				{
					try
					{
						while (operatorStack.Top() != mEnumToTokenMap[Operators::OP_LPAREN])
						{
							outputList.PushBack(operatorStack.Top());
							operatorStack.Pop();
						}
						operatorStack.Pop();
					}
					catch (std::exception e)
					{
						throw std::runtime_error("Mismatched parentheses!");
					}
				}
				else if (IsOperator(currentToken))
				{
					while (operatorStack.Size() && IsOperator(operatorStack.Top())
						&& ((mTokenToAssocMap[currentToken] == Associativity::LEFT && mTokenToPrecedenceMap[currentToken] <= mTokenToPrecedenceMap[operatorStack.Top()])
						|| (mTokenToAssocMap[currentToken] == Associativity::RIGHT && mTokenToPrecedenceMap[currentToken] < mTokenToPrecedenceMap[operatorStack.Top()])))
					{
						outputList.PushBack(operatorStack.Top());
						operatorStack.Pop();
					}
					operatorStack.Push(currentToken);
				}
			}

			while (operatorStack.Size())
			{
				if (operatorStack.Top() == mEnumToTokenMap[Operators::OP_LPAREN])
				{
					throw std::runtime_error("Mismatched parentheses!");
				}

				outputList.PushBack(operatorStack.Top());
				operatorStack.Pop();
			}

			std::string concat;
			for (std::string s : outputList)
			{
				concat += s;
			}

			return outputList;
		}

		Expression::Expression(std::string expression)
		{
			ParseExpression(expression);
		}

		SList<std::string>& Expression::GetExpression()
		{
			return mParsedExpression;
		}

		double Expression::Compute()
		{
			Stack<double> outputStack;
			try
			{
				while (mParsedExpression.Size())
				{
					std::string token = mParsedExpression.Front();
					mParsedExpression.PopFront();
					if (!IsOperator(token))
					{
						outputStack.Push(std::stod(token));
					}
					else
					{
						std::uint32_t argCount = mTokenToArgCountMap[token];
						double arguments[2];
						for (std::uint32_t i = argCount; i-- > 0;)
						{
							arguments[i] = outputStack.Top();
							outputStack.Pop();
						}
						outputStack.Push(EvaluateFunction(token, arguments));
					}
				}
			}
			catch (const std::exception&)
			{
				throw std::exception("Grammar is not right.");
			}
			
			return outputStack.Top();
		}

		void Expression::ParseExpression(std::string expression)
		{
			// Remove whitespace.
			expression.erase(std::remove_if(expression.begin(), expression.end(), isspace), expression.end());

			SList<std::string> tokens;
			std::string::iterator itBegin = expression.begin();
			std::string::iterator itEnd = expression.end();
			std::string variable;

			while (itBegin != itEnd)
			{
				std::string token = TryReadNumber(itBegin, itEnd);
				if (token.empty())
				{
					token = TryReadOperator(itBegin, itEnd);
				}
				if (token.empty() && itBegin != itEnd)
				{
					variable += *itBegin;
				}

				if (token.length())
				{
					if (variable.length())
					{
						tokens.PushBack(variable);
						variable.clear();
					}

					tokens.PushBack(token);
					token.clear();
				}
				else if (itBegin != itEnd)
				{
					++itBegin;
				}
			}

			mParsedExpression = ConvertToRPN(tokens);
		}

		std::string Expression::TryReadNumber(std::string::iterator& currentIt, const std::string::iterator & endIt) const
		{
			std::string readDigit;
			while (currentIt != endIt && (isdigit(*currentIt) || *currentIt == '.'))
			{
				readDigit += *currentIt;
				++currentIt;
			}
			return readDigit;
		}

		std::string Expression::TryReadOperator(std::string::iterator& currentIt, const std::string::iterator & endIt) const
		{
			std::string::iterator originalIt = currentIt;
			std::string readOperator;
			while (currentIt != endIt && !isdigit(*currentIt))
			{
				readOperator += *currentIt;
				++currentIt;
				if (IsOperator(readOperator))
				{
					break;
				}
			}
			if (!IsOperator(readOperator))
			{
				currentIt = originalIt;
				readOperator.clear();
			}
			return readOperator;
		}

		double Expression::EvaluateFunction(const std::string op, double* arguments)
		{
			double& a = arguments[0];
			double& b = arguments[1];

			switch (mTokenToEnumMap[op])
			{
			case GameEngine::Library::Expression::Operators::OP_PLUS:		return a + b;
			case GameEngine::Library::Expression::Operators::OP_MINUS:		return a - b;
			case GameEngine::Library::Expression::Operators::OP_MULTIPLY:	return a * b;
			case GameEngine::Library::Expression::Operators::OP_DIVIDE:		return a / b;
			case GameEngine::Library::Expression::Operators::OP_EXPONENT:	return pow(a, b);
			case GameEngine::Library::Expression::Operators::OP_SIN:		return sin(a);
			case GameEngine::Library::Expression::Operators::OP_COS:		return cos(a);
			case GameEngine::Library::Expression::Operators::OP_TAN:		return tan(a);
			case GameEngine::Library::Expression::Operators::OP_ACOS:		return acos(a);
			case GameEngine::Library::Expression::Operators::OP_ASIN:		return asin(a);
			case GameEngine::Library::Expression::Operators::OP_ATAN:		return atan(a);
			case GameEngine::Library::Expression::Operators::OP_POW:		return pow(a, b);
			case GameEngine::Library::Expression::Operators::OP_LOG:		return log(a);
			case GameEngine::Library::Expression::Operators::OP_SQRT:		return sqrt(a);
			case GameEngine::Library::Expression::Operators::OP_INVSQRT:	return 1 / sqrt(a);
			case GameEngine::Library::Expression::Operators::OP_EQUALITY:	return a == b;
			case GameEngine::Library::Expression::Operators::OP_LTHAN:		return a < b;
			case GameEngine::Library::Expression::Operators::OP_GTHAN:		return a > b;
			case GameEngine::Library::Expression::Operators::OP_LOGIC_OR:	return a || b;
			case GameEngine::Library::Expression::Operators::OP_NOT:		return !a;
			default:	throw std::invalid_argument("Undefined operator!");
			}
		}

		bool Expression::IsOperator(const std::string& token) const
		{
			return mTokenToEnumMap.ContainsKey(token);
		}

		bool Expression::IsFunctionOperator(const std::string& token) const
		{
			return mTokenToEnumMap.ContainsKey(token)
				&& token.length() > 1
				&& token != mEnumToTokenMap[Operators::OP_EQUALITY]
				&& token != mEnumToTokenMap[Operators::OP_LOGIC_OR];
		}
	}
}