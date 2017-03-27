#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"

using namespace GameEngine::Library;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAttributed
{
	TEST_CLASS(UnitTestAttributed)
	{
	private:

		TEST_METHOD(TestConstructor)
		{
			AttributedFoo* dumFoo = new AttributedFoo();
			AttributedFoo* AttrFoo1 = new AttributedFoo(
				1,
				2.0f,
				glm::vec4(),
				glm::mat4x4(),
				"hello",
				dumFoo,
				nullptr
			);

			AttributedFoo& attrFooRef = *AttrFoo1;
			Assert::IsTrue(attrFooRef["Integer"] == 1);
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(1 == attrFooRef["IntegerArray"].Get<std::int32_t>(i));
			}
			Assert::IsTrue(attrFooRef["Float"] == 2.0f);
			Assert::IsTrue(attrFooRef["Vector"] == glm::vec4());
			Assert::IsTrue(attrFooRef["Matrix"] == glm::mat4x4());
			Assert::IsTrue(attrFooRef["Integer"] == 1);
			Assert::IsTrue(attrFooRef["NestedFoo"] == PSCOPE_CAST(dumFoo));
			Assert::IsTrue(attrFooRef["RTTI"] == PRTTI_CAST(nullptr));

			attrFooRef.AppendAuxiliaryAttribute("AuxAttr");

			Assert::IsTrue(attrFooRef.IsPrescribedAttribute("Integer"));
			Assert::IsFalse(attrFooRef.IsPrescribedAttribute("AuxAttr"));
			Assert::IsTrue(attrFooRef.IsAuxiliaryAttribute("AuxAttr"));
			Assert::IsTrue(attrFooRef.IsAttribute("RTTI"));
			Assert::IsFalse(attrFooRef.IsAttribute("sdfsdf"));

			auto func = [&attrFooRef] { attrFooRef.AppendAuxiliaryAttribute("Integer"); };
			Assert::ExpectException<std::invalid_argument>(func);

			delete AttrFoo1;
		}

		TEST_METHOD(TestCopySemantics)
		{
			AttributedFoo* dumFoo = new AttributedFoo();
			AttributedFoo* AttrFoo1 = new AttributedFoo(
				1,
				2.0f,
				glm::vec4(),
				glm::mat4x4(),
				"hello",
				dumFoo,
				nullptr
			);

			AttributedFoo& attrFooRef = *AttrFoo1;
			AttributedFoo aCopy(attrFooRef);
			Assert::IsTrue(attrFooRef["Integer"] == aCopy["Integer"]);
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(aCopy["IntegerArray"].Get<std::int32_t>(i) == attrFooRef["IntegerArray"].Get<std::int32_t>(i));
			}
			Assert::IsTrue(attrFooRef["Float"] == aCopy["Float"]);
			Assert::IsTrue(attrFooRef["Vector"] == aCopy["Vector"]);
			Assert::IsTrue(attrFooRef["Matrix"] == aCopy["Matrix"]);

			AttributedFoo anotherCopy;
			anotherCopy = attrFooRef;
			Assert::IsTrue(attrFooRef["Integer"] == anotherCopy["Integer"]);
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(anotherCopy["IntegerArray"].Get<std::int32_t>(i) == attrFooRef["IntegerArray"].Get<std::int32_t>(i));
			}
			Assert::IsTrue(attrFooRef["Float"] == anotherCopy["Float"]);
			Assert::IsTrue(attrFooRef["Vector"] == anotherCopy["Vector"]);
			Assert::IsTrue(attrFooRef["Matrix"] == anotherCopy["Matrix"]);

			delete AttrFoo1;
		}

		TEST_METHOD(TestMoveSemantics)
		{
			AttributedFoo* dumFoo = new AttributedFoo();
			AttributedFoo* AttrFoo1 = new AttributedFoo(
				1,
				2.0f,
				glm::vec4(),
				glm::mat4x4(),
				"hello",
				dumFoo,
				nullptr
			);

			AttributedFoo& attrFooRef = *AttrFoo1;
			AttributedFoo aSafeCopy = attrFooRef;
			AttributedFoo aMove(std::move(attrFooRef));
			Assert::IsTrue(aSafeCopy["Integer"] == aMove["Integer"]);
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(aMove["IntegerArray"].Get<std::int32_t>(i) == aSafeCopy["IntegerArray"].Get<std::int32_t>(i));
			}
			Assert::IsTrue(aSafeCopy["Float"] == aMove["Float"]);
			Assert::IsTrue(aSafeCopy["Vector"] == aMove["Vector"]);
			Assert::IsTrue(aSafeCopy["Matrix"] == aMove["Matrix"]);
			
			AttributedFoo anotherMove;
			anotherMove = std::move(aMove);
			Assert::IsTrue(aSafeCopy["Integer"] == anotherMove["Integer"]);
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(anotherMove["IntegerArray"].Get<std::int32_t>(i) == aSafeCopy["IntegerArray"].Get<std::int32_t>(i));
			}
			Assert::IsTrue(aSafeCopy["Float"] == anotherMove["Float"]);
			Assert::IsTrue(aSafeCopy["Vector"] == anotherMove["Vector"]);
			Assert::IsTrue(aSafeCopy["Matrix"] == anotherMove["Matrix"]);

			delete AttrFoo1;
		}

	public:

#ifdef _DEBUG
		TEST_METHOD_INITIALIZE(Initialize)
		{
			AttributedFoo* AttrFoo1 = new AttributedFoo(
				1,
				2.0f,
				glm::vec4(),
				glm::mat4x4(),
				"hello",
				new AttributedFoo(),
				nullptr
			);
			delete AttrFoo1;

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
	_CrtMemState UnitTestAttributed::sStartMemState;
#endif
}