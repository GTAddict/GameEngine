#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <chrono>

namespace GameEngine
{
	namespace Library
	{
		class EventSubscriber;

		class EventPublisher : public RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, RTTI);

		public:
			EventPublisher(Vector<EventSubscriber*>& concreteSubscribers, bool deleteAterPublish = true);
			EventPublisher(const EventPublisher& rhs) = default;
			EventPublisher(EventPublisher&& rhs) = default;
			EventPublisher& operator=(const EventPublisher& rhs) = default;
			EventPublisher& operator=(EventPublisher&& rhs) = default;
			virtual ~EventPublisher() = default;

			void SetTime(const std::chrono::high_resolution_clock::time_point& timeNow, const std::chrono::milliseconds& delay = std::chrono::milliseconds(0));
			const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;
			const std::chrono::milliseconds& Delay() const;
			bool IsExpired(const std::chrono::high_resolution_clock::time_point& timeNow) const;
			void Deliver();
			bool DeleteAfterPublishing() const;

		private:
			Vector<EventSubscriber*>*						mConcreteSubscribers;
			bool											mbDeleteAfterPublish;
			std::chrono::high_resolution_clock::time_point	mTimeEnqueued;
			std::chrono::milliseconds						mDelay;
		};
	}
}