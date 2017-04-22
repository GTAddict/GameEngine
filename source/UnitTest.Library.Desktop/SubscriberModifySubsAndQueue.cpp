#include "pch.h"
#include "SubscriberModifySubsAndQueue.h"
#include "MessageAddSubscribers.h"
#include "MessageClearSubscribers.h"
#include "MessageEnqueuePublisher.h"
#include "MessageClearEventQueue.h"
#include "DummySubscriber.h"

namespace GameEngine
{
	namespace Library
	{
		SubscriberModifySubsAndQueue::SubscriberModifySubsAndQueue()
		{
			Event<MessageAddSubscribers>::Subscribe(*this);
			Event<MessageClearEventQueue>::Subscribe(*this);
			Event<MessageClearSubscribers>::Subscribe(*this);
			Event<MessageEnqueuePublisher>::Subscribe(*this);
		}

		SubscriberModifySubsAndQueue::~SubscriberModifySubsAndQueue()
		{
			Event<MessageAddSubscribers>::Unsubscribe(*this);
			Event<MessageClearEventQueue>::Unsubscribe(*this);
			Event<MessageClearSubscribers>::Unsubscribe(*this);
			Event<MessageEnqueuePublisher>::Unsubscribe(*this);
		}

		void SubscriberModifySubsAndQueue::Notify(const EventPublisher& event)
		{
			Event<MessageAddSubscribers>* e = event.As<Event<MessageAddSubscribers>>();
			if (e)
			{
				for (std::uint32_t i = 0; i < e->Message().GetSubscribersToAdd(); ++i)
				{
					std::shared_ptr<DummySubscriber> d = std::make_shared<DummySubscriber>();
				}
			}

			Event<MessageClearSubscribers>* cs = event.As<Event<MessageClearSubscribers>>();
			if (cs)
			{
				Event<DummyStruct>::UnsubscribeAll();
				Event<MessageAddSubscribers>::UnsubscribeAll();
				Event<MessageClearSubscribers>::UnsubscribeAll();
			}

			Event<MessageEnqueuePublisher>* eq = event.As<Event<MessageEnqueuePublisher>>();
			if (eq)
			{
				for (std::uint32_t i = 0; i < eq->Message().GetPublishersToEnqueue(); ++i)
				{
					std::shared_ptr<Event<DummyStruct>> ev = std::make_shared<Event<DummyStruct>>(DummyStruct());
					int randomVal;
					_CRITICAL(*eq->Message().GetMutex());
					randomVal = (*eq->Message().GetDis())(*eq->Message().GetGen());
					_CRITICAL_END
					eq->Message().GetClock()->UpdateGameTime(*eq->Message().GetGameTime());
					eq->Message().GetEventQueue()->Enqueue(ev, *eq->Message().GetGameTime(), std::chrono::milliseconds(randomVal));
				}
			}

			Event<MessageClearEventQueue>* cq = event.As<Event<MessageClearEventQueue>>();
			if (cq)
			{
				cq->Message().GetEventQueue()->Clear();
			}

		}
	}
}
