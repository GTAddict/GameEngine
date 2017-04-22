#pragma once
#include "EventSubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		class SubscriberModifySubsAndQueue : public EventSubscriber
		{
		public:
			SubscriberModifySubsAndQueue();
			~SubscriberModifySubsAndQueue();

			void Notify(const EventPublisher& event);
		};
	}
}

