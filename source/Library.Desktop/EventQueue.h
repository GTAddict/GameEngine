#pragma once
#include "Vector.h"

namespace GameEngine
{
	namespace Library
	{
		class EventPublisher;
		class GameTime;

		class EventQueue
		{
		public:
			
			void Enqueue(EventPublisher& publisher, const GameTime& gameTime, const std::chrono::milliseconds& delay);
			void Send(EventPublisher& publisher);
			void Update(const GameTime& gameTime);
			void Clear();
			bool IsEmpty() const;
			std::uint32_t Size() const;

		private:

			Vector<EventPublisher*> mEventQueue;

		};
	}
}