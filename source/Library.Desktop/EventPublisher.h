#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <chrono>
#include <future>

namespace GameEngine
{
	namespace Library
	{
		class EventSubscriber;

		/**
		*	\class	EventPublisher
		*	\brief	This is an abstract base class that provides
		*			functionality for a class to publish events.
		*			It is responsible for sending itself.
		*/
		class EventPublisher abstract : public RTTI
		{
			RTTI_DECLARATIONS(EventPublisher, RTTI);

			using time_point	= std::chrono::high_resolution_clock::time_point;
			using milliseconds	= std::chrono::milliseconds;

		public:

			/**
			*	\brief						Parametrized constructor. Stores the
			*								list of subscribers to notify and whether
			*								it should be deleted once published.
			*	\param concreteSubscribers	The list of subscribers to notify
			*	\param concreteMutex		The mutex that guards the subscribers.
			*/
											EventPublisher(Vector<EventSubscriber*>& concreteSubscribers, std::mutex& concreteMutex);

			/**
			*	\brief						Copy constructor. Neither futures nor the
			*								buffer are copied.
			*/
											EventPublisher(const EventPublisher& rhs);

			/**
			*	\brief						Copy assignment operator. Neither futures nor
			*								the buffer are copied.
			*	\return						A reference to the EventPublisher assigned to.
			*/
			EventPublisher&					operator=(const EventPublisher& rhs);

			/**
			*	\brief						Default destructor.
			*/
			virtual							~EventPublisher() = default;

			/**
			*	\brief						Sets the current time and delay after which
			*								Deliver is called, if this is enqueued in the
			*								EventQueue.
			*	\param timeNow				The current time.
			*	\param delay				The period after the current time when Deliver
			*								should be called.
			*/
			void							SetTime(const time_point& timeNow, const milliseconds& delay = milliseconds(0));

			/**
			*	\brief						Returns the time this was enqueued in the EventQueue.
			*	\return						A const reference to the time this was enqueued.
			*/
			const time_point&				TimeEnqueued() const;

			/**
			*	\brief						Returns the delay from the enqueued time that this was
			*								scheduled to be delivered.
			*	\return						A const reference to the delay after the enqueued time
			*								that this was scheduled to be delivered.
			*/
			const milliseconds&				Delay() const;
			
			/**
			*	\brief						Whether the sum total of the enqueue time and delay
			*								exceeds the current time or not.
			*	\param timeNow				The current time.
			*	\return						False if it exceeds, true if it doesn't.
			*/
			bool							IsExpired(const time_point& timeNow) const;

			/**
			*	\brief						Notifies all of its subscribers about the event.
			*/
			void							Deliver();

		private:

			Vector<EventSubscriber*>*		mConcreteSubscribers;		/**< A pointer to the list of subscribers to notify. */
			Vector<EventSubscriber*>		mSubscribersBuffer;			/**< A copy of the concrete subscribers that should be notified. */
			std::mutex*						mConcreteSubscribersLock;	/**< A pointer to the concrete mutex that guards the concrete subscribers. */
			Vector<std::future<void>>		mFutures;					/**< Vector of futures that async will create. Don't want to stack alloc this vector every frame on Update. */

			time_point						mTimeEnqueued;				/**< The time point at which the was added to the EventQueue. */
			milliseconds					mDelay;						/**< The delay after the time enqueued that this is schedule to be delivered. */
		};
	}
}