#pragma once
#include "EventSubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		class DummySubscriber : public EventSubscriber
		{
		public:
			DummySubscriber();
			~DummySubscriber();

			void Notify(const EventPublisher& event);
			bool ReceivedNotification();

		private:
			bool mbNotificationReceived;
		};
	}
}
