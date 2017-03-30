#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		Entity::Entity()
		{
			AddPrescribedAttributeExternal("Name", mName);
		}

		const std::string& Entity::Name() const
		{
			return mName;
		}

		void Entity::SetName(const std::string& name)
		{
			if (!name.length())
			{
				throw std::invalid_argument("Cannot set an empty name.");
			}

			mName = name;
		}

		const Sector& Entity::GetSector() const
		{
			return *(GetParent()->As<Sector>());
		}

		void Entity::SetSector(Sector& sector)
		{
			sector.Adopt(*this, "Entities");
		}

		void Entity::Update(const WorldState& worldState)
		{
			ENGINE_UNUSED(worldState);
		}
	}
}