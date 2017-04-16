#include "pch.h"
#include "CppUnitTest.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestTableParser
{
	TEST_CLASS(UnitTestTableParser)
	{
	private:

		TEST_METHOD(TestRTTI)
		{
			XMLParseMaster::SharedData* data = new XMLParseHelperTable::SharedDataTable();
			Assert::IsTrue(data->Is(XMLParseHelperTable::SharedDataTable::TypeIdClass()));
			Assert::IsTrue(data->Is("SharedDataTable"));
			Assert::IsTrue(data->As<XMLParseHelperTable::SharedDataTable>() == static_cast<XMLParseHelperTable::SharedDataTable*>(data));
			Assert::IsTrue(data->ToString() == "RTTI");
			delete data;

			World* world = new World();
			Assert::IsTrue(world->Is(World::TypeIdClass()));
			Assert::IsTrue(world->Is("World"));
			Assert::IsTrue(world->As<Attributed>() == static_cast<Attributed*>(world));
			Assert::IsTrue(world->ToString() == "RTTI");
			delete world;

			Sector* sector = new Sector();
			Assert::IsTrue(sector->Is(Sector::TypeIdClass()));
			Assert::IsTrue(sector->Is("Sector"));
			Assert::IsTrue(sector->As<Sector>() == static_cast<Sector*>(sector));
			Assert::IsTrue(sector->ToString() == "RTTI");
			delete sector;

			Entity* entity = new Entity();
			Assert::IsTrue(entity->Is(Entity::TypeIdClass()));
			Assert::IsTrue(entity->Is("Entity"));
			Assert::IsTrue(entity->As<Entity>() == static_cast<Entity*>(entity));
			Assert::IsTrue(entity->ToString() == "RTTI");
			delete entity;

			ActionExpression* actionExpression = new ActionExpression();
			Assert::IsTrue(actionExpression->Is(ActionExpression::TypeIdClass()));
			Assert::IsTrue(actionExpression->Is("ActionExpression"));
			Assert::IsTrue(actionExpression->As<ActionExpression>() == static_cast<ActionExpression*>(actionExpression));
			Assert::IsTrue(actionExpression->ToString() == "RTTI");
			delete actionExpression;
		}

		TEST_METHOD(TestParse)
		{
			TestClassFactory testClassFactory;
			AnotherClassFactory anotherClassFactory;
			ActionExpressionFactory actionExpressionFactory;
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionAttributedFactory;

			XMLParseHelperTable::SharedDataTable* sharedData = new XMLParseHelperTable::SharedDataTable();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(new XMLParseHelperTable());
			parseMaster.AddHelper(new XMLParseHelperWorld());
			parseMaster.AddHelper(new XMLParseHelperSector());
			parseMaster.AddHelper(new XMLParseHelperEntity());
			parseMaster.AddHelper(new XMLParseHelperAction());
			parseMaster.AddHelper(new XMLParseHelperExpression());
			parseMaster.AddHelper(new XMLParseHelperReaction());
			parseMaster.ParseFromFile("TableParserTestData.xml");

			EventQueue e;
			GameClock clock;
			GameTime gameTime;
			WorldState state;
			state.SetGameTime(gameTime);
			clock.UpdateGameTime(gameTime);
			state.mpWorld = sharedData->mScope->As<World>();
			state.mpEventQueue = &e;
			state.mpWorld->Update(state);
			e.Update(gameTime);

			Assert::IsTrue(state.GetGameTime().TotalGameTime() == gameTime.TotalGameTime());
			Assert::IsTrue(state.mpWorld->Name() == "root");
			Assert::IsTrue(state.mpWorld->Sectors().Size() == 2);
			Sector* sector = (&state.mpWorld->Sectors()[0])->As<Sector>();
			Assert::IsTrue(sector->Name() == "indent");
			Assert::IsTrue(sector->Entities().Size() == 2);
			Assert::IsTrue(&sector->GetWorld() == state.mpWorld);
			Entity* entity = (&sector->Entities()[0])->As<Entity>();
			Assert::IsTrue(entity->Name() == "one");
			Assert::IsTrue(&entity->GetSector() == sector);

			delete sharedData;
			SList<IXMLParseHelper*> list = parseMaster.GetHelperList();
			for (IXMLParseHelper* helper : list)
			{
				parseMaster.RemoveHelper(helper);
				delete helper;
			}
		}

		TEST_METHOD(TestMoveSemantics)
		{
			TestClassFactory testClassFactory;
			AnotherClassFactory anotherClassFactory;

			XMLParseHelperTable::SharedDataTable* sharedData = new XMLParseHelperTable::SharedDataTable();
			XMLParseMaster parseMaster(sharedData);
			parseMaster.AddHelper(new XMLParseHelperTable());
			parseMaster.AddHelper(new XMLParseHelperWorld());
			parseMaster.AddHelper(new XMLParseHelperSector());
			parseMaster.AddHelper(new XMLParseHelperEntity());
			parseMaster.ParseFromFile("TableParserTestData.xml");

			World world = std::move(*sharedData->mScope->As<World>());
			Sector* oldSector = (&world.Sectors()[0])->As<Sector>();
			Sector* sector = new Sector();
			*sector = std::move(*oldSector);
			Entity* oldEntity = (&sector->Entities()[0])->As<Entity>();
			Entity* entity = new Entity();
			*entity	= std::move(*oldEntity);
			delete oldSector;
			delete oldEntity;
			
			Assert::IsTrue(world.Name() == "root");
			Assert::IsTrue(world.Sectors().Size() == 2);
			Assert::IsTrue(sector->Name() == "indent");
			Assert::IsTrue(sector->Entities().Size() == 2);
			Assert::IsTrue(&sector->GetWorld() == &world);
			Assert::IsTrue(entity->Name() == "one");
			Assert::IsTrue(&entity->GetSector() == sector);

			world = std::move(world);
			sector = std::move(sector);
			entity = std::move(entity);
			 
			delete sharedData;
			SList<IXMLParseHelper*> list = parseMaster.GetHelperList();
			for (IXMLParseHelper* helper : list)
			{
				parseMaster.RemoveHelper(helper);
				delete helper;
			}
		}

		TEST_METHOD(TestExceptions)
		{
			Assert::ExpectException<std::invalid_argument>
				([]{
				Entity e;
				e.SetName("");
			});
			Assert::ExpectException<std::invalid_argument>
				([] {
				Sector s;
				s.SetName("");
			});
			Assert::ExpectException<std::invalid_argument>
				([] {
				World w;
				w.SetName("");
			});
			
		}

		TEST_METHOD(TestParser)
		{
			Entity s;
			s["AnInteger"] = 5;
			s["AFloat"] = 5.6f;
			s["LastInt"] = 22;
			s["LastFloat"] = 4.4f;

			WorldState ws;

			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("AnInteger * AFloat + 1"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 29);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("2 + 4 -5 *6 / 7^ 8 + (sin11 + cos12+  tan13 + (acos0.1 + asin(0.515)) +  atan0.16)+ pow(2, 2) + log(5)+  sqrt(4)+  invsqrt(5)"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 16.533823006125626);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("LastInt > 5"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 1);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("(LastInt < 5)"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 0);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("LastFloat == 22"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 0);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("LastFloat == 5 || LastInt == 22"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 1);
			}
			{
				ActionExpression& action = *new ActionExpression();
				action.SetExpression(std::string("!(LastFloat == 22)"));
				s.AdoptAction(action);
				action.Update(ws);
				Assert::IsTrue(action.GetResult() == 1);
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
		ConcreteFactory(Entity, TestClass);
		ConcreteFactory(Entity, AnotherClass);

	};

#ifdef _DEBUG
	_CrtMemState UnitTestTableParser::sStartMemState;
#endif
}
