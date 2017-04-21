#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <algorithm>
#include <thread>
#include <iterator>

namespace GameEngine
{
	namespace Library
	{
		void EventQueue::Enqueue(EventPublisher& publisher, const GameTime& gameTime, const milliseconds& delay)
		{
			publisher.SetTime(gameTime.CurrentTime(), delay);

			_CRITICAL(mEventQueueLock)
			mEventQueue.PushBack(&publisher);
			_CRITICAL_END
		}
		
		void EventQueue::Send(EventPublisher& publisher)
		{
			publisher.Deliver();
			if (publisher.DeleteAfterPublishing())
			{
				delete &publisher;
			}
		}

		void EventQueue::Update(const GameTime& gameTime)
		{
			_CRITICAL(mEventQueueLock)
			if (mEventQueue.Size())
			{
				auto it = std::partition(
					mEventQueue.begin(),
					mEventQueue.end(),
					[&gameTime](EventPublisher* eventPublisher) { return !eventPublisher->IsExpired(gameTime.CurrentTime()); }
				);

				std::back_insert_iterator<Vector<EventPublisher*>> sweepIt(mSweepQueue);
				std::move(it, mEventQueue.end(), sweepIt);
				mEventQueue.Remove(it, mEventQueue.end());
			}
			_CRITICAL_END

			for (EventPublisher* eventPublisher : mSweepQueue)
			{
				mFutures.PushBack(std::async([this, eventPublisher] { Send(*eventPublisher); }));
			}
			mSweepQueue.Clear();

			for (auto& f : mFutures)
			{
				f.get();
			}
			mFutures.Clear();
		}

		void EventQueue::Clear()
		{
			_CRITICAL(mEventQueueLock)
			for (EventPublisher* eventPublisher : mEventQueue)
			{
				if (eventPublisher->DeleteAfterPublishing())
				{
					delete eventPublisher;
				}
			}
			mEventQueue.Clear();
			_CRITICAL_END
		}

		std::uint32_t EventQueue::Size() const
		{
			_CRITICAL(mEventQueueLock)
			return mEventQueue.Size();
			_CRITICAL_END
		}

		bool EventQueue::IsEmpty() const
		{
			_CRITICAL(mEventQueueLock)
			return mEventQueue.IsEmpty();
			_CRITICAL_END
		}
	}
}
