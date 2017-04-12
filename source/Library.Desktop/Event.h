#pragma once
#include "EventPublisher.h"
#include "Vector.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Event
		*	\brief	This is a templated Event class that
		*			implements the EventPublisher interface.
		*			It is responsible for sending itself.
		*/
		template <typename T>
		class Event final : public EventPublisher
		{
			RTTI_DECLARATIONS(Event<T>, EventPublisher);

		public:

			/**
			*	\brief				Parametrized constructor. Stores the 
			*						message to pass and whether to
			*						delete it after it is published.
			*	\param message		The message to be stored in this Event.
			*	\param deleteAfterPublishing Whether this Event should be
			*						deleted once it's dispatched from the queue.
			*/
									Event(const T& message, bool deleteAfterPublishing);

			/**
			*	\brief				Default copy constructor.
			*/
									Event(const Event& rhs) = default;
			
			/**
			*	\brief				Default move constructor.
			*/
									Event(Event&& rhs) = default;

			/**
			*	\brief				Default copy assignment operator.
			*	\return				A reference to the Event assigned to.
			*/
			Event&					operator=(const Event& rhs) = default;
			
			/**
			*	\brief				Default move assignment operator.
			*	\return				A reference to the Event assigned to.
			*/
			Event&					operator=(Event&& rhs) = default;

			/**
			*	\brief				Allows EventSubscribers to receive
			*						Events of this type.
			*	\param subscriber	The EventSubscriber to send
			*						notifications to.
			*/
			static void				Subscribe(EventSubscriber& subscriber);

			/**
			*	\brief				Allows EventSubscribers to stop receiving
			*						Events of this type.
			*	\param subscriber	The EventSubscriber to stop sending
			*						notifications to.
			*/
			static void				Unsubscribe(EventSubscriber& subscriber);

			/**
			*	\brief				Stops sending notifications to all
			*						registered subscribers.
			*/
			static void				UnsubscribeAll();

			/**
			*	\brief				Returns the message associated with this
			*						Event.
			*	\return				A const reference to the message contained
			*						in this event.
			*/
			const T&				Message() const;

		private:

			static Vector<EventSubscriber*>		mSubscribers;	/**< The list of subscribers to send notifications to. */
			T									mMessage;		/**< The message associated with this Event. */

		};

#include "Event.inl"

	}
}