#include "pch.h"
#include "DummySubscriber.h"
#include "Event.h"
#include "DummyStruct.h"

namespace GameEngine
{
	namespace Library
	{
		DummySubscriber::DummySubscriber()
			: mbNotificationReceived(false)
		{
			Event<DummyStruct>::Subscribe(*this);
		}

		DummySubscriber::~DummySubscriber()
		{
			Event<DummyStruct>::Unsubscribe(*this);
		}

		void DummySubscriber::Notify(const EventPublisher& event)
		{
			ENGINE_UNUSED(event);
			mbNotificationReceived = true;
		}

		bool DummySubscriber::ReceivedNotification()
		{
			return mbNotificationReceived;
		}
	}
}