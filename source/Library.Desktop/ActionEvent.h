#pragma once
#include "Action.h"

namespace GameEngine
{
	namespace Library
	{
		class WorldState;

		/**
		*	\class	ActionEvent
		*	\brief	This is an Action class that sends Events
		*			(namely EventMessageAttributed) Events on
		*			its Update() method.
		*/
		class ActionEvent final : public Action
		{
		public:
			
			/**
			*	\brief				Default constructor. Adds the subtype and the
			*						delay as a prescribed attribute.
			*/
									ActionEvent();

			/**
			*	\brief				Sends an EventMessageAttributed after copying all
			*						auxiliary attributes from this into the event message.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState);

		private:

			std::string		mSubtype;	/**< The subtype of the event. */
			std::int32_t	mDelay;		/**< The delay to enqueue this event with. */
		};
	}
}