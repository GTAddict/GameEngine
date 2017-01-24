#include "pch.h"
#include "CppUnitTest.h"

namespace UnitTestVectorConstants
{
	const int startValue = 65;
	const int endValue = 81;
	const float divisor = 100.0f;
	const unsigned int expectedNumElements = endValue - startValue + 1;
	const std::string name = "Name";
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTestVectorConstants;

namespace UnitTestVector
{
	TEST_CLASS(UnitTestVector)
	{
	public:

		TEST_METHOD(TestOne)
		{
			Vector<int> v;
			v.PushBack(1);
			v.PushBack(2);
			v.PushBack(3);
			v.PushBack(4);
			v.PushBack(5);
			v.PushBack(6);

			int a = v.Front();
			a;

			int b = v.Back();
			b;



			v.PopBack();
			v.PushBack(1);
		}

	private:
#ifdef _DEBUG
		static _CrtMemState sStartMemState;
#endif
	};

#ifdef _DEBUG
	_CrtMemState UnitTestVector::sStartMemState;
#endif
}

#include <vector>

namespace stdvectortest
{
	/*TEST_CLASS(vectortest)
	{
	public:
		TEST_METHOD(test)
		{
			std::vector<int> v;
			v.reserve(10);
			v[4] = 1;
		}
	};*/
}