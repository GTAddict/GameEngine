#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		EventPublisher::EventPublisher(const Vector<EventSubscriber*>& concreteSubscribers, bool deleteAterPublish)
			: mConcreteSubscribers(concreteSubscribers)
			, mbDeleteAfterPublish(deleteAterPublish)
		{
		}

		void EventPublisher::SetTime(const std::chrono::high_resolution_clock::time_point& timeNow, const std::chrono::milliseconds& delay)
		{
			mTimeEnqueued = timeNow;
			mDelay = delay;
		}

		const std::chrono::high_resolution_clock::time_point& EventPublisher::TimeEnqueued() const
		{
			return mTimeEnqueued;
		}

		const std::chrono::milliseconds& EventPublisher::Delay() const
		{
			return mDelay;
		}

		bool EventPublisher::IsExpired(const std::chrono::high_resolution_clock::time_point & timeNow) const
		{
			return (mTimeEnqueued + mDelay) >= timeNow;
		}

		void EventPublisher::Deliver()
		{
			for (EventSubscriber* eventSubscriber : mConcreteSubscribers)
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