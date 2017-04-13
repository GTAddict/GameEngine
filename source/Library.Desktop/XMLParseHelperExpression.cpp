#include "pch.h"
#include "XMLParseHelperExpression.h"
#include "XMLParseHelperTable.h"
#include "Action.h"
#include "Entity.h"
#include "Expression.h"
#include "ActionExpression.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperExpression::StartElementHandler(const std::string& element, const HashMapType attributes)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == EXPRESSION_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				ActionExpression* actionExpression = sharedData->mScope->As<ActionExpression>();

				if (actionExpression == nullptr)
				{
					throw std::runtime_error("Expressions can only be children of ActionExpressions!");
				}

				HashMapType::Iterator expressionIt = attributes.Find(VALUE_IDENTIFIER);
				if (expressionIt != attributes.end())
				{
					Expression expression(expressionIt->second);
					actionExpression->SetExpression(std::move(expression));
				}

				return true;
			}

			return false;
		}

		bool XMLParseHelperExpression::EndElementHandler(const std::string& element)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == EXPRESSION_IDENTIFIER)
			{
				return true;
			}

			return false;
		}

		IXMLParseHelper* XMLParseHelperExpression::Clone()
		{
			return new XMLParseHelperExpression();
		}
	}
}