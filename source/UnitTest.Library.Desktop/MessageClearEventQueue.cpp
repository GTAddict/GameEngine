#include "pch.h"
#include "MessageClearEventQueue.h"

namespace GameEngine
{
	namespace Library
	{
		MessageClearEventQueue::MessageClearEventQueue(EventQueue* eventQueue)
		{
			mEventQueue = eventQueue;
		}

		EventQueue* MessageClearEventQueue::GetEventQueue() const
		{
			return mEventQueue;
		}
	}
}
