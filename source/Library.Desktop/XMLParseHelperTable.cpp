#include "pch.h"
#include "XMLParseHelperTable.h"
#include "Datum.h"
#include "Scope.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(XMLParseHelperTable::SharedDataTable)

		using namespace TableParserConstants;

		XMLParseHelperTable::SharedDataTable::SharedDataTable()
			: mScope(nullptr)
		{
		}

		XMLParseHelperTable::SharedDataTable::~SharedDataTable()
		{
			delete mScope;
		}

		XMLParseMaster::SharedData* XMLParseHelperTable::SharedDataTable::Clone() const
		{
			SharedData* pClone = new SharedDataTable();
			pClone->SetXMLParseMaster(GetXMLParseMaster());
			// Clone scope?
			return pClone;
		}

		Scope* XMLParseHelperTable::SharedDataTable::GetScope() const
		{
			return mScope;
		}

		bool XMLParseHelperTable::StartElementHandler(const std::string& element, const HashMapType attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(SharedDataTable::TypeIdClass()))	return false;

			SharedDataTable* sharedData = mpSharedData->As<SharedDataTable>();

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
			else if (element == SECTOR_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				if (!sharedData->mScope->Is(World::TypeIdClass()))
				{
					throw std::runtime_error("Sectors can only be children of worlds!");
				}
				
				Sector& sector = sharedData->mScope->As<World>()->CreateSector();
				if (attributes.ContainsKey(NAME_IDENTIFIER))
				{
					sector.SetName(attributes[NAME_IDENTIFIER]);
				}
				
				sharedData->mScope = &sector;
				return true;
			}
			else if (element == ENTITY_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				if (!sharedData->mScope->Is(Sector::TypeIdClass()))
				{
					throw std::runtime_error("Entities can only be children of sectors!");
				}
				
				sharedData->mScope = &sharedData->mScope->As<Sector>()->CreateEntity(attributes[CLASS_IDENTIFIER], attributes[NAME_IDENTIFIER]);
				return true;
			}
			else if (element == INTEGER_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Integer), attributes);
			}
			else if (element == FLOAT_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Float), attributes);
			}
			else if (element == MATRIX_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Matrix), attributes);
			}
			else if (element == VECTOR_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Vector), attributes);
			}
			else if (element == STRING_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::String), attributes);
			}

			return false;
		}

		bool XMLParseHelperTable::EndElementHandler(const std::string& element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(SharedDataTable::TypeIdClass()))	return false;

			SharedDataTable* sharedData = mpSharedData->As<SharedDataTable>();

			if (element == WORLD_IDENTIFIER || element == SECTOR_IDENTIFIER || element == ENTITY_IDENTIFIER)
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

		IXMLParseHelper* XMLParseHelperTable::Clone()
		{
			return new XMLParseHelperTable();
		}

		bool XMLParseHelperTable::PopulateDatum(XMLParseHelperTable::SharedDataTable* sharedData, std::int32_t type, const HashMapType attributes)
		{
			assert(sharedData->mScope != nullptr);
			Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
			datum.SetType(static_cast<Datum::DatumType>(type));
			HashMapType::Iterator indexIt = attributes.Find(INDEX_IDENTIFIER);
			std::uint32_t index = (indexIt == attributes.end() ? 0 : stoi(indexIt->second));
			datum.SetFromString(attributes[VALUE_IDENTIFIER], index);
			return true;
		}
	}
}
