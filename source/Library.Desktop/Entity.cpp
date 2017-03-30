#include "pch.h"
#include "Entity.h"
#include "Sector.h"

namespace GameEngine
{
	namespace Library
	{
		namespace EntityConstants
		{
			const std::string NAME_IDENTIFIER = "Name";
		}

		using namespace EntityConstants;

		Entity::Entity()
		{
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
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
			assert(GetParent()->Is(Sector::TypeIdClass()));
			return *(GetParent()->As<Sector>());
		}

		void Entity::Update(const WorldState& worldState)
		{
			ENGINE_UNUSED(worldState);
		}
	}
}