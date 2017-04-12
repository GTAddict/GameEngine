#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Reaction
		*	\brief	This is an abstract base class that provides
		*			an interface to respond to Events.
		*/
		class Reaction abstract : public ActionList, public EventSubscriber
		{
		public:

			/**
			*	\brief				Default destructor.
			*/
			virtual					~Reaction() = default;

			/**
			*	\brief				Called when the Event is delivered.
			*	\param event		The EventPublisher who sent the event.
			*/
			virtual void			Notify(const EventPublisher& event) override = 0;
		};

#define ReactionFactory(ConcreteReaction)	ConcreteFactory(Reaction, ConcreteReaction)

	}
}