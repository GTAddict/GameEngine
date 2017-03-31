#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "Factory.h"
#include "World.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace SectorConstants
		{
			const std::string NAME_IDENTIFIER		= "Name";
			const std::string ENTITIES_IDENTIFIER	= "Entities";
		}

		using namespace SectorConstants;

		Sector::Sector()
		{
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
			mpEntities = AddPrescribedAttributeInternalWithType(ENTITIES_IDENTIFIER, Datum::DatumType::Table);
		}

		Sector::Sector(Sector&& rhs)
			: Attributed::Attributed(std::move(rhs))
			, mName(std::move(rhs.mName))
			, mpEntities(rhs.mpEntities)
		{
			rhs.mpEntities = nullptr;
		}

		Sector& Sector::operator=(Sector&& rhs)
		{
			Attributed::operator=(std::move(rhs));

			if (this != &rhs)
			{
				mName = std::move(rhs.mName);
				mpEntities = rhs.mpEntities;

				rhs.mpEntities = nullptr;
			}

			return *this;
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
			return *mpEntities;
		}

		Entity& Sector::CreateEntity(const std::string& className, const std::string& instanceName)
		{
			Entity& entity = *Factory<Entity>::Create(className);
			entity.SetName(instanceName);
			AdoptEntity(entity);
			return entity;
		}

		const World& Sector::GetWorld() const
		{
			assert(GetParent()->Is(World::TypeIdClass()));
			return *(GetParent()->As<World>());
		}

		void Sector::Update(WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpEntities->Size(); ++i)
			{
				assert((*mpEntities)[i].Is(Entity::TypeIdClass()));
				worldState.mpEntity = (*mpEntities)[i].As<Entity>();
				worldState.mpEntity->Update(worldState);
			}
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, ENTITIES_IDENTIFIER);
		}
	}
}