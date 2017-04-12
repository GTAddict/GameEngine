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
			static const std::uint32_t kMaxSubtypes = 5;

		public:

			/**
			*	\brief				Default constructor. Adds the subtypes array
			*						as a prescribed attribute. Also subscribes to
			*						EventMessageAttributed messages.
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

		private:

			std::string	mSubtypes[kMaxSubtypes];	/**< The subtypes this Reaction should respond to. */
		};

	}
}