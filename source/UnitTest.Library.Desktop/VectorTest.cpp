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

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;
using namespace UnitTestVectorConstants;

namespace UnitTestVector
{
	TEST_CLASS(UnitTestVector)
	{
	public:

		TEST_METHOD_EXTENSIVE(TestReserveAndCapacity)
		TEST_METHOD_EXTENSIVE(TestCustomCapacityFn)
		TEST_METHOD_EXTENSIVE(TestBack)
		TEST_METHOD_EXTENSIVE(TestFront)
		TEST_METHOD_EXTENSIVE(TestRandomAccess)
		TEST_METHOD_EXTENSIVE(TestRemove)
		TEST_METHOD_EXTENSIVE(TestCopySemantics)
		TEST_METHOD_EXTENSIVE(TestMoveSemantics)
		TEST_METHOD_EXTENSIVE(TestShrinkToFit)
		TEST_METHOD_EXTENSIVE(TestIterators)
		TEST_METHOD_EXTENSIVE(TestExceptions)

	private:

		template <typename T>
		void TestReserveAndCapacity()
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
		void TestCustomCapacityFn()
		{
			Vector<T> vector(BIND_TO_GETCAPACITYFN(&UnitTestVector::GetNewCapacityCustom));
			Assert::AreEqual(customCapacityDefaultSize, vector.Capacity());

			Vector<T> anotherVector(BIND_TO_GETCAPACITYFN(&UnitTestVector::GetNewCapacityCustom), smallerCustomCapacitySize);
			Assert::AreEqual(smallerCustomCapacitySize, anotherVector.Capacity());

			for (int i = startValue; i <= endValue; ++i)
			{
				anotherVector.PushBack(ConvertValue<T>(i));
			}

			Assert::AreEqual(smallerCustomCapacitySize * 2, anotherVector.Capacity());
		}

		template <typename T>
		void TestBack()
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
		void TestFront()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
				Assert::IsTrue(ConvertValue<T>(startValue) == vector.Front());
			}
		}

		template <typename T>
		void TestRandomAccess()
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
		void TestRemove()
		{
			Vector<T> vector;

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Assert::IsTrue(vector.Size() == expectedNumElements);

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.Remove(ConvertValue<T>(i));
			}

			Assert::IsTrue(vector.IsEmpty());

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}

			Assert::IsTrue(vector.Size() == expectedNumElements);
			 
			vector.Remove(vector.begin(), vector.end() - 1);
			
			Assert::IsTrue(vector.IsEmpty());
		}

		template <typename T>
		void TestCopySemantics()
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
		void TestMoveSemantics()
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
		void TestShrinkToFit()
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
		void TestIterators()
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

		template <typename T>
		void TestExceptions()
		{
			Vector<T> vector;
			Vector<T>::Iterator it;
			
			auto deferenceFunction = [&it] { *it; };
			it = vector.begin();
			auto deferenceFunctionTwo = [&it] { *it; };
			Assert::ExpectException<std::out_of_range>(deferenceFunction);
			Assert::ExpectException<std::out_of_range>(deferenceFunctionTwo);


			auto popBackFunction	= [&vector] { vector.PopBack(); };
			auto frontFunction		= [&vector] { vector.Front(); };
			auto backFunction		= [&vector] { vector.Back(); };
			auto operatorFunction	= [&vector] { vector[vector.Size()]; };
			Assert::ExpectException<std::out_of_range>(popBackFunction);
			Assert::ExpectException<std::out_of_range>(frontFunction);
			Assert::ExpectException<std::out_of_range>(backFunction);
			Assert::ExpectException<std::out_of_range>(operatorFunction);

			vector.Find(ConvertValue<T>(startValue));				//< Should not throw any exception
			vector.Remove(ConvertValue<T>(startValue));				//< Should not throw any exception

			for (int i = startValue; i <= endValue; ++i)
			{
				vector.PushBack(ConvertValue<T>(i));
			}
			auto removeItFunction		= [&vector] { vector.Remove(vector.end(), vector.begin()); };
			auto removeItFunctionTwo	= [&vector] { vector.Remove(vector.end() + 1, vector.begin()); };
			auto removeItFunctionThree	= [&vector] { vector.Remove(vector.end(), vector.begin() - 1); };
			Assert::ExpectException<std::out_of_range>(removeItFunction);
			Assert::ExpectException<std::out_of_range>(removeItFunctionTwo);
			Assert::ExpectException<std::out_of_range>(removeItFunctionThree);
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
	_CrtMemState UnitTestVector::sStartMemState;
#endif
}