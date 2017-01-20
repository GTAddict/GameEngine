#include "pch.h"
#include "CppUnitTest.h"
#include "Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine::Library;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(UnitTestLibraryDesktop)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
#endif
			_CrtMemCheckpoint(&endMemState);

			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Your application is leaking memory!");
			}
		}
		
		TEST_METHOD(TestEngineVersion)
		{
			Assert::AreEqual(Constants::kEngineVersion, Utils::GetEngineVersion(), "Invalid Engine Version!");
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif

	};

#ifdef _DEBUG
	_CrtMemState UnitTestLibraryDesktop::sStartMemState;
#endif
}