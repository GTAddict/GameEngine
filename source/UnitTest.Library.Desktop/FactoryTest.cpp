#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFactory
{
	TEST_CLASS(UnitTestFactory)
	{
	private:

		TEST_METHOD(TestConstructor)
		{
			ConcreteFactory(RTTI, AttributedFoo);
			AttributedFooFactory f;
			RTTI* attributedFoo = Factory<RTTI>::Create("AttributedFoo");
			Assert::IsTrue(attributedFoo->Is(AttributedFoo::TypeIdClass()));
			delete attributedFoo;
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
	_CrtMemState UnitTestFactory::sStartMemState;
#endif
}