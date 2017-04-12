#pragma once

namespace GameEngine
{
	namespace Library
	{
		class EventPublisher;

		/**
		*	\class	EventPublisher
		*	\brief	This is an abstract base class that provides
		*			functionality for a class to listen to
		*			EventPublishers.
		*/
		class EventSubscriber
		{
		public:

			/**
			*	\brief				Default destructor.
			*/
			virtual					~EventSubscriber() = default;

			/**
			*	\brief				Called when the EventPublisher is delivered.
			*	\param event		The EventPublisher who sent the event.
			*/
			virtual void			Notify(const EventPublisher& event) = 0;
		};

	}
}
