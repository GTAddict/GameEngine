#include "pch.h"
#include "CppUnitTest.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestEvent
{
	TEST_CLASS(UnitTestEvent)
	{
	private:

		TEST_METHOD(TestConstructor)
		{
			EventQueue e;
			DummyStruct d;
			Event<DummyStruct> event(d, false);
			static int called = 0;
			class BlahBloo : public EventSubscriber
			{
			public:
				BlahBloo()
				{
					Event<DummyStruct>::Subscribe(*this);
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
			e.Send(event);
			Assert::IsTrue(called == 1);
			e.Enqueue(event, g, std::chrono::milliseconds(0));
			e.Update(g);
			Assert::IsTrue(called == 2);
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