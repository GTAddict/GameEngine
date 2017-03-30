#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "Factory.h"
#include "World.h"

namespace GameEngine
{
	namespace Library
	{
		Sector::Sector()
		{
			AddPrescribedAttributeExternal("Name", mName);
			Append("Sectors").SetType(Datum::DatumType::Table);
		}

		const std::string& Sector::Name() const
		{
			return mName;
		}

		void Sector::SetName(const std::string& name)
		{
			if (!name.length())
			{
				throw std::invalid_argument("Cannot set an empty name.");
			}

			mName = name;
		}

		Datum& Sector::Entities()
		{
			return Append("Entities");
		}

		Entity& Sector::CreateEntity(const std::string& className, const std::string & instanceName)
		{
			Entity* entity = Factory<Entity>::Create(className);
			entity->SetName(instanceName);
			entity->SetSector(*this);
			return *entity;
		}

		void Sector::SetWorld(World& world)
		{
			world.Adopt(*this, "Sectors");
		}

		const World& Sector::GetWorld() const
		{
			return *(GetParent()->As<World>());
		}

		void Sector::Update(const WorldState& worldState)
		{
			Datum& entities = Entities();

			for (std::uint32_t i = 0; i < entities.Size(); ++i)
			{
				(entities[i].As<Entity>())->Update(worldState);
			}
		}
	}
}