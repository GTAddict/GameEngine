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
			if (!mbIsInitialized || !mpSharedData->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()))	return false;

			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (element == ACTION_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				if (!sharedData->mScope->Is(Entity::TypeIdClass()))
				{
					throw std::runtime_error("Actions can only be children of Entities!");
				}

				sharedData->mScope = &sharedData->mScope->As<Entity>()->CreateAction(attributes[CLASS_IDENTIFIER], attributes[NAME_IDENTIFIER]);
				return true;
			}

			return false;
		}

		bool XMLParseHelperAction::EndElementHandler(const std::string & element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()))	return false;

			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

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
