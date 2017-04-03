#include "pch.h"
#include "Action.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionConstants
		{
			const std::string NAME_IDENTIFIER = "Name";
		}

		RTTI_DEFINITIONS(Action);

		using namespace ActionConstants;

		Action::Action()
		{
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
		}

		const std::string& Action::Name() const
		{
			return mName;
		}

		void Action::SetName(const std::string& name)
		{
			if (!name.length())
			{
				throw std::invalid_argument("Cannot set an empty name.");
			}

			mName = name;
		}
	}
}