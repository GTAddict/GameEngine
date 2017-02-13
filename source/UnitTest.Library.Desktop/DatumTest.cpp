#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"
#include <windows.h>

namespace UnitTestDatumConstants
{
	// ...
}

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestConstants;
using namespace UnitTestDatumConstants;

namespace UnitTestDatum
{
	TEST_CLASS(UnitTestDatum)
	{
	public:

		TEST_METHOD_EXTENSIVE(TestConstructor)

	private:

		template <typename T>
		void TestConstructor()
		{
			Datum d;
			d.SetType(Datum::DatumType::String);
			d.SetSize(10);
			d.Set(std::string("A"), 0);
			d.Set(std::string("B"), 1);
			d.Set(std::string("C"), 2);
			d.Set(std::string("D"), 3);
			d.Set(std::string("E"), 4);
			d.Set(std::string("Z"), 15);

			std::string output
				= d.Get<std::string>(0)
				+ d.Get<std::string>(1)
				+ d.Get<std::string>(2)
				+ d.Get<std::string>(3)
				+ d.Get<std::string>(4)
				+ d.Get<std::string>(11)
				+ d.Get<std::string>(15);


		}

	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#ifdef _DEBUG
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);

			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Your code is leaking memory!");
			}
#endif
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestDatum::sStartMemState;
#endif
}