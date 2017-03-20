#include "pch.h"
#include "CppUnitTest.h"
#include "FooSharedData.h"
#include "FooXMLHelper.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestParseMaster
{
	TEST_CLASS(UnitTestParseMaster)
	{
	private:

		TEST_METHOD(TestConstructor)
		{
			FooSharedData* sharedData = new FooSharedData(); sharedData;
			FooXMLHelper* helper = new FooXMLHelper(); helper;
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(helper);
			parseMaster.ParseFromFile("books.xml");
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
	_CrtMemState UnitTestParseMaster::sStartMemState;
#endif
}