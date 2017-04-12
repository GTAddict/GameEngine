#include "pch.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "WorldState.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionEventConstants
		{
			const std::string SUBTYPE_IDENTIFIER = "Subtype";
			const std::string DELAY_IDENTIFIER = "Delay";
		}

		using namespace ActionEventConstants;

		ActionEvent::ActionEvent()
			: mDelay(0)
		{
			AddPrescribedAttributeExternal(SUBTYPE_IDENTIFIER, mSubtype);
			AddPrescribedAttributeExternal(DELAY_IDENTIFIER, mDelay);
		}

		void ActionEvent::Update(WorldState& worldState)
		{
			EventMessageAttributed* eventMessageAttributed = new EventMessageAttributed();
			eventMessageAttributed->SetSubtype(mSubtype);
			eventMessageAttributed->SetWorld(*worldState.mpWorld);
			// Copy all aux params into event
			// Queue event.
		}
	}
}