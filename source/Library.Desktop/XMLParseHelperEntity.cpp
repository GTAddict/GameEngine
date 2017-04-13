#include "pch.h"
#include "XMLParseHelperEntity.h"
#include "XMLParseHelperTable.h"
#include "Entity.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperEntity::StartElementHandler(const std::string& element, const HashMapType attributes)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == ENTITY_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Sector* sector = sharedData->mScope->As<Sector>();
				if (!sector)
				{
					throw std::runtime_error("Entities can only be children of sectors!");
				}

				sharedData->mScope = &sector->CreateEntity(attributes[CLASS_IDENTIFIER], attributes[NAME_IDENTIFIER]);
				return true;
			}

			return false;
		}

		bool XMLParseHelperEntity::EndElementHandler(const std::string & element)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == ENTITY_IDENTIFIER)
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

		IXMLParseHelper* XMLParseHelperEntity::Clone()
		{
			return new XMLParseHelperEntity();
		}
	}
}
