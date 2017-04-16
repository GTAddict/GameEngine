#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionListConstants
		{
			const std::string ACTIONS_IDENTIFIER = "actions";
		}

		RTTI_DEFINITIONS(ActionList);

		using namespace ActionListConstants;

		ActionList::ActionList()
		{
			Populate();
		}

		void ActionList::AdoptAction(Action& action)
		{
			Adopt(action, ACTIONS_IDENTIFIER);
		}

		void ActionList::Update(WorldState& worldState)
		{
			for (std::uint32_t i = 0; i < mpActions->Size(); ++i)
			{
				assert((*mpActions)[i].Is(Action::TypeIdClass()));
				worldState.mpAction = (*mpActions)[i].As<Action>();
				worldState.mpAction->Update(worldState);
			}
		}

		void ActionList::Populate()
		{
			Parent::Populate();
			mpActions = AddPrescribedAttributeInternalWithType(ACTIONS_IDENTIFIER, Datum::DatumType::Table);
		}
	}
}
