#include "pch.h"
#include "CppUnitTest.h"
#include "ScopeXMLHelper.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestScopeParser
{
	TEST_CLASS(UnitTestScopeParser)
	{
	private:

		TEST_METHOD(TestProcess)
		{
			std::string stringToParse = "<scope name=\"root\"><scope name=\"indent\"><int name=\"AnInteger\" value=\"5\" /><float name=\"AFloat\" value=\"5.6\" /><scope name=\"deeper\"></scope></scope><scope name=\"test\" /></scope>";

			// First do the parsing and re-build the XML structure.
			ScopeXMLHelper::ScopeSharedData* sharedData = new ScopeXMLHelper::ScopeSharedData();
			ScopeXMLHelper* helper = new ScopeXMLHelper();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(helper);
			parseMaster.Parse(stringToParse.c_str(), (uint32_t)stringToParse.length(), true);
			Scope* scope = sharedData->GetScope();
			scope;
			delete sharedData;
			delete helper;
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
	_CrtMemState UnitTestScopeParser::sStartMemState;
#endif
}