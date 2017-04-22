#include "pch.h"
#include "MessageAddSubscribers.h"

namespace GameEngine
{
	namespace Library
	{
		MessageAddSubscribers::MessageAddSubscribers(const std::uint32_t subscribersToAdd)
		{
			mSubscribersToAdd = subscribersToAdd;
		}

		std::uint32_t MessageAddSubscribers::GetSubscribersToAdd() const
		{
			return mSubscribersToAdd;
		}
	}
}
