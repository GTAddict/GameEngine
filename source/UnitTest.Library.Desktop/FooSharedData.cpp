#include "pch.h"
#include "FooSharedData.h"

XMLParseMaster::SharedData* FooSharedData::Clone() const
{
	return SharedData::Clone();
}
