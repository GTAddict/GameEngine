#pragma once

namespace GameEngine
{
	namespace Library
	{
		class EventQueue;

		class MessageClearEventQueue
		{
		public:
			explicit MessageClearEventQueue(EventQueue* eventQueue);
			
			EventQueue* GetEventQueue() const;

		private:

			EventQueue* mEventQueue;
		};
	}
}

