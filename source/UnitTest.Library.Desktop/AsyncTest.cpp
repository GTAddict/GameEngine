#include "pch.h"
#include "CppUnitTest.h"
#include <random>
#include "DummySubscriber.h"
#include "MessageAddSubscribers.h"
#include "MessageClearSubscribers.h"
#include "MessageClearEventQueue.h"
#include "MessageEnqueuePublisher.h"
#include "SubscriberModifySubsAndQueue.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAsyncConstants
{
	const std::uint32_t NUM_ITERATIONS		= 500;
	const std::uint32_t DELAY_RANGE_BEGIN	= 0;
	const std::uint32_t DELAY_RANGE_END		= 1000;
	const std::uint32_t SUBS_TO_ADD			= 100;
}

using namespace UnitTestAsyncConstants;

namespace UnitTestAsync
{
	TEST_CLASS(UnitTestAsync)
	{
	private:

		TEST_METHOD(TestBasicFunctionality)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(DELAY_RANGE_BEGIN, DELAY_RANGE_END);

			EventQueue eventQueue;
			GameClock clock;
			GameTime gameTime;
			clock.UpdateGameTime(gameTime);

			DummySubscriber subscribers[NUM_ITERATIONS];

			for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
			{
				std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(DummyStruct());
				eventQueue.Enqueue(e, gameTime, std::chrono::milliseconds(dis(gen)));
			}

			while (!eventQueue.IsEmpty())
			{
				clock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}

			for (int i = 0; i < NUM_ITERATIONS; ++i)
			{
				Assert::IsTrue(subscribers[i].ReceivedNotification());
			}
		}

		TEST_METHOD(TestAddSubsInBetweenDelivery)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(DELAY_RANGE_BEGIN, DELAY_RANGE_END);

			EventQueue eventQueue;
			GameClock clock;
			GameTime gameTime;
			clock.UpdateGameTime(gameTime);

			DummySubscriber subscribers[NUM_ITERATIONS];
			
			SubscriberModifySubsAndQueue sub;
			for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
			{
				std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(DummyStruct());
				eventQueue.Enqueue(e, gameTime, std::chrono::milliseconds(dis(gen)));
			}
			SubscriberModifySubsAndQueue sub2;

			std::shared_ptr<Event<MessageAddSubscribers>> event = std::make_shared<Event<MessageAddSubscribers>>(MessageAddSubscribers(SUBS_TO_ADD));
			eventQueue.Send(event);

			while (!eventQueue.IsEmpty())
			{
				clock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}

			for (int i = 0; i < NUM_ITERATIONS; ++i)
			{
				Assert::IsTrue(subscribers[i].ReceivedNotification());
			}
		}

		TEST_METHOD(TestClearSubsInBetweenDelivery)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(DELAY_RANGE_BEGIN, DELAY_RANGE_END);

			EventQueue eventQueue;
			GameClock clock;
			GameTime gameTime;
			clock.UpdateGameTime(gameTime);

			DummySubscriber subscribers[NUM_ITERATIONS];
			SubscriberModifySubsAndQueue sub;
			for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
			{
				std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(DummyStruct());
				eventQueue.Enqueue(e, gameTime, std::chrono::milliseconds(dis(gen)));
			}
			SubscriberModifySubsAndQueue sub2;
			std::shared_ptr<Event<MessageClearSubscribers>> event = std::make_shared<Event<MessageClearSubscribers>>(MessageClearSubscribers());
			eventQueue.Send(event);

			while (!eventQueue.IsEmpty())
			{
				clock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}
		}

		TEST_METHOD(TestAddPublishersInBetweenDelivery)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(DELAY_RANGE_BEGIN, DELAY_RANGE_END);
			std::mutex randMutex;

			EventQueue eventQueue;
			GameClock clock;
			GameTime gameTime;
			clock.UpdateGameTime(gameTime);

			DummySubscriber subscribers[NUM_ITERATIONS];
			SubscriberModifySubsAndQueue sub;
			for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
			{
				std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(DummyStruct());
				eventQueue.Enqueue(e, gameTime, std::chrono::milliseconds(dis(gen)));
			}
			SubscriberModifySubsAndQueue sub2;
			std::shared_ptr<Event<MessageEnqueuePublisher>> event = std::make_shared<Event<MessageEnqueuePublisher>>(MessageEnqueuePublisher(SUBS_TO_ADD, &eventQueue, &gen, &dis, &randMutex, &clock, &gameTime));
			eventQueue.Send(event);

			while (!eventQueue.IsEmpty())
			{
				clock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}

			for (int i = 0; i < NUM_ITERATIONS; ++i)
			{
				Assert::IsTrue(subscribers[i].ReceivedNotification());
			}
		}

		TEST_METHOD(TestClearQueueInBetweenDelivery)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(DELAY_RANGE_BEGIN, DELAY_RANGE_END);
			std::mutex randMutex;

			EventQueue eventQueue;
			GameClock clock;
			GameTime gameTime;
			clock.UpdateGameTime(gameTime);

			DummySubscriber subscribers[NUM_ITERATIONS];
			SubscriberModifySubsAndQueue sub;
			for (std::uint32_t i = 0; i < NUM_ITERATIONS; ++i)
			{
				std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(DummyStruct());
				eventQueue.Enqueue(e, gameTime, std::chrono::milliseconds(dis(gen)));
			}
			SubscriberModifySubsAndQueue sub2;
			std::shared_ptr<Event<MessageClearEventQueue>> event = std::make_shared<Event<MessageClearEventQueue>>(MessageClearEventQueue(&eventQueue));
			eventQueue.Send(event);

			while (!eventQueue.IsEmpty())
			{
				clock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}
		}

	public:

#ifdef _DEBUG
		TEST_METHOD_INITIALIZE(Initialize)
		{
			{
				DummySubscriber s[NUM_ITERATIONS];
			}
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Your code is leaking memory!");
			}
		}

	private:
		static _CrtMemState sStartMemState;
#endif

	};

#ifdef _DEBUG
	_CrtMemState UnitTestAsync::sStartMemState;
#endif
}