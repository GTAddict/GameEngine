#pragma once
#include <random>
#include <mutex>

namespace GameEngine
{
	namespace Library
	{
		class EventQueue;
		class GameTime;
		class GameClock;

		class MessageEnqueuePublisher
		{
		public:
			MessageEnqueuePublisher(const std::uint32_t publishersToEnqueue, EventQueue* eventQueue, std::mt19937* gen, std::uniform_int_distribution<>* dis, std::mutex* randMutex, GameClock* clock, GameTime* gameTime);

			std::uint32_t GetPublishersToEnqueue() const;
			EventQueue* GetEventQueue() const;
			std::mt19937* GetGen() const;
			std::uniform_int_distribution<>* GetDis() const;
			std::mutex* GetMutex() const;
			GameClock* GetClock() const;
			GameTime* GetGameTime() const;

		private:
			std::uint32_t mPublishersToEnqueue;
			EventQueue* mEventQueue;
			std::mt19937* mGen;
			std::uniform_int_distribution<>* mDis;
			std::mutex* mRandMutex;
			GameTime* mGameTime;
			GameClock* mGameClock;
		};
	}
}

