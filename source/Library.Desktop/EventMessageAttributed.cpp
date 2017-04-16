#include "pch.h"
#include "EventMessageAttributed.h"
#include "World.h"

namespace GameEngine
{
	namespace Library
	{
		namespace EventMessageAttributedConstants
		{
			const std::string SUBTYPE_IDENTIFIER = "subtype";
		}

		RTTI_DEFINITIONS(EventMessageAttributed);

		using namespace EventMessageAttributedConstants;

		EventMessageAttributed::EventMessageAttributed()
			: mpWorldState(nullptr)
		{
			Populate();
		}

		void EventMessageAttributed::SetSubtype(const std::string subtype)
		{
			mSubtype = subtype;
		}

		const std::string& EventMessageAttributed::GetSubtype() const
		{
			return mSubtype;
		}

		void EventMessageAttributed::SetWorldState(WorldState& worldState)
		{
			mpWorldState = &worldState;
		}

		WorldState& EventMessageAttributed::GetWorldState()
		{
			return *mpWorldState;
		}

		void EventMessageAttributed::Populate()
		{
			Parent::Populate();
			AddPrescribedAttributeExternal(SUBTYPE_IDENTIFIER, mSubtype);
		}
	}
}