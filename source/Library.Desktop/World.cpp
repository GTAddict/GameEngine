#include "pch.h"
#include "World.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		namespace WorldConstants
		{
			const std::string NAME_IDENTIFIER		= "Name";
			const std::string SECTORS_IDENTIFIER	= "Sectors";
		}

		using namespace WorldConstants;

		World::World()
		{
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
			mpSectors = AddPrescribedAttributeInternal(SECTORS_IDENTIFIER, Datum::DatumType::Table);
		}

		const std::string& World::Name() const
		{
			return mName;
		}

		void World::SetName(const std::string& name)
		{
			if (!name.length())
			{
				throw std::invalid_argument("Cannot set an empty name.");
			}

			mName = name;
		}

		Datum& World::Sectors()
		{
			return *mpSectors;
		}

		Sector& World::CreateSector()
		{
			Sector& sector = *new Sector();
			AdoptSector(sector);
			return sector;
		}

		void GameEngine::Library::World::Update(const WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpSectors->Size(); ++i)
			{
				assert((*mpSectors)[i].Is(Sector::TypeIdClass()));
				(*mpSectors)[i].As<Sector>()->Update(worldState);
			}
		}

		void World::AdoptSector(Sector& sector)
		{
			Adopt(sector, SECTORS_IDENTIFIER);
		}
	}
}