#include "pch.h"
#include "World.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		World::World()
		{
			AddPrescribedAttributeExternal("Name", mName);
			Append("Sectors").SetType(Datum::DatumType::Table);
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
			return Append("Sectors");
		}

		Sector& World::CreateSector()
		{
			Sector* sector = new Sector();
			sector->SetWorld(*this);
			return *sector;
		}

		void GameEngine::Library::World::Update(const WorldState& worldState)
		{
			Datum& sectors = Sectors();

			for (std::uint32_t i = 0; i < sectors.Size(); ++i)
			{
				(sectors[i].As<Sector>())->Update(worldState);
			}
		}
	}
}