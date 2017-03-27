#pragma once
#include "RTTI.h"

#pragma warning (disable : 4459)

using namespace GameEngine::Library;

class Foo : public RTTI
{
	RTTI_DECLARATIONS(Foo, RTTI)

public:
	Foo();
	Foo(const int data);
	Foo(const Foo& rhs);
	Foo(Foo&& rhs);
	Foo& operator=(const Foo& rhs);
	Foo& operator=(Foo&& rhs);
	bool operator==(const Foo& rhs);
	bool operator!=(const Foo& rhs);

	virtual ~Foo();

	int Data() const;

private:
	int* mpData;
};

RTTI_DEFINITIONS(Foo)

Foo::Foo()
	: mpData(nullptr)
{
}

Foo::Foo(const int data)
	: mpData(new int (data))
{
}

Foo::Foo(const Foo& rhs)
	: mpData(new int (*rhs.mpData))
{
}

Foo::Foo(Foo&& rhs)
	: mpData(rhs.mpData)
{
	rhs.mpData = nullptr;
}

Foo& Foo::operator=(const Foo& rhs)
{
	mpData = new int(*rhs.mpData);
	return *this;
}

Foo& Foo::operator=(Foo&& rhs)
{
	mpData = rhs.mpData;
	rhs.mpData = nullptr;
	return *this;
}

Foo::~Foo()
{
	delete mpData;
	mpData = nullptr;
}

bool Foo::operator==(const Foo& rhs)
{
	return *mpData == *rhs.mpData;
}

bool Foo::operator!=(const Foo& rhs)
{
	return !(*this == rhs);
}

int Foo::Data() const
{
	if (mpData == nullptr)
	{
		throw std::runtime_error("mpData is nullptr.");
	}

	return *mpData;
}