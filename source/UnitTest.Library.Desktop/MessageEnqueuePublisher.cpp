#include "pch.h"
#include "MessageEnqueuePublisher.h"

namespace GameEngine
{
	namespace Library
	{
		MessageEnqueuePublisher::MessageEnqueuePublisher(const std::uint32_t publishersToEnqueue, EventQueue* eventQueue, std::mt19937* gen, std::uniform_int_distribution<>* dis, std::mutex* randMutex, GameClock* clock, GameTime* gameTime)
		{
			mPublishersToEnqueue = publishersToEnqueue;
			mEventQueue = eventQueue;
			mGen = gen;
			mDis = dis;
			mRandMutex = randMutex;
			mGameTime = gameTime;
			mGameClock = clock;
		}

		std::uint32_t MessageEnqueuePublisher::GetPublishersToEnqueue() const
		{
			return mPublishersToEnqueue;
		}

		EventQueue* MessageEnqueuePublisher::GetEventQueue() const
		{
			return mEventQueue;
		}

		std::mt19937* MessageEnqueuePublisher::GetGen() const
		{
			return mGen;
		}

		std::uniform_int_distribution<>* MessageEnqueuePublisher::GetDis() const
		{
			return mDis;
		}

		std::mutex* MessageEnqueuePublisher::GetMutex() const
		{
			return mRandMutex;
		}
		
		GameClock* MessageEnqueuePublisher::GetClock() const
		{
			return mGameClock;
		}

		GameTime* MessageEnqueuePublisher::GetGameTime() const
		{
			return mGameTime;
		}
	}
}
