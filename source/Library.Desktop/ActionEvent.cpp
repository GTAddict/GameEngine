#include "pch.h"
#include "ActionEvent.h"
#include "Event.h"
#include "WorldState.h"
#include "EventQueue.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionEventConstants
		{
			const std::string SUBTYPE_IDENTIFIER	= "subtype";
			const std::string DELAY_IDENTIFIER		= "delay";
		}

		RTTI_DEFINITIONS(ActionEvent);

		using namespace ActionEventConstants;

		ActionEvent::ActionEvent()
			: mDelay(0)
			, mEvent(std::make_shared<Event<EventMessageAttributed>>(EventMessageAttributed()))
		{
			Populate();
		}

		void ActionEvent::Update(WorldState& worldState)
		{
			EventMessageAttributed& message = mEvent->Message();

			message.SetSubtype(mSubtype);
			message.SetWorldState(worldState);

			VectorType::Iterator itBegin = begin() + GetPrescribedAttributeCount();
			VectorType::Iterator itEnd	 = end();
			
			for ( ; itBegin != itEnd; ++itBegin)
			{
				auto& datumPair = *itBegin;
				message[datumPair->first] = datumPair->second;
			}

			assert(worldState.mpEventQueue != nullptr);
			worldState.mpEventQueue->Enqueue(
				mEvent,
				worldState.GetGameTime(),
				std::chrono::duration<long long, std::milli>(mDelay)
			);
		}

		void ActionEvent::Populate()
		{
			Parent::Populate();
			AddPrescribedAttributeExternal(SUBTYPE_IDENTIFIER, mSubtype);
			AddPrescribedAttributeExternal(DELAY_IDENTIFIER, mDelay);
		}
	}
}