#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
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
			ConcreteFactory(Scope, Attributed);

			FooFactory fooFactory;
			AttributedFooFactory attributedFooFactory;
			AttributedFactory attributedFactory;

			RTTI* attributedFoo = Factory<RTTI>	::Create("AttributedFoo");
			RTTI* foo			= Factory<RTTI>	::Create("Foo");
			Scope* attributed	= Factory<Scope>::Create("Attributed");

			Assert::IsTrue(Factory<RTTI>::Find("Foo") == &fooFactory);
			Assert::IsTrue(Factory<RTTI>::Find("AttributedFoo") == &attributedFooFactory);
			Assert::IsTrue(Factory<Scope>::Find("Attributed") == &attributedFactory);
			Assert::IsNull(Factory<RTTI>::Create("BLAHH"));
			Assert::IsNull(Factory<Scope>::Create("BLAHH"));

			Assert::IsTrue(foo->Is(Foo::TypeIdClass()));
			Assert::IsTrue(attributedFoo->Is(AttributedFoo::TypeIdClass()));
			Assert::IsTrue(attributed->Is(Attributed::TypeIdClass()));
			Assert::IsTrue(foo->As<Foo>()->Equals(static_cast<Foo*>(foo)));
			Assert::IsNotNull(attributedFoo->As<AttributedFoo>());
			Assert::IsNotNull(attributed->As<Attributed>());
			Assert::IsTrue(foo->ToString() == "RTTI");
			Assert::IsTrue(attributedFoo->ToString() == "RTTI");
			Assert::IsTrue(attributed->ToString() == "RTTI");
			
			Assert::IsNull(Factory<RTTI>::Find("Attributed"));
			Assert::IsNull(Factory<Scope>::Find("Foo"));
			Assert::IsNull(Factory<Scope>::Find("AttributedFoo"));

			int counter = 0;
			auto it = Factory<RTTI>::begin();
			auto itEnd = Factory<RTTI>::end();
			for (; it != itEnd; ++it)
			{
				++counter;
			}
			Assert::IsTrue(counter == 2);

			auto anotherIt = Factory<Scope>::begin();
			auto anotherItEnd = Factory<Scope>::end();
			counter = 0;
			for (; anotherIt != anotherItEnd; ++anotherIt)
			{
				++counter;
			}
			Assert::IsTrue(counter == 1);

			delete foo;
			delete attributedFoo;
			delete attributed;
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