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
						VectorType::Iterator itBegin = message->begin() + message->GetPrescribedAttributeCount();
						VectorType::Iterator itEnd = message->end();

						for (; itBegin != itEnd; ++itBegin)
						{
							auto& datumPair = *itBegin;
							(*this)[datumPair->first] = datumPair->second;
						}
						
						Update(message->GetWorldState());
					}
				}
			}
		}
	}
}