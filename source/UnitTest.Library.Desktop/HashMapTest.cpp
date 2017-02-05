#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"
#include <iostream>

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;

namespace UnitTestHashMap
{
	TEST_CLASS(UnitTestHashMap)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			{
				HashMap<int, int> hashMap(10);
			}
			{
				HashMap<int*, int*> hashMap(10);
			}
			{
				HashMap<std::string, std::string> hashMap(10);
			}
			{
				HashMap<DummyStruct*, DummyStruct*> hashMap(10);
			}
		}

		TEST_METHOD(TestCopySemantics)
		{
			{
				HashMap<int, int> firstHashMap(10);
				for (int i = startValue; i <= endValue; ++i)
				{
					firstHashMap.Insert(std::pair<int, int>(i, i));
				}

				HashMap<int, int> secondHashMap(5);
				secondHashMap = firstHashMap;
				Assert::IsTrue(secondHashMap == firstHashMap);
				HashMap<int, int> thirdHashMap = firstHashMap;
				Assert::IsTrue(thirdHashMap == firstHashMap);
			}
			{
				int one = 1, two = 2;
				HashMap<int*, int> firstHashMap(10);
				firstHashMap.Insert(std::pair<int*, int>(&one, one));
				firstHashMap.Insert(std::pair<int*, int>(&two, two));

				HashMap<int*, int> secondHashMap(5);
				secondHashMap = firstHashMap;
				Assert::IsTrue(secondHashMap == firstHashMap);
				HashMap<int*, int> thirdHashMap = firstHashMap;
				Assert::IsTrue(thirdHashMap == firstHashMap);
			}
			{
				std::string hello = "Hello";
				std::string you = "you";
				std::string hi = "Hi";
				std::string there = "there";
				HashMap<std::string, std::string> firstHashMap(10);
				firstHashMap.Insert(std::pair<std::string, std::string>(hello, you));
				firstHashMap.Insert(std::pair<std::string, std::string>(hi, there));

				HashMap<std::string, std::string> secondHashMap(5);
				secondHashMap = firstHashMap;
				Assert::IsTrue(secondHashMap == firstHashMap);
				HashMap<std::string, std::string> thirdHashMap = firstHashMap;
				Assert::IsTrue(thirdHashMap == firstHashMap);
			}
			{
				DummyStruct d;
				int a = 5;
				HashMap<DummyStruct*, int> firstHashMap(10);
				firstHashMap.Insert(std::pair<DummyStruct*, int>(&d, a));

				HashMap<DummyStruct*, int> secondHashMap(5);
				secondHashMap = firstHashMap;
				Assert::IsTrue(secondHashMap == firstHashMap);
				HashMap<DummyStruct*, int> thirdHashMap = firstHashMap;
				Assert::IsTrue(thirdHashMap == firstHashMap);
			}
		}

		TEST_METHOD(TestMoveSemantics)
		{
			{
				HashMap<int, int> firstHashMap(10);
				for (int i = startValue; i <= endValue; ++i)
				{
					firstHashMap.Insert(std::pair<int, int>(i, i));
				}
				HashMap<int, int> copyOfFirst = firstHashMap;

				HashMap<int, int> secondHashMap(5);
				secondHashMap = std::move(firstHashMap);
				Assert::IsTrue(copyOfFirst == secondHashMap);
				HashMap<int, int> thirdHashMap = std::move(secondHashMap);
				Assert::IsTrue(copyOfFirst == thirdHashMap);
				Assert::IsTrue(copyOfFirst != firstHashMap);
			}
			{
				HashMap<int*, int> firstHashMap(10);
				int a = 10, b = 20;
				firstHashMap.Insert(std::pair<int*, int>(&a, a));
				firstHashMap.Insert(std::pair<int*, int>(&b, b));

				HashMap<int*, int> copyOfFirst = firstHashMap;

				HashMap<int*, int> secondHashMap(5);
				secondHashMap = std::move(firstHashMap);
				Assert::IsTrue(copyOfFirst == secondHashMap);
				HashMap<int*, int> thirdHashMap = std::move(secondHashMap);
				Assert::IsTrue(copyOfFirst == thirdHashMap);
				Assert::IsTrue(copyOfFirst != firstHashMap);
			}
			{
				HashMap<std::string, int> firstHashMap(10);
				int a = 10, b = 20;
				std::string x = "Hello", y = "Hi";
				firstHashMap.Insert(std::pair<std::string, int>(x, a));
				firstHashMap.Insert(std::pair<std::string, int>(y, b));

				HashMap<std::string, int> copyOfFirst = firstHashMap;

				HashMap<std::string, int> secondHashMap(5);
				secondHashMap = std::move(firstHashMap);
				Assert::IsTrue(copyOfFirst == secondHashMap);
				HashMap<std::string, int> thirdHashMap = std::move(secondHashMap);
				Assert::IsTrue(copyOfFirst == thirdHashMap);
				Assert::IsTrue(copyOfFirst != firstHashMap);
			}
			{
				HashMap<DummyStruct*, int> firstHashMap(10);
				int a = 10, b = 20;
				DummyStruct x, y;
				firstHashMap.Insert(std::pair<DummyStruct*, int>(&x, a));
				firstHashMap.Insert(std::pair<DummyStruct*, int>(&y, b));

				HashMap<DummyStruct*, int> copyOfFirst = firstHashMap;

				HashMap<DummyStruct*, int> secondHashMap(5);
				secondHashMap = std::move(firstHashMap);
				Assert::IsTrue(copyOfFirst == secondHashMap);
				HashMap<DummyStruct*, int> thirdHashMap = std::move(secondHashMap);
				Assert::IsTrue(copyOfFirst == thirdHashMap);
				Assert::IsTrue(copyOfFirst != firstHashMap);
			}

		}

		TEST_METHOD(TestInsertFindContainsKey)
		{
			{
				HashMap<int, int> hashMap(10);

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::IsTrue(hashMap.Find(i) == hashMap.end());
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap.Insert(std::pair<int, int>(i, i));
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap.Insert(std::pair<int, int>(i, i));
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::IsTrue(hashMap.Find(i) != hashMap.end());
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::IsTrue(hashMap.ContainsKey(i));
				}
			}

			{
				HashMap<int*, int> hashMap(10);
				int a = 1, b = 2;

				hashMap.Find(&a);
				hashMap.Find(&b);

				hashMap.Insert(std::pair<int*, int>(&a, a));
				hashMap.Insert(std::pair<int*, int>(&b, b));

				hashMap.Insert(std::pair<int*, int>(&a, a));
				hashMap.Insert(std::pair<int*, int>(&b, b));

				Assert::IsTrue(hashMap.Find(&a) != hashMap.end());
				Assert::IsTrue(hashMap.Find(&b) != hashMap.end());

				Assert::IsTrue(hashMap.ContainsKey(&a));
				Assert::IsTrue(hashMap.ContainsKey(&b));
			}

			{
				HashMap<std::string, int> hashMap(10);
				int a = 1, b = 2;
				std::string x = "Heloo", y = "WJU";

				hashMap.Find(x);
				hashMap.Find(y);

				hashMap.Insert(std::pair<std::string, int>(x, a));
				hashMap.Insert(std::pair<std::string, int>(y, b));

				hashMap.Insert(std::pair<std::string, int>(x, a));
				hashMap.Insert(std::pair<std::string, int>(y, b));

				Assert::IsTrue(hashMap.Find(x) != hashMap.end());
				Assert::IsTrue(hashMap.Find(y) != hashMap.end());

				Assert::IsTrue(hashMap.ContainsKey(x));
				Assert::IsTrue(hashMap.ContainsKey(y));
			}
			{
				HashMap<DummyStruct*, int> hashMap(10);
				int a = 1, b = 2;
				DummyStruct x, y;

				hashMap.Find(&x);
				hashMap.Find(&y);

				hashMap.Insert(std::pair<DummyStruct*, int>(&x, a));
				hashMap.Insert(std::pair<DummyStruct*, int>(&y, b));
										 
				hashMap.Insert(std::pair<DummyStruct*, int>(&x, a));
				hashMap.Insert(std::pair<DummyStruct*, int>(&y, b));

				Assert::IsTrue(hashMap.Find(&x) != hashMap.end());
				Assert::IsTrue(hashMap.Find(&y) != hashMap.end());

				Assert::IsTrue(hashMap.ContainsKey(&x));
				Assert::IsTrue(hashMap.ContainsKey(&y));
			}

		}

		TEST_METHOD(TestMove)
		{
			{
				HashMap<int, int> hashMap(5);

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap.Insert(std::pair<int, int>(i, i));
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::IsTrue(hashMap.Remove(i));
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::IsFalse(hashMap.Remove(i));
				}
			}
			{
				HashMap<int*, int> hashMap(5);
				int a = 5, b = 6;

				hashMap.Insert(std::pair<int*, int>(&a, a));
				hashMap.Insert(std::pair<int*, int>(&b, b));

				Assert::IsTrue(hashMap.Remove(&a));
				Assert::IsTrue(hashMap.Remove(&b));
				Assert::IsFalse(hashMap.Remove(&a));
				Assert::IsFalse(hashMap.Remove(&b));
			}
			{
				HashMap<std::string, int> hashMap(5);
				int a = 5, b = 6;
				std::string x = "hello", y = "hi";

				hashMap.Insert(std::pair<std::string, int>(x, a));
				hashMap.Insert(std::pair<std::string, int>(y, b));

				Assert::IsTrue(hashMap.Remove(x));
				Assert::IsTrue(hashMap.Remove(y));
				Assert::IsFalse(hashMap.Remove(x));
				Assert::IsFalse(hashMap.Remove(y));
			}
			{
				HashMap<DummyStruct*, int> hashMap(5);
				int a = 5, b = 6;
				DummyStruct x, y;

				hashMap.Insert(std::pair<DummyStruct*, int>(&x, a));
				hashMap.Insert(std::pair<DummyStruct*, int>(&y, b));

				Assert::IsTrue(hashMap.Remove(&x));
				Assert::IsTrue(hashMap.Remove(&y));
				Assert::IsFalse(hashMap.Remove(&x));
				Assert::IsFalse(hashMap.Remove(&y));
			}
		}

		TEST_METHOD(TestIndexOperator)
		{
			{
				HashMap<int, int> hashMap(5);

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap[i] = i;
				}

				for (int i = startValue; i <= endValue; ++i)
				{
					Assert::AreEqual(hashMap[i], i);
					hashMap[i];
				}
			}
			{
				HashMap<int*, int> hashMap(5);
				int a = 5, b = 6;

				hashMap[&a] = a;
				hashMap[&b] = b;

				Assert::AreEqual(hashMap[&a], a);
				Assert::AreEqual(hashMap[&b], b);
			}
			{
				HashMap<std::string, int> hashMap(5);
				int a = 5, b = 6;
				std::string x = "fd", y = "asd";

				hashMap[x] = a;
				hashMap[y] = b;

				Assert::AreEqual(hashMap[x], a);
				Assert::AreEqual(hashMap[y], b);
			}
			{
				HashMap<DummyStruct*, int> hashMap(5);
				int a = 5, b = 6;
				DummyStruct x, y;

				hashMap[&x] = a;
				hashMap[&y] = b;

				Assert::AreEqual(hashMap[&x], a);
				Assert::AreEqual(hashMap[&y], b);
			}
		}

		TEST_METHOD(TestSizeAndClear)
		{
			{
				HashMap<int, int> hashMap(5);

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap[i] = i;
				}

				Assert::IsTrue(hashMap.Size() == expectedNumElements);

				hashMap.Clear();

				Assert::IsTrue(hashMap.Size() == 0);
			}

			{
				HashMap<int*, int> hashMap(5);

				for (int i = startValue; i <= endValue; ++i)
				{
					hashMap[&i] = i;
				}

				hashMap.Clear();

				Assert::IsTrue(hashMap.Size() == 0);
			}

			{
				HashMap<std::string, int> hashMap(5);
				std::string one = "ONE", two = "TWO";
				hashMap[one] = 1;
				hashMap[two] = 2;

				Assert::IsTrue(hashMap.Size() == 2);

				hashMap.Clear();

				Assert::IsTrue(hashMap.Size() == 0);
			}
			{
				HashMap<DummyStruct*, int> hashMap(5);
				DummyStruct a, b;

				hashMap[&a] = 1;
				hashMap[&b] = 2;

				Assert::IsTrue(hashMap.Size() == 2);

				hashMap.Clear();

				Assert::IsTrue(hashMap.Size() == 0);
			}
		}

		TEST_METHOD(TestIterators)
		{
			HashMap<int, int> firstHashMap(5);
			HashMap<int, int> secondHashMap(10);

			for (int i = startValue; i <= endValue; ++i)
			{
				firstHashMap.Insert(std::pair<int, int>(i, i));
				secondHashMap.Insert(std::pair<int, int>(i, i));
			}

			HashMap<int, int>::Iterator firstIt = firstHashMap.begin(), secondIt = secondHashMap.begin();
			Assert::IsTrue(firstHashMap.begin() != secondHashMap.begin());

			HashMap<int, int>::Iterator copyIt = firstIt;
			Assert::IsTrue(copyIt == firstIt);
			copyIt = secondIt;
			Assert::IsTrue(copyIt == secondIt);

			HashMap<int, int>::Iterator moveIt = std::move(copyIt);
			Assert::IsTrue(moveIt == secondIt);
			HashMap<int, int>::Iterator firstCopy = firstIt;
			moveIt = std::move(firstIt);
			Assert::IsTrue(moveIt == firstCopy);

			auto function = [&firstHashMap] { firstHashMap.end()++; };
			Assert::ExpectException<std::out_of_range>(function);
		}

		TEST_METHOD(TestIteratorsMore)
		{
			HashMap<int, int> hashMap(10);

			for (int i = startValue; i <= endValue; ++i)
			{
				hashMap.Insert(std::pair<int, int>(i, i));
			}

			HashMap<int, int>::Iterator itBegin = hashMap.begin(), itEnd = hashMap.end();
			for (; itBegin != itEnd; ++itBegin)
			{
				Assert::IsTrue(hashMap.ContainsKey((*itBegin).first));
				Assert::IsTrue(hashMap.ContainsKey(itBegin->first));
			}
		}
		

	private:

		

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
	_CrtMemState UnitTestHashMap::sStartMemState;
#endif
}