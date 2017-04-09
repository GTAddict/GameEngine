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
		public:
			EventPublisher(const Vector<EventSubscriber*>& concreteSubscribers, bool deleteAterPublish = true);
			void SetTime(const std::chrono::high_resolution_clock::time_point& timeNow, const std::chrono::milliseconds& delay = std::chrono::milliseconds(0));
			const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;
			const std::chrono::milliseconds& Delay() const;
			bool IsExpired(const std::chrono::high_resolution_clock::time_point& timeNow) const;
			void Deliver();
			bool DeleteAfterPublishing() const;

			
			virtual ~EventPublisher() = default;

		private:
			const Vector<EventSubscriber*>&						mConcreteSubscribers;
			const bool											mbDeleteAfterPublish;
			std::chrono::high_resolution_clock::time_point		mTimeEnqueued;
			std::chrono::milliseconds							mDelay;
		};
	}
}