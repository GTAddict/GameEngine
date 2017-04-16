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
			const std::string SUBTYPES_IDENTIFIER = "subtypes";
		}

		RTTI_DEFINITIONS(ReactionAttributed);

		using namespace ReactionAttributedConstants;

		ReactionAttributed::ReactionAttributed()
		{
			Populate();
			Event<EventMessageAttributed>::Subscribe(*this);
		}

		ReactionAttributed::~ReactionAttributed()
		{
			Event<EventMessageAttributed>::Unsubscribe(*this);
		}

		void ReactionAttributed::Notify(const EventPublisher& event)
		{
			Event<EventMessageAttributed>* eventMessageAttributed = event.As<Event<EventMessageAttributed>>();

			if (eventMessageAttributed)
			{
				EventMessageAttributed& message = eventMessageAttributed->Message();
				for (std::string& subtype : mSubtypes)
				{
					if (subtype == message.GetSubtype())
					{
						VectorType::Iterator itBegin = message.begin() + message.GetPrescribedAttributeCount();
						VectorType::Iterator itEnd = message.end();

						for (; itBegin != itEnd; ++itBegin)
						{
							auto& datumPair = *itBegin;
							(*this)[datumPair->first] = datumPair->second;
						}

						Update(message.GetWorldState());
					}
				}
			}
		}

		void ReactionAttributed::Populate()
		{
			Parent::Populate();
			AddPrescribedAttributeExternal(SUBTYPES_IDENTIFIER, mSubtypes, kMaxSubtypes);
		}
	}
}