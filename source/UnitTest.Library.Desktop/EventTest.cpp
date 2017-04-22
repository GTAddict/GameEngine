#include "pch.h"
#include "CppUnitTest.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestEvent
{
	TEST_CLASS(UnitTestEvent)
	{
	private:

		TEST_METHOD(TestBasicFunctionality)
		{
			EventQueue e;
			DummyStruct d;
			std::shared_ptr<Event<DummyStruct>> event = std::make_shared<Event<DummyStruct>>(d);

			static int called = 0;
			class BlahBloo : public EventSubscriber
			{
			public:
				BlahBloo()
				{
					Event<DummyStruct>::Subscribe(*this);
				}

				~BlahBloo()
				{
					Event<DummyStruct>::Unsubscribe(*this);
				}

				void Notify(const EventPublisher& event) override
				{
					event;
					++called;
				}
			};
			BlahBloo b;
			GameTime g;
			GameClock gam;
			gam.UpdateGameTime(g);
			event->SetTime(g.CurrentTime(), std::chrono::milliseconds(0));
			e.Send(event);
			Assert::IsTrue(called == 1);
			e.Enqueue(event, g, std::chrono::milliseconds(0));
			e.Update(g);
			Assert::IsTrue(called == 2);
		}

		TEST_METHOD(TestPublisher)
		{
			EventQueue eventQueue;
			DummyStruct d;
			std::shared_ptr<Event<DummyStruct>> e = std::make_shared<Event<DummyStruct>>(d);
			std::shared_ptr<Event<DummyStruct>> delEvent = std::make_shared<Event<DummyStruct>>(d);
			Assert::IsTrue(d == e->Message());
			Assert::IsTrue(d == delEvent->Message());
			GameClock clock;
			GameTime gameTime;
			std::chrono::milliseconds delay(1);
			clock.UpdateGameTime(gameTime);
			eventQueue.Enqueue(e, gameTime, delay);
			eventQueue.Enqueue(delEvent, gameTime, delay);
			Assert::IsTrue(eventQueue.Size() == 2);
			Assert::IsFalse(eventQueue.IsEmpty());
			Assert::IsTrue(gameTime.CurrentTime() == e->TimeEnqueued());
			Assert::IsTrue(delay == e->Delay());
			Assert::IsFalse(e->IsExpired(gameTime.CurrentTime()));
			eventQueue.Update(gameTime);
			Assert::IsTrue(eventQueue.Size() == 2);
			Assert::IsFalse(eventQueue.IsEmpty());
			Sleep(1);
			clock.UpdateGameTime(gameTime);
			Assert::IsTrue(e->IsExpired(gameTime.CurrentTime()));
			eventQueue.Update(gameTime);
			Assert::IsTrue(eventQueue.Size() == 0);
			Assert::IsTrue(eventQueue.IsEmpty());
			Event<DummyStruct>::UnsubscribeAll();
		}

		TEST_METHOD(TestRTTI)
		{
			Event<DummyStruct>* event = new Event<DummyStruct>(DummyStruct());
			Assert::IsTrue(event->TypeName() == "Event<T>");
			Assert::IsTrue(event->TypeIdClass() == Event<DummyStruct>::TypeIdClass());
			Assert::IsTrue(event->TypeIdInstance() == event->TypeIdClass());
			Assert::IsTrue(event->Is(Event<DummyStruct>::TypeIdClass()));
			Assert::IsTrue(event->Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(event->Is("Event<T>"));
			Assert::IsTrue(event->Is("EventPublisher"));
			Assert::IsTrue(event->Equals(event));
			Assert::IsTrue(event->ToString() == "RTTI");
			Assert::IsTrue(event->As<EventPublisher>() == static_cast<EventPublisher*>(event));

			EventPublisher* publisher = event->As<EventPublisher>();
			Assert::IsTrue(publisher->TypeName() == "EventPublisher");
			Assert::IsTrue(publisher->TypeIdClass() == EventPublisher::TypeIdClass());
			Assert::IsTrue(publisher->TypeIdInstance() == Event<DummyStruct>::TypeIdClass());
			Assert::IsTrue(publisher->Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(publisher->Is("Event<T>"));
			Assert::IsTrue(publisher->Is("EventPublisher"));
			Assert::IsTrue(publisher->Equals(publisher));
			Assert::IsTrue(publisher->ToString() == "RTTI");
			Assert::IsTrue(publisher->As<EventPublisher>() == static_cast<EventPublisher*>(event));

			delete event;
		}

		TEST_METHOD(TestCopyMoveSemantics)
		{
			DummyStruct d1, d2;
			Event<DummyStruct> event(d1);
			Event<DummyStruct> anotherEvent(d2);
			
			Event<DummyStruct> copyConstruct(event);
			Event<DummyStruct> moveConstruct(event);
			
			Event<DummyStruct> copyAssign(d1);
			copyAssign = anotherEvent;
			Event<DummyStruct> moveAssign(d1);
			moveAssign = std::move(anotherEvent);
		}

	public:

#ifdef _DEBUG
		TEST_METHOD_INITIALIZE(Initialize)
		{
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
	_CrtMemState UnitTestEvent::sStartMemState;
#endif
}