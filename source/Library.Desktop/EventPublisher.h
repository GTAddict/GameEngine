#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <chrono>

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

			using time_point = std::chrono::high_resolution_clock::time_point;
			using milliseconds = std::chrono::milliseconds;

		public:

			/**
			*	\brief				Parametrized constructor. Stores the
			*						list of subscribers to notify and whether
			*						it should be deleted once published.
			*	\param concreteSubscribers	The list of subscribers to notify
			*	\param deleteAfterPublishing Whether this should be deleted once it
			*						is dispatched from the EventQueue.
			*/
									EventPublisher(Vector<EventSubscriber*>& concreteSubscribers, bool deleteAterPublish = true);

			/**
			*	\brief				Default copy constructor.
			*/
									EventPublisher(const EventPublisher& rhs) = default;

			/**
			*	\brief				Default move constructor.
			*/
									EventPublisher(EventPublisher&& rhs) = default;

			/**
			*	\brief				Default copy assignment operator.
			*	\return				A reference to the EventPublisher assigned to.
			*/
			EventPublisher&			operator=(const EventPublisher& rhs) = default;

			/**
			*	\brief				Default move assignment operator.
			*	\return				A reference to the EventPublisher assigned to.
			*/
			EventPublisher&			operator=(EventPublisher&& rhs) = default;

			/**
			*	\brief				Default destructor.
			*/
			virtual					~EventPublisher() = default;

			/**
			*	\brief				Sets the current time and delay after which
			*						Deliver is called, if this is enqueued in the
			*						EventQueue.
			*	\param timeNow		The current time.
			*	\param delay		The period after the current time when Deliver
			*						should be called.
			*/
			void					SetTime(const time_point& timeNow, const milliseconds& delay = milliseconds(0));

			/**
			*	\brief				Returns the time this was enqueued in the EventQueue.
			*	\return				A const reference to the time this was enqueued.
			*/
			const time_point&		TimeEnqueued() const;

			/**
			*	\brief				Returns the delay from the enqueued time that this was
			*						scheduled to be delivered.
			*	\return				A const reference to the delay after the enqueued time
			*						that this was scheduled to be delivered.
			*/
			const milliseconds&		Delay() const;
			
			/**
			*	\brief				Whether the sum total of the enqueue time and delay
			*						exceeds the current time or not.
			*	\param timeNow		The current time.
			*	\return				False if it exceeds, true if it doesn't.
			*/
			bool					IsExpired(const time_point& timeNow) const;

			/**
			*	\brief				Notifies all of its subscribers about the event.
			*/
			void					Deliver();

			/**
			*	\brief				Returns whether or not this should be deleted after
			*						being published from the EventQueue.
			*	\return				Whether or not this should be deleted after being
			*						published from the EventQueue.
			*/
			bool					DeleteAfterPublishing() const;

		private:

			Vector<EventSubscriber*>*	mConcreteSubscribers;	/**< A pointer to the list of subscribers to notify. */
			bool						mbDeleteAfterPublish;	/**< Whether or not this should be deleted after being published. */
			time_point					mTimeEnqueued;			/**< The time point at which the was added to the EventQueue. */
			milliseconds				mDelay;					/**< The delay after the time enqueued that this is schedule to be delivered. */
		};
	}
}