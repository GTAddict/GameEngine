#include "pch.h"
#include "XMLParseHelperSector.h"
#include "XMLParseHelperTable.h"
#include "World.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		using namespace TableParserConstants;

		bool XMLParseHelperSector::StartElementHandler(const std::string & element, const HashMapType attributes)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == SECTOR_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				World* world = sharedData->mScope->As<World>();

				if (!world)
				{
					throw std::runtime_error("Sectors can only be children of worlds!");
				}

				Sector& sector = world->CreateSector();
				if (attributes.ContainsKey(NAME_IDENTIFIER))
				{
					sector.SetName(attributes[NAME_IDENTIFIER]);
				}

				sharedData->mScope = &sector;
				return true;
			}

			return false;
		}

		bool XMLParseHelperSector::EndElementHandler(const std::string & element)
		{
			XMLParseHelperTable::SharedDataTable* sharedData = mpSharedData->As<XMLParseHelperTable::SharedDataTable>();

			if (!mbIsInitialized || !sharedData)	return false;

			if (element == SECTOR_IDENTIFIER)
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

		IXMLParseHelper* XMLParseHelperSector::Clone()
		{
			return new XMLParseHelperSector();
		}

	}
}