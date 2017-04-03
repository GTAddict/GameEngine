#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"

namespace UnitTestStackConstants
{
	const std::uint32_t kTHIRTY = 30;
	const std::uint32_t kZERO = 0;
}

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;
using namespace UnitTestStackConstants;

namespace UnitTestStack
{
	TEST_CLASS(UnitTestStack)
	{
	public:

		TEST_METHOD_EXTENSIVE(TestConstructor)
			TEST_METHOD_EXTENSIVE(TestPushPopTopSizeEmpty)
			TEST_METHOD_EXTENSIVE(TestCopySemantics)
			TEST_METHOD_EXTENSIVE(TestMoveSemantics)
			TEST_METHOD_EXTENSIVE(TestExceptions)

	private:

		template <typename T>
		void TestConstructor()
		{
			Stack<T> stack;
			Vector<T> userDefinedContainer;
			Stack<T> anotherStack(userDefinedContainer);
			
			for (int i = startValue; i <= endValue; ++i)
			{
				stack.Push(ConvertValue<T>(i));
				anotherStack.Push(ConvertValue<T>(i));
			}

			Assert::IsTrue(stack == anotherStack);
			stack.Push(ConvertValue<T>(startValue));
			Assert::IsTrue(stack != anotherStack);
		}

		template <typename T>
		void TestPushPopTopSizeEmpty()
		{
			Stack<T> stack;

			for (int i = startValue; i <= endValue; ++i)
			{
				stack.Push(ConvertValue<T>(i));
				Assert::IsTrue(ConvertValue<T>(i) == stack.Top());
			}

			Assert::IsTrue(expectedNumElements == stack.Size());

			const Stack<T> constStack = stack;
			Assert::IsTrue(constStack.Top() == stack.Top());

			for (int i = endValue; i >= startValue; --i)
			{
				Assert::IsTrue(ConvertValue<T>(i) == stack.Top());
				stack.Pop();
			}

			Assert::IsTrue(stack.IsEmpty());
		}

		template <typename T>
		void TestCopySemantics()
		{
			Stack<T> stack;
			for (int i = startValue; i <= endValue; ++i)
			{
				stack.Push(ConvertValue<T>(i));
			}

			Stack<T> stackConstruct(stack);
			Stack<T> stackAssign;
			stackAssign = stackConstruct;

			Assert::IsTrue(stackConstruct == stackAssign);

			// Self assignment test.
			stackAssign = stackAssign;
		}

		template <typename T>
		void TestMoveSemantics()
		{
			Stack<T> stack;
			for (int i = startValue; i <= endValue; ++i)
			{
				stack.Push(ConvertValue<T>(i));
			}

			Stack<T> stackCopy = stack;
			Stack<T> stackConstruct(std::move(stack));
			Assert::IsTrue(stackCopy == stackConstruct);

			Stack<T> stackAssign;
			stackAssign = std::move(stackConstruct);
			Assert::IsTrue(stackAssign == stackCopy);

			// Self assignment test.
			stackAssign == std::move(stackAssign);
		}

		template <typename T>
		void TestExceptions()
		{
			Stack<T> stack;
			Assert::ExpectException<std::out_of_range>([&stack]{stack.Pop();});
			Assert::ExpectException<std::out_of_range>([&stack]{stack.Top(); });
		}

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);

			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Your code is leaking memory!");
			}
#endif
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestStack::sStartMemState;
#endif
}