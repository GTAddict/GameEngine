#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Factory.h"
#include "Action.h"
#include "Reaction.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace EntityConstants
		{
			const std::string NAME_IDENTIFIER		= "name";
			const std::string ACTIONS_IDENTIFIER	= "actions";
			const std::string REACTIONS_IDENTIFIER	= "reactions";
		}

		RTTI_DEFINITIONS(Entity);

		using namespace EntityConstants;

		Entity::Entity()
		{
			Populate();
		}

		Entity::Entity(Entity&& rhs)
			: Parent(std::move(rhs))
			, mName(std::move(rhs.mName))
			, mpActions(rhs.mpActions)
			, mpReactions(rhs.mpReactions)
		{
			rhs.mpActions	= nullptr;
			rhs.mpReactions = nullptr;
		}

		Entity& Entity::operator=(Entity&& rhs)
		{
			Parent::operator=(std::move(rhs));
			
			if (this != &rhs)
			{
				mName		= std::move(rhs.mName);
				mpActions	= rhs.mpActions;
				mpReactions = rhs.mpReactions;

				rhs.mpActions	= nullptr;
				rhs.mpReactions = nullptr;
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

		Reaction& Entity::CreateReaction(const std::string& className, const std::string& instanceName)
		{
			Reaction& reaction = *Factory<Reaction>::Create(className);
			reaction.SetName(instanceName);
			AdoptReaction(reaction);
			return reaction;
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

		void Entity::AdoptReaction(Reaction& reaction)
		{
			Adopt(reaction, REACTIONS_IDENTIFIER);
		}

		void Entity::Populate()
		{
			Parent::Populate();
			mpActions	= AddPrescribedAttributeInternalWithType(ACTIONS_IDENTIFIER, Datum::DatumType::Table);
			mpReactions = AddPrescribedAttributeInternalWithType(REACTIONS_IDENTIFIER, Datum::DatumType::Table);
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
		}
	}
}