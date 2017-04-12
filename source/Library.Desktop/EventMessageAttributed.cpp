#include "pch.h"
#include "EventMessageAttributed.h"
#include "World.h"

namespace GameEngine
{
	namespace Library
	{
		namespace EventMessageAttributedConstants
		{
			const std::string SUBTYPE_IDENTIFIER = "Subtype";
		}

		using namespace EventMessageAttributedConstants;

		EventMessageAttributed::EventMessageAttributed()
			: mpWorld(nullptr)
		{
			AddPrescribedAttributeExternal(SUBTYPE_IDENTIFIER, mSubtype);
		}

		void EventMessageAttributed::SetSubtype(const std::string subtype)
		{
			mSubtype = subtype;
		}

		const std::string& EventMessageAttributed::GetSubtype() const
		{
			return mSubtype;
		}

		void EventMessageAttributed::SetWorld(World& world)
		{
			mpWorld = &world;
		}

		World& EventMessageAttributed::GetWorld()
		{
			return *mpWorld;
		}
	}
}