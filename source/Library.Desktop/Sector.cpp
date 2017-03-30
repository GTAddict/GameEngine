#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "Factory.h"
#include "World.h"

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
			mpEntities = AddPrescribedAttributeInternal(ENTITIES_IDENTIFIER, Datum::DatumType::Table);
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

		Entity& Sector::CreateEntity(const std::string& className, const std::string & instanceName)
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

		void Sector::Update(const WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpEntities->Size(); ++i)
			{
				assert((*mpEntities)[i].Is(Entity::TypeIdClass()));
				(*mpEntities)[i].As<Entity>()->Update(worldState);
			}
		}

		void Sector::AdoptEntity(Entity& entity)
		{
			Adopt(entity, ENTITIES_IDENTIFIER);
		}
	}
}