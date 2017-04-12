#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(EventPublisher);

		EventPublisher::EventPublisher(Vector<EventSubscriber*>& concreteSubscribers, bool deleteAterPublish)
			: mConcreteSubscribers(&concreteSubscribers)
			, mbDeleteAfterPublish(deleteAterPublish)
		{
		}

		void EventPublisher::SetTime(const time_point& timeNow, const milliseconds& delay)
		{
			mTimeEnqueued = timeNow;
			mDelay = delay;
		}

		const EventPublisher::time_point& EventPublisher::TimeEnqueued() const
		{
			return mTimeEnqueued;
		}

		const EventPublisher::milliseconds& EventPublisher::Delay() const
		{
			return mDelay;
		}

		bool EventPublisher::IsExpired(const time_point& timeNow) const
		{
			return (mTimeEnqueued + mDelay) <= timeNow;
		}

		void EventPublisher::Deliver()
		{
			for (EventSubscriber* eventSubscriber : *mConcreteSubscribers)
			{
				eventSubscriber->Notify(*this);
			}
		}

		bool EventPublisher::DeleteAfterPublishing() const
		{
			return mbDeleteAfterPublish;
		}
	}
}