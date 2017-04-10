#pragma once

namespace GameEngine
{
	namespace Library
	{
		class EventPublisher;

		class EventSubscriber
		{
		public:
			virtual ~EventSubscriber() = default;
			virtual void Notify(const EventPublisher& event) = 0;
		};

	}
}
