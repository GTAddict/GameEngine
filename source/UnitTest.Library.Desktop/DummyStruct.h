#pragma once
#include <string>
#include <CppUnitTestAssert.h>

struct DummyStruct
{
	int ID;
	std::string name;
	void* customData;
	int* pOwnedInteger;

	DummyStruct() : ID(0), customData(nullptr), pOwnedInteger(nullptr) { pOwnedInteger = new int; }
	DummyStruct(int inID, std::string inName, void* inCustomData)
		: ID(inID), name(inName), customData(inCustomData), pOwnedInteger(new int(inID)) {};
	~DummyStruct() { delete pOwnedInteger; }

	DummyStruct(const DummyStruct& rhs) : ID(0), customData(nullptr), pOwnedInteger(nullptr)
	{
		pOwnedInteger = new int(*(rhs.pOwnedInteger));
		ID = rhs.ID;
		name = rhs.name;
		customData = rhs.customData;
	}

	DummyStruct& operator=(const DummyStruct& rhs)
	{
		if (this != &rhs)
		{
			delete pOwnedInteger;
			pOwnedInteger = new int(*(rhs.pOwnedInteger));
			ID = rhs.ID;
			name = rhs.name;
			customData = rhs.customData;
		}

		return *this;
	}

	bool operator==(const DummyStruct& rhs) const
	{
		return (*pOwnedInteger == *rhs.pOwnedInteger) && ID == rhs.ID && name == rhs.name && customData == rhs.customData;
	}

	bool operator!=(const DummyStruct& rhs) const
	{
		return !(*this == rhs);
	}
};

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<DummyStruct>(const DummyStruct& t)
			{
				RETURN_WIDE_STRING(t.ID);
			}

			template<> inline std::wstring ToString<DummyStruct>(DummyStruct* t)
			{
				RETURN_WIDE_STRING(t->ID);
			}
		}
	}
}
