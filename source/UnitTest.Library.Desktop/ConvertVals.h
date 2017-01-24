#pragma once

#include "DummyStruct.h"

static DummyStruct* sdStruct;
static const std::string name = "Dummy";

template <typename T>	inline T			ConvertValue(int i) { return static_cast<T>(i); }
template <>				inline bool			ConvertValue(int i) { return i != 0; }
template <>				inline DummyStruct	ConvertValue(int i) { return DummyStruct(i, name, sdStruct); }