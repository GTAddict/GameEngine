#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace WorldConstants
		{
			const std::string NAME_IDENTIFIER		= "name";
			const std::string SECTORS_IDENTIFIER	= "sectors";
		}

		RTTI_DEFINITIONS(World);

		using namespace WorldConstants;

		World::World()
		{
			Populate();
		}

		World::World(World&& rhs)
			: Parent(std::move(rhs))
			, mName(std::move(rhs.mName))
			, mpSectors(rhs.mpSectors)
		{
			rhs.mpSectors = nullptr;
		}

		World& World::operator=(World&& rhs)
		{
			Parent::operator=(rhs);

			if (this != &rhs)
			{
				mName = std::move(rhs.mName);
				mpSectors = rhs.mpSectors;

				rhs.mpSectors = nullptr;
			}

			return *this;
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

		void GameEngine::Library::World::Update(WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpSectors->Size(); ++i)
			{
				assert((*mpSectors)[i].Is(Sector::TypeIdClass()));
				worldState.mpSector = (*mpSectors)[i].As<Sector>();
				worldState.mpSector->Update(worldState);
			}
		}

		void World::AdoptSector(Sector& sector)
		{
			Adopt(sector, SECTORS_IDENTIFIER);
		}

		void World::Populate()
		{
			Parent::Populate();
			mpSectors = (AddPrescribedAttributeInternalWithType(SECTORS_IDENTIFIER, Datum::DatumType::Table));
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
		}
	}
}