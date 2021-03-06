#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class WorldState;

		/**
		*	\class	EventMessageAttributed
		*	\brief	This is the message that an	ActionEvent
		*			will send on its Update() method.
		*/
		class EventMessageAttributed final : public Attributed
		{
			RTTI_DECLARATIONS(EventMessageAttributed, Attributed);

		public:

			/**
			*	\brief				Default constructor. Calls Populate.
			*/
									EventMessageAttributed();

			/**
			*	\brief				Sets the subtype of this event message.
			*	\param subtype		The subtype of this event message to be set.
			*/
			void					SetSubtype(const std::string subtype);
			
			/**
			*	\brief				Returns the subtype of this event message.
			*	\return				A const reference to this event message type.
			*/
			const std::string&		GetSubtype() const;

			/**
			*	\brief				Sets the current World State.
			*	\param world		The current World State at the time the message is sent.
			*/
			void					SetWorldState(WorldState& worldState);

			/**
			*	\brief				Returns the World State pointer.
			*	\return				The World State pointer.
			*/
			WorldState&				GetWorldState();

			/**
			*	\brief				Calls Parent Populate and adds the subtype as a
			*						prescribed attribute.
			*/
			void					Populate() override;

		private:

			std::string				mSubtype;		/**< The subtype of this event. */
			WorldState*				mpWorldState;	/**< The World State at the time the message is sent. */
		};
	}
}