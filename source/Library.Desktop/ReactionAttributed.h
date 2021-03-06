#pragma once
#include "Reaction.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	ReactionAttributed
		*	\brief	This is a Reaction class that responds
		*			to EventMessageAttributed Events.
		*/
		class ReactionAttributed final : public Reaction
		{
			RTTI_DECLARATIONS(ReactionAttributed, Reaction);

			static const std::uint32_t kMaxSubtypes = 255;

		public:

			/**
			*	\brief				Default constructor. Calls Populate. Also
			*						subscribes to EventMessageAttributed messages.
			*/
									ReactionAttributed();
			
			/**
			*	\brief				Default destructor. Adds the subtype as a
			*						prescribed attribute. Unsubscribes itself
			*						from EventMessageAttributed messages.
			*/
									~ReactionAttributed();

			/**
			*	\brief				Called when an EventMessageAttributed event is
			*						sent. Looks for matching arguments and calls
			*						Update on the base ActionList if any matches
			*						were found, after copying the arguments over.
			*	\param event		The EventPublisher who sent the event.
			*/
			void					Notify(const EventPublisher& event) override;

			/**
			*	\brief				Calls Parent Populate and adds the subtypes array
			*						as a prescribed attribute.
			*/
			void					Populate() override;

		private:

			std::string				mSubtypes[kMaxSubtypes];	/**< The subtypes this Reaction can respond to. */
		};

		ReactionFactory(ReactionAttributed);
	}
}