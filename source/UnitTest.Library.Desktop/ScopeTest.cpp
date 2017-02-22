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

			Datum* pDeeperScopeDatum = nestedScope.Find("deeperScope");
			Assert::IsNotNull(pDeeperScopeDatum);
			Scope* pMainScope;
			Datum* pNestedScopeDatum = deeperScope.Search("nestedScope", &pMainScope);
			Assert::IsNotNull(pMainScope);
			Assert::IsNotNull(pNestedScopeDatum);
			Assert::IsTrue(&mainScope == pMainScope);
			Assert::IsTrue(mainScope == *pMainScope);

			Assert::IsTrue(std::string("nestedScope") == mainScope.FindName(&nestedScope));
		}

		TEST_METHOD(TestOrphan)
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
			Scope oneMoreScope;
			oneMoreScope = mainScope;
			Assert::IsTrue(oneMoreScope == mainScope);

			Scope moveConstructorScope(anotherScope);
			Assert::IsTrue(moveConstructorScope == mainScope);
			Scope moveAssignmentScope;
			moveAssignmentScope = std::move(oneMoreScope);
			Assert::IsTrue(moveAssignmentScope == mainScope);
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