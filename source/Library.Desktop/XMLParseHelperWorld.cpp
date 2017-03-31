#include "pch.h"
#include "XMLParseHelperWorld.h"
#include "XMLParseHelperTable.h"
#include "World.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperWorld::StartElementHandler(const std::string & element, const HashMapType attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()))	return false;

			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (element == WORLD_IDENTIFIER)
			{
				if (sharedData->mScope == nullptr)
				{
					World* world = new World();
					sharedData->mScope = world;
					if (attributes.ContainsKey(NAME_IDENTIFIER))
					{
						world->SetName(attributes[NAME_IDENTIFIER]);
					}
				}
				else
				{
					throw std::runtime_error("Cannot have a world contained inside another!");
				}

				return true;
			}

			return false;
		}

		bool XMLParseHelperWorld::EndElementHandler(const std::string & element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()))	return false;

			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (element == WORLD_IDENTIFIER)
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

		IXMLParseHelper* XMLParseHelperWorld::Clone()
		{
			return new XMLParseHelperWorld();
		}
	}
}
