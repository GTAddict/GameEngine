#include "pch.h"
#include "CppUnitTest.h"
#include "FooXMLHelper.h"
#include <fstream>

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestParseMaster
{
	TEST_CLASS(UnitTestParseMaster)
	{
	private:

		TEST_METHOD(TestProcess)
		{
			// First do the parsing and re-build the XML structure.
			FooXMLHelper::FooSharedData* sharedData = new FooXMLHelper::FooSharedData();
			FooXMLHelper* helper = new FooXMLHelper();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(helper);
			parseMaster.ParseFromFile("books.xml");

			// Read in the file separately and see if the contents match.
			std::fstream filin(parseMaster.GetFileName(), std::ios::in);
			std::string fileContents;
			std::getline(filin, fileContents); // chomp off the first line - xml spec
			std::stringstream buffer;
			buffer << filin.rdbuf();
			filin.close();
			fileContents = buffer.str();
			std::string finalString = sharedData->GetConstructedString();
			Assert::IsTrue(fileContents == finalString);
			delete sharedData;
			delete helper;
		}

		TEST_METHOD(TestDepthClone)
		{
			FooXMLHelper* helper = new FooXMLHelper();
			FooXMLHelper::FooSharedData* sharedData = new FooXMLHelper::FooSharedData();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(helper);
			sharedData->IncrementDepth();
			Assert::IsTrue(parseMaster.GetSharedData()->GetDepth() == 1);
			parseMaster.GetSharedData()->DecrementDepth();
			Assert::IsTrue(sharedData->GetDepth() == 0);
			parseMaster.GetSharedData()->IncrementDepth();

			XMLParseMaster& newParseMaster = *parseMaster.Clone();
			Assert::IsTrue(newParseMaster.GetSharedData()->GetDepth() == 0);
			Assert::IsTrue(parseMaster.GetSharedData()->GetXMLParseMaster() == &parseMaster);
			Assert::IsTrue(newParseMaster.GetSharedData()->GetXMLParseMaster() == &newParseMaster);

			parseMaster.RemoveHelper(helper);
			delete helper;
			delete sharedData;
			delete &newParseMaster;
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