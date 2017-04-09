#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"

namespace GameEngine
{
	namespace Library
	{
		void EventQueue::Enqueue(EventPublisher& publisher, const GameTime& gameTime, const std::chrono::milliseconds& delay)
		{
			publisher.SetTime(gameTime.CurrentTime(), delay);
			mEventQueue.PushBack(&publisher);
		}

		void EventQueue::Send(EventPublisher& publisher)
		{
			publisher.Deliver();
			mEventQueue.Remove(&publisher);
			if (publisher.DeleteAfterPublishing())
			{
				delete &publisher;
			}
		}

		void EventQueue::Update(const GameTime& gameTime)
		{
			for (EventPublisher* eventPublisher : mEventQueue)
			{
				if (eventPublisher->IsExpired(gameTime.CurrentTime()))
				{
					Send(*eventPublisher);
				}
			}
		}

		void EventQueue::Clear()
		{
			for (EventPublisher* eventPublisher : mEventQueue)
			{
				if (eventPublisher->DeleteAfterPublishing())
				{
					delete eventPublisher;
				}
			}

			mEventQueue.Clear();
		}

		std::uint32_t EventQueue::Size() const
		{
			return mEventQueue.Size();
		}

		bool EventQueue::IsEmpty() const
		{
			return mEventQueue.IsEmpty();
		}
	}
}
