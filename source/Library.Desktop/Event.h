#pragma once
#include "EventPublisher.h"
#include "Vector.h"

namespace GameEngine
{
	namespace Library
	{
		template <typename T>
		class Event final : public EventPublisher
		{
			RTTI_DECLARATIONS(Event<T>, EventPublisher);

		public:
			Event(const T& message, bool deleteAfterPublishing);

			Event(const Event& rhs) = default;
			Event(Event&& rhs) = default;
			Event& operator=(const Event& rhs) = default;
			Event& operator=(Event&& rhs) = default;

			static void Subscribe(EventSubscriber& subscriber);
			static void Unsubscribe(EventSubscriber& subscriber);
			static void UnsubscribeAll();

			const T& Message() const;

		private:
			static Vector<EventSubscriber*> mSubscribers;
			T mMessage;

		};

#include "Event.inl"

	}
}