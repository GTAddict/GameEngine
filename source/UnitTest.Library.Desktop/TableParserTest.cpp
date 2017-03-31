#include "pch.h"
#include "CppUnitTest.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTableParser
{
	TEST_CLASS(UnitTestTableParser)
	{
	private:

		TEST_METHOD(TestProcess)
		{
			
		}

		TEST_METHOD(TestRTTI)
		{
			XMLParseMaster::SharedData* data = new XMLParseHelperTable::SharedDataTable();
			Assert::IsTrue(data->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()));
			Assert::IsTrue(data->Is("SharedDataTable"));
			Assert::IsTrue(data->As<XMLParseHelperTable::SharedDataTable>() == static_cast<XMLParseHelperTable::SharedDataTable*>(data));
			delete data;
		}

		TEST_METHOD(TestEntities)
		{
			 ConcreteFactory(Entity, TestClass);
			 ConcreteFactory(Entity, AnotherClass);
			 TestClassFactory testClassFactory;
			 AnotherClassFactory anotherClassFactory;
			 
			 XMLParseHelperTable::SharedDataTable* sharedData = new XMLParseHelperTable::SharedDataTable();
			 XMLParseMaster parseMaster(sharedData);
			 parseMaster.AddHelper(new XMLParseHelperTable());
			 parseMaster.AddHelper(new XMLParseHelperWorld());
			 parseMaster.AddHelper(new XMLParseHelperSector());
			 parseMaster.AddHelper(new XMLParseHelperEntity());
			 parseMaster.ParseFromFile("TableParserTestData.xml");
			 
			 WorldState state;
			 state.mpWorld = sharedData->mScope->As<World>();
			 state.mpWorld->Update(state);
			 
			 delete sharedData;
			 SList<IXMLParseHelper*> list = parseMaster.GetHelperList();
			 for (IXMLParseHelper* helper : list)
			 {
				 parseMaster.RemoveHelper(helper);
				 delete helper;
			 }
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

		class TestClass : public Entity {};
		class AnotherClass : public Entity {};

	};

#ifdef _DEBUG
	_CrtMemState UnitTestTableParser::sStartMemState;
#endif
}
