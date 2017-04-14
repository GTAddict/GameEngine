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

		using namespace ActionEventConstants;

		ActionEvent::ActionEvent()
			: mDelay(0)
			, mEvent(new Event<EventMessageAttributed>(EventMessageAttributed(), false))
		{
			AddPrescribedAttributeExternal(SUBTYPE_IDENTIFIER, mSubtype);
			AddPrescribedAttributeExternal(DELAY_IDENTIFIER, mDelay);
		}

		ActionEvent::~ActionEvent()
		{
			delete mEvent;
		}

		void ActionEvent::Update(WorldState& worldState)
		{
			EventMessageAttributed& message = mEvent->Message();

			message.SetSubtype(mSubtype);
			message.SetWorldState(worldState);

			VectorType::Iterator itBegin	= begin() + GetPrescribedAttributeCount();
			VectorType::Iterator itEnd		= end();
			
			for ( ; itBegin != itEnd; ++itBegin)
			{
				auto& datumPair = *itBegin;
				message[datumPair->first] = datumPair->second;
			}

			assert(worldState.mpEventQueue != nullptr);
			worldState.mpEventQueue->Enqueue(
				*mEvent,
				worldState.GetGameTime(),
				std::chrono::duration<long long, std::milli>(mDelay)
			);
		}
	}
}