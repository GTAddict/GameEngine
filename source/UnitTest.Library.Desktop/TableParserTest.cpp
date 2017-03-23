#include "pch.h"
#include "CppUnitTest.h"
#include "XMLParseHelperTable.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTableParser
{
	TEST_CLASS(UnitTestTableParser)
	{
	private:

		TEST_METHOD(TestProcess)
		{
			std::string stringToParse = "<scope name=\"root\"><scope name=\"indent\"><integer name=\"AnInteger\" value=\"5\" /><float name=\"AFloat\" value=\"5.6\" /><scope name=\"deeper\"></scope></scope><scope name=\"test\" /></scope>";

			// First do the parsing and re-build the XML structure.
			XMLParseHelperTable::SharedDataTable* sharedData = new XMLParseHelperTable::SharedDataTable();
			XMLParseHelperTable* helper = new XMLParseHelperTable();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(helper);
			parseMaster.Parse(stringToParse.c_str(), (uint32_t)stringToParse.length(), true, true);
			XMLParseMaster* newMaster = parseMaster.Clone(); newMaster;
			newMaster->Parse(stringToParse.c_str(), (uint32_t)stringToParse.length(), true, true);
			delete newMaster;
			Scope* scope = sharedData->GetScope();
			scope;
			// Scope& s = *scope;
			// Assert::IsTrue(5 == s["indent"].Get<Scope*>()->operator[]("integer").Get<int>());
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
	_CrtMemState UnitTestTableParser::sStartMemState;
#endif
}