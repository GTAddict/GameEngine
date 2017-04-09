#pragma once

namespace GameEngine
{
	namespace Library
	{
		class EventPublisher;

		class EventSubscriber
		{
		public:
			virtual ~EventSubscriber();

			virtual void Notify(const EventPublisher& event) = 0;
		};

	}
}
