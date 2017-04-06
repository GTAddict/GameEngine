#include "pch.h"
#include "ActionExpression.h"
#include "SList.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(ActionExpression);

		namespace ActionExpressionConstants
		{
			const std::string EXPRESSION_IDENTIFIER = "expression";
		}

		using namespace ActionExpressionConstants;

		void ActionExpression::SetExpression(Expression expression)
		{
			mExpression = expression;
		}

		void ActionExpression::Update(WorldState& worldState)
		{
			ENGINE_UNUSED(worldState);

			// First, replace all variables in expression with values
			SList<std::string>& expression = mExpression.GetExpression();
			for (std::string& token : expression)
			{
				if (!mExpression.IsOperator(token))
				{
					Datum* foundDatum = Search(token);
					if (foundDatum)
					{
						if (foundDatum->Type() == Datum::DatumType::Integer)
						{
							token = std::to_string(foundDatum->Get<std::int32_t>());
						}
						else if (foundDatum->Type() == Datum::DatumType::Float)
						{
							token = std::to_string(foundDatum->Get<float>());
						}
						else
						{
							throw std::invalid_argument("Expressions only supported on ints and floats.");
						}
					}
				}
			}

			// Now simply evaluate the expression.
			double result = mExpression.Compute();
			ENGINE_UNUSED(result);
		}
	}
}
