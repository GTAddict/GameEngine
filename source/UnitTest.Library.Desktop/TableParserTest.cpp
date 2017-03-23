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
			std::string stringToParse = "<scope name=\"root\"><scope name=\"indent\"><integer name=\"AnInteger\" value=\"5\" /><float name=\"AFloat\" value=\"5.6\" /><string name=\"AString\" value=\"Hello\" index=\"0\" /><string name=\"AString\" value=\"Hi\" index=\"1\" /><vector name=\"AVector\" value=\"vec4(2.2, 3.3, 4.4, 55)\" /><matrix name=\"AMatrix\" value=\"mat4x4((1.1, 2.2, 3.3, 4.4), (5.5, 6.6, 7.7, 8.8), (9.9, 10.10, 11.11, 12.12), (13.13, 14.14, 15.15, 16.16))\" /><scope name=\"deeper\"></scope></scope><scope name=\"test\" /></scope>";

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
			std::int32_t integer			= (*scope)["indent"][0]["AnInteger"].Get<std::int32_t>();
			float theFloat					= (*scope)["indent"][0]["AFloat"].Get<float>();
			glm::vec4 theVector				= (*scope)["indent"][0]["AVector"].Get<glm::vec4>();
			glm::mat4x4 theMatrix			= (*scope)["indent"][0]["AMatrix"].Get<glm::mat4x4>();
			std::string theStringIndexZero	= (*scope)["indent"][0]["AString"].Get<std::string>();
			std::string theStringIndexOne	= (*scope)["indent"][0]["AString"].Get<std::string>(1);
			Assert::IsTrue(5 == integer);
			Assert::IsTrue(5.6f == theFloat);
			Assert::IsTrue(theVector == glm::vec4(2.2, 3.3, 4.4, 55));
			Assert::IsTrue(theMatrix == glm::mat4x4(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16));
			Assert::IsTrue(theStringIndexZero == "Hello");
			Assert::IsTrue(theStringIndexOne == "Hi");

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