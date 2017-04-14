#include "pch.h"
#include "XMLParseHelperReaction.h"
#include "XMLParseHelperTable.h"
#include "Reaction.h"
#include "Entity.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperReaction::StartElementHandler(const std::string& element, const HashMapType attributes)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == REACTION_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Entity* entity = sharedData->mScope->As<Entity>();

				if (!entity)
				{
					throw std::runtime_error("Reactions can only be children of Entities!");
				}

				Reaction& reaction = entity->CreateReaction(attributes[CLASS_IDENTIFIER], attributes[NAME_IDENTIFIER]);
				sharedData->mScope = &reaction;

				return true;
			}

			return false;
		}

		bool XMLParseHelperReaction::EndElementHandler(const std::string& element)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == REACTION_IDENTIFIER)
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

		IXMLParseHelper* XMLParseHelperReaction::Clone()
		{
			return new XMLParseHelperReaction();
		}
	}
}