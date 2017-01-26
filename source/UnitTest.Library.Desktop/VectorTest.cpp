#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"

namespace UnitTestVectorConstants
{
	const std::uint32_t kTHIRTY = 30;
	const std::uint32_t kZERO = 0;

	const std::uint32_t customCapacityDefaultSize = 50;
	const std::uint32_t smallerCustomCapacitySize = 10;
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;
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
			Assert::AreEqual(DEFAULT_CONTAINER_CAPACITY, vector.Capacity());

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
			
			Vector<T> aThirdVector(kTHIRTY);
			Assert::AreEqual(kTHIRTY, aThirdVector.Capacity());
		}

		std::uint32_t GetNewCapacityCustom(std::uint32_t size, std::uint32_t capacity)
		{
			if (capacity == 0)
			{
				return customCapacityDefaultSize;
			}
			else
			{
				float fractionUsed = static_cast<float>(size / capacity);
				return static_cast<std::uint32_t>(capacity + capacity * fractionUsed);
			}
		}

		template <typename T>
		void TestCustomCapacityFn_Impl()
		{
			Vector<T> vector(BIND_TO_GETCAPACITYFN_T(&UnitTestVector::GetNewCapacityCustom));
			Assert::AreEqual(customCapacityDefaultSize, vector.Capacity());

			Vector<T> anotherVector(BIND_TO_GETCAPACITYFN_T(&UnitTestVector::GetNewCapacityCustom), smallerCustomCapacitySize);
			Assert::AreEqual(smallerCustomCapacitySize, anotherVector.Capacity());

			for (int i = startValue; i <= endValue; ++i)
			{
				anotherVector.PushBack(ConvertValue<T>(i));
			}

			Assert::AreEqual(smallerCustomCapacitySize * 2, anotherVector.Capacity());
		}

		template <typename T>
		void TestBack_Impl()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
				Assert::IsTrue(ConvertValue<T>(i) == vector.Back());
			}

			Assert::IsTrue(expectedNumElements == vector.Size());

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
				Assert::IsTrue(ConvertValue<T>(startValue) == vector.Front());
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
				Assert::IsTrue(ConvertValue<T>(i) == vector[i - startValue]);
				Assert::IsTrue(ConvertValue<T>(i) == vector.At(i - startValue));
			}
		}

		template <typename T>
		void TestCopySemantics_Impl()
		{
			Vector<T> vector;
			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Vector<T> vectorConstruct(vector);
			Vector<T> vectorAssign;
			vectorAssign = vectorConstruct;

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::IsTrue(ConvertValue<T>(i) == vectorConstruct.At(i - startValue));
				Assert::IsTrue(ConvertValue<T>(i) == vectorAssign.At(i - startValue));
			}
		}

		template <typename T>
		void TestMoveSemantics_Impl()
		{
			Vector<T> vector;
			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Vector<T> vectorConstruct(std::move(vector));
			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::IsTrue(ConvertValue<T>(i) == vectorConstruct.At(i - startValue));
			}
			
			Vector<T> vectorAssign;
			vectorAssign = std::move(vectorConstruct);
			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::IsTrue(ConvertValue<T>(i) == vectorAssign.At(i - startValue));
			}
		}

		template <typename T>
		void TestShrinkToFit_Impl()
		{
			Vector<T> vector;
			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Assert::IsTrue(vector.Size() == expectedNumElements);

			vector.ShrinkToFit();
			Assert::IsTrue(vector.Size() == expectedNumElements);
			Assert::IsTrue(vector.Capacity() == expectedNumElements);

			vector.Clear();
			vector.ShrinkToFit();
			Assert::IsTrue(vector.Size() == 0);
			Assert::IsTrue(vector.Capacity() == 0);

			vector.PushBack(ConvertValue<T>(startValue));
			Assert::IsTrue(vector.Size() == 1);
			Assert::IsTrue(vector.Capacity() == DEFAULT_CONTAINER_CAPACITY);
		}

		template <typename T>
		void TestIterators_Impl()
		{
			Vector<T> vector;
			vector.PushBack(ConvertValue<T>(startValue));

			Vector<T>::Iterator it, itEnd;
			it		= vector.begin();
			itEnd	= vector.end();

			Assert::IsTrue(it != itEnd);
			Assert::IsTrue(it < itEnd);
			Assert::IsTrue(it <= itEnd);
			Assert::IsTrue(itEnd > it);
			Assert::IsTrue(itEnd >= it);

			Assert::IsTrue(it + 1 == itEnd);
			Assert::IsTrue(itEnd - 1 == it);
			Assert::IsTrue(itEnd - it == 1);

			Assert::IsTrue(++it == itEnd);
			Assert::IsTrue(it++ == itEnd);

			Assert::IsTrue(it == ++itEnd);
			Assert::IsTrue(it <= itEnd);
			Assert::IsTrue(it >= itEnd);

			it = vector.begin();
			itEnd = vector.end();

			Vector<T>::Iterator copyIt = it;
			Assert::IsTrue(copyIt == vector.begin());

			copyIt = itEnd;
			Assert::IsTrue(copyIt == vector.end());

			Vector<T>::Iterator moveIt = std::move(it);
			Assert::IsTrue(moveIt == vector.begin());

			moveIt = std::move(itEnd);
			Assert::IsTrue(moveIt == vector.end());

			Vector<T> anEmptyVector, anotherEmptyVector;
			
			Assert::IsTrue(anEmptyVector.begin() != anotherEmptyVector.begin());
			Assert::IsTrue(anEmptyVector.end() != anotherEmptyVector.end());

			Assert::IsTrue(anEmptyVector.begin() == anEmptyVector.begin());
			Assert::IsTrue(anotherEmptyVector.end() == anotherEmptyVector.end());
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

			TestReserveAndCapacity_Impl<char*>();
			TestReserveAndCapacity_Impl<bool*>();
			TestReserveAndCapacity_Impl<int*>();
			TestReserveAndCapacity_Impl<float*>();
			TestReserveAndCapacity_Impl<DummyStruct*>();

		}

		TEST_METHOD(TestCustomCapacityFn)
		{
			TestCustomCapacityFn_Impl<char>();
			TestCustomCapacityFn_Impl<bool>();
			TestCustomCapacityFn_Impl<int>();
			TestCustomCapacityFn_Impl<float>();
			TestCustomCapacityFn_Impl<DummyStruct>();

			TestCustomCapacityFn_Impl<char*>();
			TestCustomCapacityFn_Impl<bool*>();
			TestCustomCapacityFn_Impl<int*>();
			TestCustomCapacityFn_Impl<float*>();
			TestCustomCapacityFn_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestBack)
		{
			TestBack_Impl<char>();
			TestBack_Impl<bool>();
			TestBack_Impl<int>();
			TestBack_Impl<float>();
			TestBack_Impl<DummyStruct>();

			TestBack_Impl<char*>();
			TestBack_Impl<bool*>();
			TestBack_Impl<int*>();
			TestBack_Impl<float*>();
			TestBack_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestFront)
		{
			TestFront_Impl<char>();
			TestFront_Impl<bool>();
			TestFront_Impl<int>();
			TestFront_Impl<float>();
			TestFront_Impl<DummyStruct>();

			TestFront_Impl<char*>();
			TestFront_Impl<bool*>();
			TestFront_Impl<int*>();
			TestFront_Impl<float*>();
			TestFront_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestRandomAccess)
		{
			TestRandomAccess_Impl<char>();
			TestRandomAccess_Impl<bool>();
			TestRandomAccess_Impl<int>();
			TestRandomAccess_Impl<float>();
			TestRandomAccess_Impl<DummyStruct>();

			TestRandomAccess_Impl<char*>();
			TestRandomAccess_Impl<bool*>();
			TestRandomAccess_Impl<int*>();
			TestRandomAccess_Impl<float*>();
			TestRandomAccess_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestCopySemantics)
		{
			TestCopySemantics_Impl<char>();
			TestCopySemantics_Impl<bool>();
			TestCopySemantics_Impl<int>();
			TestCopySemantics_Impl<float>();
			TestCopySemantics_Impl<DummyStruct>();

			TestCopySemantics_Impl<char*>();
			TestCopySemantics_Impl<bool*>();
			TestCopySemantics_Impl<int*>();
			TestCopySemantics_Impl<float*>();
			TestCopySemantics_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestMoveSemantics)
		{
			TestMoveSemantics_Impl<char>();
			TestMoveSemantics_Impl<bool>();
			TestMoveSemantics_Impl<int>();
			TestMoveSemantics_Impl<float>();
			TestMoveSemantics_Impl<DummyStruct>();

			TestMoveSemantics_Impl<char*>();
			TestMoveSemantics_Impl<bool*>();
			TestMoveSemantics_Impl<int*>();
			TestMoveSemantics_Impl<float*>();
			TestMoveSemantics_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestShrinkToFit)
		{
			TestShrinkToFit_Impl<char>();
			TestShrinkToFit_Impl<bool>();
			TestShrinkToFit_Impl<int>();
			TestShrinkToFit_Impl<float>();
			TestShrinkToFit_Impl<DummyStruct>();

			TestShrinkToFit_Impl<char*>();
			TestShrinkToFit_Impl<bool*>();
			TestShrinkToFit_Impl<int*>();
			TestShrinkToFit_Impl<float*>();
			TestShrinkToFit_Impl<DummyStruct*>();
		}

		TEST_METHOD(TestIterators)
		{
			TestIterators_Impl<char>();
			TestIterators_Impl<bool>();
			TestIterators_Impl<int>();
			TestIterators_Impl<float>();
			TestIterators_Impl<DummyStruct>();

			TestIterators_Impl<char*>();
			TestIterators_Impl<bool*>();
			TestIterators_Impl<int*>();
			TestIterators_Impl<float*>();
			TestIterators_Impl<DummyStruct*>();
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