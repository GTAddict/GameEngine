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

		TEST_METHOD_EXTENSIVE(TestConstructor)

	private:

		template <typename T>
		void TestConstructor()
		{
			HashMap<std::string, int> myMap(5);

			for (int i = 0; i < 10; ++i)
			{
				myMap.Insert(std::pair<std::string, int>(std::string(2, 'A' + (char)i), i));
			}

			std::string helloString = "Hello";
			std::string hiString = "Hi";

			myMap[helloString] = 10;
			myMap[hiString] = 20;
			myMap[helloString] = 5;

			bool isPresent = false;
			isPresent = myMap.ContainsKey(helloString);
			isPresent = myMap.ContainsKey(hiString);
			isPresent = myMap.ContainsKey("BB");
			isPresent = myMap.ContainsKey("DD");
			isPresent = myMap.ContainsKey("FF");

			HashMap<std::string, int>::Iterator it = myMap.begin();

			it->first;
			it->second;

			// int a = myMap.Size();
			// a;

			HashMap<std::string, int> myDifferentMap(10);

			myDifferentMap = myMap;

			if (myDifferentMap == myMap)
			{
				myDifferentMap = std::move(myMap);
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

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestHashMap::sStartMemState;
#endif
}