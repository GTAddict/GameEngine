#pragma once
#include "Action.h"
#include "EventMessageAttributed.h"
#include <memory>

namespace GameEngine
{
	namespace Library
	{
		class WorldState;
		template <typename T>
		class Event;

		/**
		*	\class	ActionEvent
		*	\brief	This is an Action class that sends Events
		*			(namely EventMessageAttributed) Events on
		*			its Update() method.
		*/
		class ActionEvent final : public Action
		{
			RTTI_DECLARATIONS(ActionEvent, Action);

		public:
			
			/**
			*	\brief				Default constructor. Creates a new Event of type
			*						EventMessageAttributed and stores it for reuse.
			*						Calls Populate.
			*/
									ActionEvent();

			/**
			*	\brief				Sends an EventMessageAttributed after copying all
			*						auxiliary attributes from this into the event message.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState);

			/**
			*	\brief				Calls parent Populate and adds the subtype and the delay as
			*						a prescribed attribute.
			*/
			void					Populate() override;

		private:

			std::string										mSubtype;	/**< The subtype of the event. */
			std::int32_t									mDelay;		/**< The delay to enqueue this event with. */
			std::shared_ptr<Event<EventMessageAttributed>>	mEvent;		/**< The Event that will be sent on Update. */
		};

		ActionFactory(ActionEvent);
	}
}