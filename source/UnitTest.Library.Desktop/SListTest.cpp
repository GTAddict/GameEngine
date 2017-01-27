#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template <typename T>
			std::wstring ToString(const SList<T>::template Iterator t)
			{
				std::wstringstream s;
				s << "Current node pointer: ";
#if _DEBUG
				s << t.GetCurrentNodePtr() << "\n";
#endif
				s << "Current list owner: ";
#if _DEBUG
				s << t.GetOwnerPtr();
#endif
				return s.str();
			}

			template<> std::wstring ToString<SList<char>::Iterator>(const SList<char>::Iterator& t) { return ToString<char>(t); }
			template<> std::wstring ToString<SList<int>::Iterator>(const SList<int>::Iterator& t) { return ToString<int>(t); }
			template<> std::wstring ToString<SList<float>::Iterator>(const SList<float>::Iterator& t) { return ToString<float>(t); }
		}
	}
}

namespace UnitTestSList
{
	TEST_CLASS(UnitTestSList)
	{
	private:

		template <typename U, typename T = SList<U>>
		void TestListFront(T& list)
		{
			for (int i = startValue; i <= endValue; ++i)					///< Test PushFront
			{
				list.PushFront(ConvertValue<U>(i));
			}

			Assert::AreEqual(expectedNumElements, list.Size());				///< Test Size

			for (int i = endValue; i >= startValue; --i)					///< Test Front and PopFront
			{
				Assert::AreEqual(ConvertValue<U>(i), list.Front());
				list.PopFront();
			}

			Assert::IsTrue(list.IsEmpty());									///< Test IsEmpty

			auto PopFrontFunction = [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction = [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction = [&list] { list.Back(); };				///< when the list is empty.
			Assert::ExpectException<std::out_of_range>(PopFrontFunction);
			Assert::ExpectException<std::out_of_range>(FrontFunction);
			Assert::ExpectException<std::out_of_range>(BackFunction);
		}

		template<typename U, typename T = SList<U>>
		void TestListFrontPtr(SList<DummyStruct*>& list)
		{
			for (int i = startValue; i <= endValue; ++i)					///< Test PushFront
			{
				DummyStruct* dStruct = new DummyStruct();
				dStruct->ID = i;
				dStruct->name = name;
				dStruct->customData = this;
				*dStruct->pOwnedInteger = i;
				list.PushFront(dStruct);
			}

			Assert::AreEqual(expectedNumElements, list.Size());				///< Test Size

			for (int i = endValue; i >= startValue; --i)					///< Test Front and PopFront
			{
				DummyStruct* dStruct = list.Front();
				Assert::AreEqual(i, dStruct->ID);
				Assert::AreEqual(name, dStruct->name);
				Assert::AreEqual((void*)this, dStruct->customData);
				Assert::AreEqual(i, *dStruct->pOwnedInteger);
				list.PopFront();
				delete dStruct;												///< Prevent memory leaks in test
			}

			Assert::IsTrue(list.IsEmpty());									///< Test IsEmpty

			auto PopFrontFunction = [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction = [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction = [&list] { list.Back(); };				///< when the list is empty.
			Assert::ExpectException<std::out_of_range>(PopFrontFunction);
			Assert::ExpectException<std::out_of_range>(FrontFunction);
			Assert::ExpectException<std::out_of_range>(BackFunction);
		}

		template <typename U, typename T = SList<U>>
		void TestListFrontPtr(T& list)
		{
			U array[expectedNumElements];

			for (int i = startValue; i <= endValue; ++i)					///< Test PushFront
			{
				list.PushFront(array[i - startValue]);
			}

			Assert::AreEqual(expectedNumElements, list.Size());				///< Test Size

			for (int i = endValue; i >= startValue; --i)					///< Test Front and PopFront
			{
				Assert::AreEqual(array[i - startValue], list.Front());
				list.PopFront();
			}

			Assert::IsTrue(list.IsEmpty());									///< Test IsEmpty

			auto PopFrontFunction = [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction = [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction = [&list] { list.Back(); };				///< when the list is empty.
			Assert::ExpectException<std::out_of_range>(PopFrontFunction);
			Assert::ExpectException<std::out_of_range>(FrontFunction);
			Assert::ExpectException<std::out_of_range>(BackFunction);
		}

		template <typename U, typename T = SList<U>>
		void TestListBack(T& list)
		{
			for (int i = startValue; i <= endValue; ++i)					///< Test PushBack and Back
			{
				list.PushBack(ConvertValue<U>(i));
				Assert::AreEqual(ConvertValue<U>(i), list.Back());
			}
		}

		template <typename U, typename T = SList<U>>
		void TestListBackPtr(SList<DummyStruct*>& list)
		{
			for (int i = startValue; i <= endValue; ++i)					///< Test PushBack and Back
			{
				DummyStruct* dStruct = new DummyStruct();
				dStruct->ID = i;
				dStruct->name = name;
				dStruct->customData = this;
				*dStruct->pOwnedInteger = i;
				list.PushBack(dStruct);
				Assert::AreEqual(i, list.Back()->ID);
				Assert::AreEqual(name, list.Back()->name);
				Assert::AreEqual((void*) this, list.Back()->customData);
				Assert::AreEqual(i, *list.Back()->pOwnedInteger);

				delete dStruct;												///< To prevent memory leaks in test
			}
		}

		template <typename U, typename T = SList<U>>
		void TestListBackPtr(T& list)
		{
			U array[expectedNumElements];

			for (int i = startValue; i <= endValue; ++i)					///< Test PushBack and Back
			{
				list.PushBack(array[i - startValue]);
				Assert::AreEqual((void*)array[i - startValue], (void*)list.Back());
			}
		}

		template <typename T>
		void TestListCopySemantics()
		{
			SList<T> list;
			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			SList<T> listConstruct(list);									///< Test copy constructor
			SList<T> listAssign;
			listAssign = listConstruct;										///< Test assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(ConvertValue<T>(i), listAssign.Front());
				listAssign.PopFront();

				Assert::AreEqual(ConvertValue<T>(i), listConstruct.Front());
				listConstruct.PopFront();
			}
		}

		template <typename T = DummyStruct>
		void TestListCopySemanticsDummyPtr()
		{
			SList<T*> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				DummyStruct* dStruct = new DummyStruct();
				dStruct->ID = i;
				dStruct->name = name;
				dStruct->customData = this;
				*dStruct->pOwnedInteger = i;
				list.PushBack(dStruct);
			}

			SList<T*> listConstruct(list);									///< Test copy constructor	
			SList<T*> listAssign;
			listAssign = listConstruct;										///< Test assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				DummyStruct* dStruct = listConstruct.Front();
				Assert::AreEqual(i, dStruct->ID);
				Assert::AreEqual(name, dStruct->name);
				Assert::AreEqual((void*) this, dStruct->customData);
				Assert::AreEqual(i, *dStruct->pOwnedInteger);
				listConstruct.PopFront();

				dStruct = listAssign.Front();
				Assert::AreEqual(i, dStruct->ID);
				Assert::AreEqual(name, dStruct->name);
				Assert::AreEqual((void*) this, dStruct->customData);
				Assert::AreEqual(i, *dStruct->pOwnedInteger);
				listAssign.PopFront();

				/// Prevent memory leaks in test
				dStruct = list.Front();
				list.PopFront();
				delete dStruct;
			}
		}

		template <typename T>
		void TestListCopySemanticsPtr()
		{
			T array[expectedNumElements];

			SList<T*> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(&array[i - startValue]);
			}

			SList<T*> listConstruct(list);									///< Test copy constructor
			SList<T*> listAssign;
			listAssign = listConstruct;										///< Test assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(&array[i - startValue], listConstruct.Front());
				listConstruct.PopFront();

				Assert::AreEqual(&array[i - startValue], listAssign.Front());
				listAssign.PopFront();
			}
		}

		template <typename T>
		void TestListMoveSemantics()
		{
			SList<T> list;
			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			SList<T> listConstruct(std::move(list));						///< Test move constructor
			SList<T> listTemp;
			
			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(ConvertValue<T>(i), listConstruct.Front());
				listTemp.PushBack(listConstruct.Front());
				listConstruct.PopFront();
			}

			SList<T> listAssign;
			listAssign = std::move(listTemp);							///< Test move assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(ConvertValue<T>(i), listAssign.Front());
				listAssign.PopFront();
			}

		}

		template <typename T = DummyStruct>
		void TestListMoveSemanticsDummyPtr()
		{
			SList<T*> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				DummyStruct* dStruct = new DummyStruct();
				dStruct->ID = i;
				dStruct->name = name;
				dStruct->customData = this;
				*dStruct->pOwnedInteger = i;
				list.PushBack(dStruct);
			}

			SList<T*> listConstruct(std::move(list));						///< Test move constructor	
			SList<T*> tempList;
			
			for (int i = startValue; i <= endValue; ++i)
			{
				DummyStruct* dStruct = listConstruct.Front();
				Assert::AreEqual(i, dStruct->ID);
				Assert::AreEqual(name, dStruct->name);
				Assert::AreEqual((void*) this, dStruct->customData);
				Assert::AreEqual(i, *dStruct->pOwnedInteger);
				tempList.PushBack(dStruct);
				listConstruct.PopFront();
			}

			SList<T*> listAssign;
			listAssign = std::move(tempList);							///< Test move assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				DummyStruct* dStruct = listAssign.Front();
				Assert::AreEqual(i, dStruct->ID);
				Assert::AreEqual(name, dStruct->name);
				Assert::AreEqual((void*) this, dStruct->customData);
				Assert::AreEqual(i, *dStruct->pOwnedInteger);
				listAssign.PopFront();

				/// Prevent memory leaks in test
				delete dStruct;
			}

		}

		template <typename T>
		void TestListMoveSemanticsPtr()
		{
			T array[expectedNumElements];

			SList<T*> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(&array[i - startValue]);
			}

			SList<T*> listConstruct(std::move(list));									///< Test move constructor
			SList<T*> tempList;

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(&array[i - startValue], listConstruct.Front());
				tempList.PushBack(listConstruct.Front());
				listConstruct.PopFront();
			}

			SList<T*> listAssign;
			listAssign = std::move(tempList);										///< Test move assignment operator

			for (int i = startValue; i <= endValue; ++i)
			{
				Assert::AreEqual(&array[i - startValue], listAssign.Front());
				listAssign.PopFront();
			}
		}

		template <typename T>
		void TestListIteratorBeginEnd()
		{
			SList<T> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			int counter = startValue;
			for (SList<T>::Iterator it = list.begin(), itEnd = list.end(); it != itEnd; ++it)
			{
				Assert::AreEqual(ConvertValue<T>(counter), *it);
				++counter;
			}

			SList<T*> ptrList;
			T array[expectedNumElements];

			for (int i = startValue; i <= endValue; ++i)
			{
				ptrList.PushBack(&array[i - startValue]);
			}

			counter = startValue;
			for (SList<T*>::Iterator it = ptrList.begin(), itEnd = ptrList.end(); it != itEnd; ++it)
			{
				Assert::AreEqual(&array[counter - startValue], *it);
				++counter;
			}
		}

		template <typename T>
		void TestListFind()
		{
			SList<T> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			for (int i = startValue; i <= endValue; ++i)
			{
				SList<T>::Iterator foundIt = list.Find(ConvertValue<T>(i));
				Assert::AreEqual(ConvertValue<T>(i), *foundIt);
			}

			SList<T*> ptrList;
			T array[expectedNumElements];

			for (int i = startValue; i <= endValue; ++i)
			{
				ptrList.PushBack(&array[i - startValue]);
			}

			for (int i = startValue; i <= endValue; ++i)
			{
				SList<T*>::Iterator foundIt = ptrList.Find(&array[i - startValue]);
				Assert::AreEqual(&array[i - startValue], *foundIt);
			}
		}

		template <typename T>
		void TestListRemove()
		{
			SList<T> list;

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			for (int i = endValue; i >= startValue; --i)
			{
				list.Remove(ConvertValue<T>(i));
			}

			Assert::IsTrue(list.IsEmpty());

			SList<T*> ptrList;
			T array[expectedNumElements];

			for (int i = startValue; i <= endValue; ++i)
			{
				ptrList.PushBack(&array[i - startValue]);
			}

			for (int i = endValue; i >= startValue; --i)
			{
				ptrList.Remove(&array[i - startValue]);
			}

			Assert::IsTrue(ptrList.IsEmpty());
		}

		template <typename T>
		void TestListInsertAfter()
		{
			SList<T> list;

			int insertAfterElement = (endValue + startValue) / 2;
			int valueToInsert = rand();

			for (int i = startValue; i <= endValue; ++i)
			{
				list.PushBack(ConvertValue<T>(i));
			}

			list.InsertAfter(list.Find(ConvertValue<T>(insertAfterElement)), ConvertValue<T>(valueToInsert));

			int count = startValue;
			for (SList<T>::Iterator it = list.begin(), itEnd = list.end(); it != itEnd; ++it)
			{
				if (count == insertAfterElement + 1)
				{
					Assert::AreEqual(ConvertValue<T>(valueToInsert), *it);
				}
				else if (count > insertAfterElement + 1)
				{
					Assert::AreEqual(ConvertValue<T>(count - 1), *it);
				}
				else
				{
					Assert::AreEqual(ConvertValue<T>(count), *it);
				}

				++count;
			}
		}

		template <typename T>
		void TestIteratorEqualityInequality()
		{
			SList<T> myList, anotherList;

			SList<T>::Iterator itMyList, itAnotherList;
			Assert::AreNotEqual(itMyList, itAnotherList);

			SList<T>::Iterator itMy = myList.begin(), itAnother = anotherList.begin();
			Assert::AreNotEqual(itMy, itAnother);

			for (int i = startValue; i <= endValue; ++i)
			{
				myList.PushBack(ConvertValue<T>(i));
				anotherList.PushBack(ConvertValue<T>(i));
			}

			Assert::AreNotEqual(myList.Find(ConvertValue<T>(endValue)), anotherList.Find(ConvertValue<T>(endValue)));

			SList<T>::Iterator itBegin = myList.begin();
			++itBegin;

			SList<T>::Iterator itPlusOne = myList.Find(ConvertValue<T>(startValue + 1));

			Assert::AreEqual(itBegin, itPlusOne);
		}

		template <typename T>
		void TestIteratorIncrement()
		{
			SList<T> list;
			list.PushBack(ConvertValue<T>(startValue));
			list.PushBack(ConvertValue<T>(startValue + 1));

			SList<T>::Iterator preIncIt = list.begin();
			Assert::AreEqual(ConvertValue<T>(startValue + 1), *(++preIncIt));
			Assert::AreEqual(ConvertValue<T>(startValue + 1), *preIncIt);

			list.Front() = ConvertValue<T>(startValue);
			SList<T>::Iterator postIncIt = list.begin();
			Assert::AreEqual(ConvertValue<T>(startValue), *(postIncIt++));
			Assert::AreEqual(ConvertValue<T>(startValue + 1), *postIncIt);
		}

		template <typename T>
		void TestListIteratorExceptions()
		{
			SList<T> list;
			SList<T>::Iterator it = list.end();

			auto insertAfterFunc = [this, &list, &it] { list.InsertAfter(it, ConvertValue<T>(startValue)); };
			Assert::ExpectException<std::out_of_range>(insertAfterFunc);

			auto preIncrementFunc = [&it] { ++it; };
			Assert::ExpectException<std::out_of_range>(preIncrementFunc);

			auto postIncrementFunc = [&it] { it++; };
			Assert::ExpectException<std::out_of_range>(postIncrementFunc);

			SList<T>::Iterator endIt = list.Find(ConvertValue<T>(startValue - 1));
			auto dereferenceFunc = [&it] { *it; };
			Assert::ExpectException<std::runtime_error>(dereferenceFunc);

			list.Remove(ConvertValue<T>(startValue - 1));									//< This should not throw any exception
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

		TEST_METHOD(TestFront)
		{
			/// Test constructors.
			SList<bool>		boolList;
			SList<char>		charList;
			SList<int>		intList;
			SList<float>	floatList;

			TestListFront<bool>(boolList);
			TestListFront<char>(charList);
			TestListFront<int>(intList);
			TestListFront<float>(floatList);

			/// Test const version
			SList<int>	constIntList;
			constIntList.PushBack(startValue);
			Assert::AreEqual(startValue, constIntList.Front());

			/// Destructor invoked automatically
			/// which in turn tests Clear().
		}

		TEST_METHOD(TestFrontPtr)
		{
			/// Test constructors.
			SList<DummyStruct*>*	pDummyStructList = new SList<DummyStruct*>();
			SList<bool*>			boolStarList;
			SList<char*>			charStarList;
			SList<int*>				intStarList;
			SList<float*>			floatStarList;

			TestListFrontPtr<DummyStruct*>(*pDummyStructList);
			TestListFrontPtr<bool*>(boolStarList);
			TestListFrontPtr<int*>(intStarList);
			TestListFrontPtr<float*>(floatStarList);

			delete pDummyStructList;
			/// pDummyStructList was new'd so needs to be deleted.
			/// Others have destructor invoked automatically
			/// which in turn tests Clear().
		}

		TEST_METHOD(TestBack)
		{
			/// Test constructors.
			SList<bool>				boolList;
			SList<char>				charList;
			SList<int>				intList;
			SList<float>			floatList;

			TestListBack<bool>(boolList);
			TestListBack<char>(charList);
			TestListBack<int>(intList);
			TestListBack<float>(floatList);

			/// Test const version
			SList<int>	constIntList;
			constIntList.PushBack(startValue);
			Assert::AreEqual(startValue, constIntList.Back());

			/// Destructor invoked automatically
			/// which in turn tests Clear().
		}

		TEST_METHOD(TestBackPtr)
		{
			/// Test constructors.
			SList<DummyStruct*>*	pDummyStructList = new SList<DummyStruct*>();
			SList<bool*>			boolStarList;
			SList<char*>			charStarList;
			SList<int*>				intStarList;
			SList<float*>			floatStarList;

			TestListBackPtr<DummyStruct*>(*pDummyStructList);
			TestListBackPtr<bool*>(boolStarList);
			TestListBackPtr<char*>(charStarList);
			TestListBackPtr<int*>(intStarList);
			TestListBackPtr<float*>(floatStarList);

			delete pDummyStructList;
			/// pDummyStructList was new'd so needs to be deleted.
			/// Others have destructor invoked automatically
			/// which in turn tests Clear().
		}

		TEST_METHOD(TestCopySemantics)
		{
			TestListCopySemantics<bool>();
			TestListCopySemantics<char>();
			TestListCopySemantics<int>();
			TestListCopySemantics<float>();
		}

		TEST_METHOD(TestCopySemanticsPtr)
		{
			TestListCopySemanticsDummyPtr<DummyStruct>();
			TestListCopySemanticsPtr<bool>();
			TestListCopySemanticsPtr<char>();
			TestListCopySemanticsPtr<int>();
			TestListCopySemanticsPtr<float>();
		}

		TEST_METHOD(TestMoveSemantics)
		{
			// TestListMoveSemantics<bool>();
			// TestListMoveSemantics<char>();
			TestListMoveSemantics<int>();
			TestListMoveSemantics<float>();
		}

		TEST_METHOD(TestMoveSemanticsPtr)
		{
			TestListMoveSemanticsDummyPtr<DummyStruct>();
			TestListMoveSemanticsPtr<bool>();
			TestListMoveSemanticsPtr<char>();
			TestListMoveSemanticsPtr<int>();
			TestListMoveSemanticsPtr<float>();
		}

		TEST_METHOD(TestIteratorBeginEnd)
		{
			TestListIteratorBeginEnd<char>();
			TestListIteratorBeginEnd<bool>();
			TestListIteratorBeginEnd<int>();
			TestListIteratorBeginEnd<float>();
			TestListIteratorBeginEnd<DummyStruct>();
		}
		
		TEST_METHOD(TestFind)
		{
			TestListFind<char>();
			TestListFind<bool>();
			TestListFind<int>();
			TestListFind<float>();
		}

		TEST_METHOD(TestRemove)
		{
			TestListRemove<bool>();
			TestListRemove<char>();
			TestListRemove<int>();
			TestListRemove<float>();
		}

		TEST_METHOD(TestInsertAfter)
		{
			TestListInsertAfter<bool>();
			TestListInsertAfter<char>();
			TestListInsertAfter<int>();
			TestListInsertAfter<float>();
		}

		TEST_METHOD(TestEqualityInequality)
		{
			TestIteratorEqualityInequality<char>();
			TestIteratorEqualityInequality<int>();
			TestIteratorEqualityInequality<float>();
		}

		TEST_METHOD(TestIncrement)
		{
			TestIteratorIncrement<bool>();
			TestIteratorIncrement<char>();
			TestIteratorIncrement<int>();
			TestIteratorIncrement<float>();
		}

		TEST_METHOD(TestIteratorExceptions)
		{
			TestListIteratorExceptions<char>();
			TestListIteratorExceptions<bool>();
			TestListIteratorExceptions<int>();
			TestListIteratorExceptions<float>();
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestSList::sStartMemState;
#endif
}