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

ConcreteFactory(RTTI, Foo);