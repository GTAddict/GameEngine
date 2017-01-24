#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"

namespace UnitTestVectorConstants
{
	const int startValue = 65;
	const int endValue = 81;
	const float divisor = 100.0f;
	const unsigned int expectedNumElements = endValue - startValue + 1;
	const uint32_t kTHIRTY = 30;
	const uint32_t kZERO = 0;
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestVectorConstants;

namespace UnitTestVector
{
	TEST_CLASS(UnitTestVector)
	{
	private:

		template <typename T>
		void TestReserveAndCapacity_Impl()
		{
			Vector<T> vector;
			Assert::AreEqual(DEFAULT_CONTAINER_SIZE, vector.Capacity());

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Vector<T> anotherVector;
			anotherVector.Reserve(kTHIRTY);

			for (int i = startValue; i <= endValue; ++i)
			{
				anotherVector.PushBack(ConvertValue<T>(i));
			}

			Assert::AreEqual(kTHIRTY, anotherVector.Capacity());
			anotherVector.Reserve(kZERO);
			Assert::AreEqual(kTHIRTY, anotherVector.Capacity());
		}

		template <typename T>
		void TestBack_Impl()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
				Assert::AreEqual(ConvertValue<T>(i), vector.Back());
			}

			Assert::AreEqual(expectedNumElements, vector.Size());

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PopBack();
			}

			Assert::IsTrue(vector.IsEmpty());
		}

		template <typename T>
		void TestFront_Impl()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
				Assert::AreEqual(ConvertValue<T>(startValue), vector.Front());
			}
		}

		template <typename T>
		void TestRandomAccess_Impl()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(ConvertValue<T>(i), vector[i - startValue]);
				Assert::AreEqual(ConvertValue<T>(i), vector.At(i - startValue));
			}
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

		TEST_METHOD(TestReserveAndCapacity)
		{
			TestReserveAndCapacity_Impl<char>();
			TestReserveAndCapacity_Impl<bool>();
			TestReserveAndCapacity_Impl<int>();
			TestReserveAndCapacity_Impl<float>();
			TestReserveAndCapacity_Impl<DummyStruct>();
		}

		TEST_METHOD(TestBack)
		{
			TestBack_Impl<char>();
			TestBack_Impl<bool>();
			TestBack_Impl<int>();
			TestBack_Impl<float>();
			TestBack_Impl<DummyStruct>();
		}

		TEST_METHOD(TestFront)
		{
			TestFront_Impl<char>();
			TestFront_Impl<bool>();
			TestFront_Impl<int>();
			TestFront_Impl<float>();
			TestFront_Impl<DummyStruct>();
		}

		TEST_METHOD(TestRandomAccess)
		{
			TestRandomAccess_Impl<char>();
			TestRandomAccess_Impl<bool>();
			TestRandomAccess_Impl<int>();
			TestRandomAccess_Impl<float>();
			TestRandomAccess_Impl<DummyStruct>();
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestVector::sStartMemState;
#endif
}