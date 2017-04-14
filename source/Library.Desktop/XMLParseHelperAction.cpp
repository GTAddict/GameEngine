#include "pch.h"
#include "XMLParseHelperAction.h"
#include "XMLParseHelperTable.h"
#include "Action.h"
#include "Entity.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperAction::StartElementHandler(const std::string& element, const HashMapType attributes)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == ACTION_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Entity* entity = sharedData->mScope->As<Entity>();

				if (!entity)
				{
					throw std::runtime_error("Actions can only be children of Entities!");
				}
				
				Action& action = entity->CreateAction(attributes[CLASS_IDENTIFIER], attributes[NAME_IDENTIFIER]);
				sharedData->mScope = &action;

				return true;
			}

			return false;
		}

		bool XMLParseHelperAction::EndElementHandler(const std::string& element)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == ACTION_IDENTIFIER)
			{
				if (sharedData->GetDepth() > 1)
				{
					assert(sharedData->mScope->GetParent() != nullptr);
					sharedData->mScope = sharedData->mScope->GetParent();
				}

				return true;
			}

			return false;
		}

		IXMLParseHelper* XMLParseHelperAction::Clone()
		{
			return new XMLParseHelperAction();
		}
	}
}
