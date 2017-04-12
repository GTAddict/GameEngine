#include "pch.h"
#include "ReactionAttributed.h"
#include "Event.h"
#include "EventMessageAttributed.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ReactionAttributedConstants
		{
			const std::string SUBTYPES_IDENTIFIER = "Subtypes";
		}

		using namespace ReactionAttributedConstants;

		ReactionAttributed::ReactionAttributed()
		{
			AddPrescribedAttributeInternal(SUBTYPES_IDENTIFIER, mSubtypes, kMaxSubtypes);
			Event<EventMessageAttributed>::Subscribe(*this);
		}

		ReactionAttributed::~ReactionAttributed()
		{
			Event<EventMessageAttributed>::Unsubscribe(*this);
		}

		void ReactionAttributed::Notify(const EventPublisher& event)
		{
			EventMessageAttributed* message = event.As<EventMessageAttributed>();
			if (message)
			{
				for (std::string& subtype : mSubtypes)
				{
					if (subtype == message->GetSubtype())
					{
						// TODO Copy event args
						// World& world = message->GetWorld();
						// TODO Get WorldState and Update with it
						// Update(world);
					}
				}
			}
		}
	}
}