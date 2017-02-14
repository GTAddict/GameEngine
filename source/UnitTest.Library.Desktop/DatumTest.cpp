#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "ConvertVals.h"
#include <windows.h>
#include "Foo.h"

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

	private:

		TEST_METHOD(TestConstructionAssignment)
		{
			{
				std::int32_t number = 5;
				Datum scalarIntDatum;
				scalarIntDatum = number;
				Datum intDatum = scalarIntDatum;
				Assert::IsTrue(intDatum == scalarIntDatum);
				Assert::IsFalse(intDatum != scalarIntDatum);
				Assert::IsTrue(intDatum == number);
				Assert::IsFalse(intDatum != number);
				Datum moveDatum = std::move(intDatum);
				Assert::IsTrue(scalarIntDatum == moveDatum);
				scalarIntDatum = scalarIntDatum;
				scalarIntDatum = std::move(scalarIntDatum);
				Datum scalarIntDatumAssign;
				scalarIntDatumAssign = 5;
				Datum intDatumAssign;
				intDatumAssign = scalarIntDatumAssign;
				Assert::IsTrue(intDatumAssign == scalarIntDatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(intDatumAssign);
				Assert::IsTrue(scalarIntDatumAssign == moveDatumAssign);
			}
			{
				float number = 5.0f;
				Datum scalarfloatDatum;
				scalarfloatDatum = number;
				Datum floatDatum = scalarfloatDatum;
				Assert::IsTrue(floatDatum == scalarfloatDatum);
				Assert::IsFalse(floatDatum != scalarfloatDatum);
				Assert::IsTrue(floatDatum == number);
				Assert::IsFalse(floatDatum != number);
				Datum moveDatum = std::move(floatDatum);
				Assert::IsTrue(scalarfloatDatum == moveDatum);
				scalarfloatDatum = scalarfloatDatum;
				scalarfloatDatum = std::move(scalarfloatDatum);
				Datum scalarfloatDatumAssign;
				scalarfloatDatumAssign = 5.0f;
				Datum floatDatumAssign;
				floatDatumAssign = scalarfloatDatumAssign;
				Assert::IsTrue(floatDatumAssign == scalarfloatDatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(floatDatumAssign);
				Assert::IsTrue(scalarfloatDatumAssign == moveDatumAssign);
			}
			{
				std::string value = "hello";
				Datum scalarstringDatum;
				scalarstringDatum = value;
				Datum stringDatum = scalarstringDatum;
				Assert::IsTrue(stringDatum == scalarstringDatum);
				Assert::IsFalse(stringDatum != scalarstringDatum);
				Assert::IsTrue(stringDatum == value);
				Assert::IsFalse(stringDatum != value);
				Datum moveDatum = std::move(stringDatum);
				Assert::IsTrue(scalarstringDatum == moveDatum);
				scalarstringDatum = scalarstringDatum;
				scalarstringDatum = std::move(scalarstringDatum);
				Datum scalarstringDatumAssign;
				scalarstringDatumAssign = std::string("hello");
				Datum stringDatumAssign;
				stringDatumAssign = scalarstringDatumAssign;
				Assert::IsTrue(stringDatumAssign == scalarstringDatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(stringDatumAssign);
				Assert::IsTrue(scalarstringDatumAssign == moveDatumAssign);
			}
			{
				glm::vec4 value = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
				Datum scalarvec4Datum;
				scalarvec4Datum = value;
				Datum vec4Datum = scalarvec4Datum;
				Assert::IsTrue(vec4Datum == scalarvec4Datum);
				Assert::IsFalse(vec4Datum != scalarvec4Datum);
				Assert::IsTrue(vec4Datum == value);
				Assert::IsFalse(vec4Datum != value);
				Datum moveDatum = std::move(vec4Datum);
				Assert::IsTrue(scalarvec4Datum == moveDatum);
				scalarvec4Datum = scalarvec4Datum;
				scalarvec4Datum = std::move(scalarvec4Datum);
				Datum scalarvec4DatumAssign;
				scalarvec4DatumAssign = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
				Datum vec4DatumAssign;
				vec4DatumAssign = scalarvec4DatumAssign;
				Assert::IsTrue(vec4DatumAssign == scalarvec4DatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(vec4DatumAssign);
				Assert::IsTrue(scalarvec4DatumAssign == moveDatumAssign);
			}
			{
				glm::mat4x4 value = glm::mat4x4(
					1.0f,	2.0f,	3.0f,	4.0f,
					5.0f,	6.0f,	7.0f,	8.0f,
					9.0f,	10.0f,	11.0f,	12.0f,
					13.0f,	14.0f,	15.0f,	16.0f
				);
				Datum scalarmat4x4Datum;
				scalarmat4x4Datum = value;
				Datum mat4x4Datum = scalarmat4x4Datum;
				Assert::IsTrue(mat4x4Datum == scalarmat4x4Datum);
				Assert::IsFalse(mat4x4Datum != scalarmat4x4Datum);
				Assert::IsTrue(mat4x4Datum == value);
				Assert::IsFalse(mat4x4Datum != value);
				Datum moveDatum = std::move(mat4x4Datum);
				Assert::IsTrue(scalarmat4x4Datum == moveDatum);
				scalarmat4x4Datum = scalarmat4x4Datum;
				scalarmat4x4Datum = std::move(scalarmat4x4Datum);
				Datum scalarmat4x4DatumAssign;
				scalarmat4x4DatumAssign = glm::mat4x4(
					1.0f, 2.0f, 3.0f, 4.0f,
					5.0f, 6.0f, 7.0f, 8.0f,
					9.0f, 10.0f, 11.0f, 12.0f,
					13.0f, 14.0f, 15.0f, 16.0f
				);
				Datum mat4x4DatumAssign;
				mat4x4DatumAssign = scalarmat4x4DatumAssign;
				Assert::IsTrue(mat4x4DatumAssign == scalarmat4x4DatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(mat4x4DatumAssign);
				Assert::IsTrue(scalarmat4x4DatumAssign == moveDatumAssign);
			}
			{
				RTTI* value = new Foo(5);
				Datum scalarRTTIDatum;
				scalarRTTIDatum = value;
				Datum RTTIDatum = scalarRTTIDatum;
				Assert::IsTrue(RTTIDatum == scalarRTTIDatum);
				Assert::IsFalse(RTTIDatum != scalarRTTIDatum);
				Assert::IsTrue(RTTIDatum == value);
				Assert::IsFalse(RTTIDatum != value);
				Datum moveDatum = std::move(RTTIDatum);
				Assert::IsTrue(scalarRTTIDatum == moveDatum);
				scalarRTTIDatum = scalarRTTIDatum;
				scalarRTTIDatum = std::move(scalarRTTIDatum);
				Datum scalarRTTIDatumAssign;
				scalarRTTIDatumAssign = static_cast<RTTI*>(new Foo(5));
				Datum RTTIDatumAssign;
				RTTIDatumAssign = scalarRTTIDatumAssign;
				Assert::IsTrue(RTTIDatumAssign == scalarRTTIDatumAssign);
				Datum moveDatumAssign;
				moveDatumAssign = std::move(RTTIDatumAssign);
				Assert::IsTrue(scalarRTTIDatumAssign == moveDatumAssign);
				delete value;
				delete scalarRTTIDatumAssign.Get<RTTI*>();
			}
		}

		TEST_METHOD(TestType)
		{
			{
				Datum d;
				d = 1;
				Assert::IsTrue(d.Type() == Datum::DatumType::Integer);
				Datum e;
				e.SetType(Datum::DatumType::Integer);
				Assert::IsTrue(e.Type() == Datum::DatumType::Integer);
			}
			{
				Datum d;
				d = 1.0f;
				Assert::IsTrue(d.Type() == Datum::DatumType::Float);
				Datum e;
				e.SetType(Datum::DatumType::Float);
				Assert::IsTrue(e.Type() == Datum::DatumType::Float);
			}
			{
				Datum d;
				d = glm::vec4();
				Assert::IsTrue(d.Type() == Datum::DatumType::Vector);
				Datum e;
				e.SetType(Datum::DatumType::Vector);
				Assert::IsTrue(e.Type() == Datum::DatumType::Vector);
			}
			{
				Datum d;
				d = glm::mat4x4();
				Assert::IsTrue(d.Type() == Datum::DatumType::Matrix);
				Datum e;
				e.SetType(Datum::DatumType::Matrix);
				Assert::IsTrue(e.Type() == Datum::DatumType::Matrix);
			}
			{
				Datum d;
				d = std::string("hello");
				Assert::IsTrue(d.Type() == Datum::DatumType::String);
				Datum e;
				e.SetType(Datum::DatumType::String);
				Assert::IsTrue(e.Type() == Datum::DatumType::String);
			}
			{
				Datum d;
				d = static_cast<RTTI*>(new Foo(3));
				Assert::IsTrue(d.Type() == Datum::DatumType::Pointer);
				Datum e;
				e.SetType(Datum::DatumType::Pointer);
				Assert::IsTrue(e.Type() == Datum::DatumType::Pointer);
				delete d.Get<RTTI*>();
			}
		}

		TEST_METHOD(TestSizeClearGetSet)
		{
			{
				Datum d;
				d.SetType(Datum::DatumType::Integer);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(i, i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue(i == d.Get<std::int32_t>(i));
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Float);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(static_cast<float>(i), i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue(static_cast<float>(i) == d.Get<float>(i));
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Vector);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(glm::vec4(i, i, i, i), i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue(glm::vec4(i, i, i, i) == d.Get<glm::vec4>(i));
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Matrix);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(glm::mat4x4(i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i) , i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue(
						glm::mat4x4(i, i, i, i, i, i, i, i, i, i, i, i, i, i, i, i) == d.Get<glm::mat4x4>(i));
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::String);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(std::string("hello"), i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue("hello" == d.Get<std::string>(i));
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
			{
				Datum d;
				d.SetType(Datum::DatumType::Pointer);
				Assert::IsTrue(d.Size() == 0);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				for (std::int32_t i = 0; i < 20; ++i)
				{
					d.Set(static_cast<RTTI*>(new Foo(i)), i);
				}
				for (std::int32_t i = 0; i < 20; ++i)
				{
					Assert::IsTrue(Foo(i) == *(static_cast<Foo*>(d.Get<RTTI*>(i))));
					delete d.Get<RTTI*>(i);
				}
				Assert::IsTrue(d.Size() == 20);
				d.SetSize(10);
				Assert::IsTrue(d.Size() == 10);
				d.Clear();
				Assert::IsTrue(d.Size() == 0);
			}
		}

		TEST_METHOD(TestSetStringToString)
		{
			{
				Datum d;
				std::string text = "Integer 55";
				d.SetType(Datum::DatumType::Integer);
				d.SetFromString(text);
				Assert::IsTrue(d == 55);
				Assert::AreEqual(text, d.ToString<std::int32_t>());
			}
			{
				Datum d;
				std::string text = "Float 5.5";
				d.SetType(Datum::DatumType::Float);
				d.SetFromString(text);
				Assert::IsTrue(d == 5.5f);
				Assert::AreEqual(text, d.ToString<float>());
			}
			{
				Datum d;
				std::string text = "Vector 1.1 2.2 3.3 4.4";
				d.SetType(Datum::DatumType::Vector);
				d.SetFromString(text);
				Assert::IsTrue(d == glm::vec4(1.1, 2.2, 3.3, 4.4));
				Assert::AreEqual(text, d.ToString<glm::vec4>());
			}
			{
				Datum d;
				std::string text = "Matrix 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6";
				d.SetType(Datum::DatumType::Matrix);
				d.SetFromString(text);
				Assert::IsTrue(d == glm::mat4x4(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6));
				Assert::AreEqual(text, d.ToString<glm::mat4x4>());
			}
			{
				Datum d;
				std::string text = "String hello";
				d.SetType(Datum::DatumType::String);
				d.SetFromString(text);
				Assert::IsTrue(d == std::string("hello"));
				Assert::AreEqual(text, d.ToString<std::string>());
			}
		}

		TEST_METHOD(TestExceptions)
		{
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = 5;
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Pointer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<RTTI*>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<RTTI*>(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func5);
			}
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = 5.0f;
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Pointer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<RTTI*>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<RTTI*>(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func5);
			}
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Pointer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<RTTI*>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<RTTI*>(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func5);
			}
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = glm::mat4();
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Pointer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<RTTI*>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<RTTI*>(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func5);
			}
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = std::string("hello");
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Pointer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<RTTI*>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<RTTI*>(nullptr); };
				Assert::ExpectException<std::invalid_argument>(func5);
			}
			{
				Datum d;
				auto func0 = [&d] { d.SetSize(10); };
				Assert::ExpectException<std::domain_error>(func0);
				d = static_cast<RTTI*>(new Foo(10));
				auto func1 = [&d] { d.SetFromString(""); };
				Assert::ExpectException<std::invalid_argument>(func1);
				auto func2 = [&d] { d.SetType(Datum::DatumType::Integer); };
				Assert::ExpectException<std::domain_error>(func2);
				Datum e;
				auto func3 = [&e] { e.SetFromString(""); };
				Assert::ExpectException<std::domain_error>(func3);
				auto func4 = [&d] { d.Get<float>(); };
				Assert::ExpectException<std::invalid_argument>(func4);
				auto func5 = [&d] { d.Set<float>(2.2f); };
				Assert::ExpectException<std::invalid_argument>(func5);
				delete d.Get<RTTI*>();
			}
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