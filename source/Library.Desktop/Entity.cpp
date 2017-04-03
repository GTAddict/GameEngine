#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Factory.h"
#include "Action.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace EntityConstants
		{
			const std::string NAME_IDENTIFIER = "Name";
			const std::string ACTIONS_IDENTIFIER = "Actions";
		}

		RTTI_DEFINITIONS(Entity);

		using namespace EntityConstants;

		Entity::Entity()
			: mpActions(AddPrescribedAttributeInternalWithType(ACTIONS_IDENTIFIER, Datum::DatumType::Table))
		{
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
		}

		Entity::Entity(Entity&& rhs)
			: Attributed(std::move(rhs))
			, mName(std::move(rhs.mName))
		{
		}

		Entity& Entity::operator=(Entity&& rhs)
		{
			Attributed::operator=(std::move(rhs));
			
			if (this != &rhs)
			{
				mName = std::move(rhs.mName);
			}

			return *this;
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

		Datum& Entity::Actions() const
		{
			return *mpActions;
		}

		Action& Entity::CreateAction(const std::string& className, const std::string& instanceName)
		{
			Action& action = *Factory<Action>::Create(className);
			action.SetName(instanceName);
			AdoptAction(action);
			return action;
		}

		void Entity::Update(WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpActions->Size(); ++i)
			{
				assert((*mpActions)[i].Is(Action::TypeIdClass()));
				worldState.mpAction = (*mpActions)[i].As<Action>();
				worldState.mpAction->Update(worldState);
			}
		}
		
		void Entity::AdoptAction(Action& action)
		{
			Adopt(action, ACTIONS_IDENTIFIER);
		}
	}
}