#include "pch.h"
#include "Action.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ActionConstants
		{
			const std::string NAME_IDENTIFIER = "name";
		}

		RTTI_DEFINITIONS(Action);

		using namespace ActionConstants;

		Action::Action()
		{
			Populate();
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

		void Action::Populate()
		{
			Parent::Populate();
			AddPrescribedAttributeExternal(NAME_IDENTIFIER, mName);
		}
	}
}