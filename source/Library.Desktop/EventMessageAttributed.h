#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class World;

		/**
		*	\class	EventMessageAttributed
		*	\brief	This is the message that an	ActionEvent
		*			will send on its Update() method.
		*/
		class EventMessageAttributed : public Attributed
		{
		public:

			/**
			*	\brief				Default constructor. Adds the subtype as a
			*						prescribed attribute.
			*/
									EventMessageAttributed();

			/**
			*	\brief				Default destructor.
			*/
			virtual					~EventMessageAttributed() = default;

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
			*	\brief				Sets the world that will process this event message.
			*	\param world		The world that is to process this event message.
			*/
			void					SetWorld(World& world);

			/**
			*	\brief				Returns the world that should process this event message.
			*	\return				The world that is to process this event message.
			*/
			World&					GetWorld();

		private:

			std::string		mSubtype;	/**< The subtype of this event. */
			World*			mpWorld;	/**< The world that will process this message. */


		};
	}
}