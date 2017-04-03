#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionListConstants
		{
			const std::string ACTIONS_IDENTIFIER = "Actions";
		}

		RTTI_DEFINITIONS(ActionList);

		using namespace ActionListConstants;

		ActionList::ActionList()
			: mpActions(AddPrescribedAttributeInternalWithType(ACTIONS_IDENTIFIER, Datum::DatumType::Table))
		{
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
	}
}
