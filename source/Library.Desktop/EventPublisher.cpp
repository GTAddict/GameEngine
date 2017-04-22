#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include <thread>
#include <future>

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(EventPublisher);

		EventPublisher::EventPublisher(Vector<EventSubscriber*>& concreteSubscribers, std::mutex& conreteMutex)
			: mConcreteSubscribers(&concreteSubscribers)
			, mConcreteSubscribersLock(&conreteMutex)
		{
		}

		EventPublisher::EventPublisher(const EventPublisher& rhs)
			: mConcreteSubscribers(rhs.mConcreteSubscribers)
			, mConcreteSubscribersLock(rhs.mConcreteSubscribersLock)
			, mTimeEnqueued(rhs.mTimeEnqueued)
			, mDelay(rhs.mDelay)
		{
		}

		EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
		{
			if (this != &rhs)
			{
				mConcreteSubscribers		= rhs.mConcreteSubscribers;
				mConcreteSubscribersLock	= rhs.mConcreteSubscribersLock;
				mTimeEnqueued				= rhs.mTimeEnqueued;
				mDelay						= rhs.mDelay;
			}

			return *this;
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
			_CRITICAL(*mConcreteSubscribersLock)
			mSubscribersBuffer = *mConcreteSubscribers;		// Faster than std::copy
			_CRITICAL_END

			for (EventSubscriber* eventSubscriber : mSubscribersBuffer)
			{
				mFutures.PushBack(std::async([eventSubscriber, this] { eventSubscriber->Notify(*this); }));
			}
			mSubscribersBuffer.Clear();

			for (auto& f : mFutures)
			{
				f.get();
			}
			mFutures.Clear();
		}
	}
}