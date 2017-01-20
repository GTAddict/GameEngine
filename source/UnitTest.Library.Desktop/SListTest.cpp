#include "pch.h"
#include "CppUnitTest.h"

namespace UnitTestSlistConstants
{
	const int startValue = 65;
	const int endValue = 81;
	const float divisor = 100.0f;
	const unsigned int expectedNumElements = endValue - startValue + 1;
	const std::string name = "Name";
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestSlistConstants;

namespace UnitTestSList
{
	TEST_CLASS(UnitTestSList)
	{
	private:

		struct DummyStruct
		{
			int ID;
			std::string name;
			void* customData;
			int* pOwnedInteger;

			DummyStruct() : ID(0), customData(nullptr), pOwnedInteger(nullptr) { pOwnedInteger = new int; }

			~DummyStruct() { delete pOwnedInteger; }

			DummyStruct(const DummyStruct& rhs) : ID(0), customData(nullptr), pOwnedInteger(nullptr)
			{
				pOwnedInteger = new int(*(rhs.pOwnedInteger));
				ID = rhs.ID;
				name = rhs.name;
				customData = rhs.customData;
			}

			DummyStruct& operator=(const DummyStruct& rhs)
			{
				if (this != &rhs)
				{
					delete pOwnedInteger;
					pOwnedInteger = new int(*(rhs.pOwnedInteger));
					ID = rhs.ID;
					name = rhs.name;
					customData = rhs.customData;
				}
			}
		};

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

		template <typename T>	T		ConvertValue(int i) { return static_cast<T>(i); }
		template <>				bool	ConvertValue(int i) { return i != 0; }

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

			auto PopFrontFunction	= [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction		= [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction		= [&list] { list.Back(); };				///< when the list is empty.
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

			auto PopFrontFunction	= [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction		= [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction		= [&list] { list.Back(); };				///< when the list is empty.
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

			auto PopFrontFunction	= [&list] { list.PopFront(); };			///< Test whether PopFront, Front
			auto FrontFunction		= [&list] { list.Front(); };			///< and Back throw exceptions
			auto BackFunction		= [&list] { list.Back(); };				///< when the list is empty.
			Assert::ExpectException<std::out_of_range>(PopFrontFunction);
			Assert::ExpectException<std::out_of_range>(FrontFunction);
			Assert::ExpectException<std::out_of_range>(BackFunction);
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
			// TestListFrontPtr<char*>			(charStarList);				///< This is leaking memory for some reason?
			TestListFrontPtr<int*>(intStarList);
			TestListFrontPtr<float*>(floatStarList);

			delete pDummyStructList;
			/// pDummyStructList was new'd so needs to be deleted.
			/// Others have destructor invoked automatically
			/// which in turn tests Clear().
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

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestSList::sStartMemState;
#endif
}