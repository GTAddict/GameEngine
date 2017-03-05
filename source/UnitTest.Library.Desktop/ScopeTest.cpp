#include "pch.h"
#include "CppUnitTest.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestScope
{
	TEST_CLASS(UnitTestScope)
	{

	private:

		TEST_METHOD(TestConstructor)
		{
			Scope scope;
			Scope anotherScope(20);
		}

		TEST_METHOD(TestAppendBracketOperator)
		{
			Scope mainScope;
			Datum& datum = mainScope["nestedScope"];
			Datum& insertedDatum = mainScope[0];
			Assert::IsTrue(datum == insertedDatum);
			Assert::IsTrue(datum == mainScope["nestedScope"]);
		}

		TEST_METHOD(TestAppendFindSearch)
		{
			Scope mainScope;
			Scope& nestedScope = mainScope.AppendScope("nestedScope");
			Scope& deeperScope = nestedScope.AppendScope("deeperScope");
			Scope& deeperScopeAgain = nestedScope.AppendScope("deeperScope");
			deeperScopeAgain;

			Datum* pDeeperScopeDatum = nestedScope.Find("deeperScope");
			Assert::IsNotNull(pDeeperScopeDatum);
			Datum* pShouldBeNull = nestedScope.Find("bumpkis");
			Assert::IsNull(pShouldBeNull);
			Scope* pMainScope;
			Datum* pNestedScopeDatum = deeperScope.Search("nestedScope", &pMainScope);
			Assert::IsNotNull(pMainScope);
			Assert::IsNotNull(pNestedScopeDatum);
			Assert::IsTrue(&mainScope == pMainScope);
			Assert::IsTrue(mainScope == *pMainScope);
			Scope* shouldBeNullAgain = nullptr;
			Datum* pShouldAlsoBeNull = nestedScope.Search("bleep!", &shouldBeNullAgain);
			Assert::IsNull(shouldBeNullAgain);
			Assert::IsNull(pShouldAlsoBeNull);

			Assert::IsTrue(std::string("nestedScope") == mainScope.FindName(nestedScope));
		}

		TEST_METHOD(TestAdoptOrphan)
		{
			Scope mainScope;
			Scope& nestedScope = mainScope.AppendScope("nestedScope");
			Scope& deeperScope = nestedScope.AppendScope("deeperScope");

			mainScope.Append("mainScopeInt") = 10;
			mainScope.Append("mainScopeString") = std::string("Hello");
			nestedScope.Append("nestedScopeInt") = 20;
			nestedScope.Append("nestedScopeString") = std::string("How");
			deeperScope.Append("deeperScopeInt") = 30;
			deeperScope.Append("deeperScopeString") = std::string("Are");

			mainScope.Adopt(deeperScope, "nestedScope");
		}

		TEST_METHOD(TestCopyMoveSemantics)
		{
			Scope mainScope;
			Scope& nestedScope = mainScope.AppendScope("nestedScope");
			Scope& deeperScope = nestedScope.AppendScope("deeperScope");

			mainScope.Append("mainScopeInt") = 10;
			mainScope.Append("mainScopeString") = std::string("Hello");
			nestedScope.Append("nestedScopeInt") = 20;
			nestedScope.Append("nestedScopeString") = std::string("How");
			deeperScope.Append("deeperScopeInt") = 30;
			deeperScope.Append("deeperScopeString") = std::string("Are");

			Scope anotherScope = mainScope;
			Assert::IsTrue(anotherScope == mainScope);
			mainScope = mainScope;
			Scope oneMoreScope;
			oneMoreScope = mainScope;
			Assert::IsTrue(oneMoreScope == mainScope);

			Scope moveConstructorScope(anotherScope);
			Assert::IsTrue(moveConstructorScope == mainScope);
			mainScope = std::move(mainScope);
			Scope moveAssignmentScope;
			moveAssignmentScope = std::move(oneMoreScope);
			Assert::IsTrue(moveAssignmentScope == mainScope);
		}

		TEST_METHOD(TestInequalityFind)
		{
			Scope firstScope, secondScope;
			Assert::IsTrue(firstScope.Append("Hello") == firstScope["Hello"]);
			Assert::IsTrue(firstScope != secondScope);
			Assert::IsTrue(firstScope.FindName(secondScope) == std::string());
		}

		TEST_METHOD(TestExceptions)
		{
			Scope scope;
			scope.AppendScope("SomeScope");
			auto func = [&scope]
			{
				const Scope& s = scope;
				s["exception"];
			};
			Assert::ExpectException<std::out_of_range>(func);
			auto func2 = [&scope] {scope.Search("SomeScope", nullptr); };	// should not throw any exception
			auto func3 = [&scope]
			{
				scope.Append("anInteger").SetType(Datum::DatumType::Integer);
				scope.AppendScope("anInteger");
			};
			Assert::ExpectException<std::runtime_error>(func3);
			auto func4 = [&scope] { scope.Adopt(scope, "wtf"); };
			Assert::ExpectException<std::runtime_error>(func4);
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
	_CrtMemState UnitTestScope::sStartMemState;
#endif
}