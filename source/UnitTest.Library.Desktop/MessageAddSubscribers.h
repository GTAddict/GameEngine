#pragma once

namespace GameEngine
{
	namespace Library
	{
		class MessageAddSubscribers
		{
		public:
			explicit MessageAddSubscribers(const std::uint32_t subscribersToAdd);

			std::uint32_t GetSubscribersToAdd() const;

		private:
			std::uint32_t mSubscribersToAdd;
		};
	}
}
