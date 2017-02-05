#pragma once

#include "DummyStruct.h"

#define TEST_METHOD_EXTENSIVE(methodName)	\
TEST_METHOD(methodName)						\
{											\
	methodName<std::string>();				\
	methodName<bool>();						\
	methodName<std::int32_t>();				\
	methodName<float>();					\
	methodName<DummyStruct>();				\
											\
	methodName<std::string*>();				\
	methodName<bool*>();					\
	methodName<std::int32_t*>();			\
	methodName<float*>();					\
	methodName<DummyStruct*>();				\
}

static DummyStruct* sdStruct;
static const std::string name = "Dummy";

namespace UnitTestConstants
{
	const int startValue = 65;
	const int endValue = 81;
	const unsigned int expectedNumElements = endValue - startValue + 1;
	const int repsForString = 5;
}

template <class T>
inline typename std::enable_if<std::is_pointer<T>::value, T>::type ConvertValue(int i)
{
	static T array[expectedNumElements];
	return array[i - UnitTestConstants::startValue];
}

template <class T>
inline typename std::enable_if<!std::is_pointer<T>::value
	&& !std::is_same<T, bool>::value
	&& !std::is_same<T, DummyStruct>::value
	&& !std::is_same<T, std::string>::value, T>::type ConvertValue(int i)
{ 
	return static_cast<T>(i);
}

template <class T>
inline  typename std::enable_if<!std::is_pointer<T>::value && std::is_same<T, bool>::value, bool>::type ConvertValue(int i)
{
	return i != 0;
}

template <class T>
inline typename std::enable_if<!std::is_pointer<T>::value && std::is_same<T, DummyStruct>::value, DummyStruct>::type ConvertValue(int i)
{
	return DummyStruct(i, name, sdStruct);
}

template <class T>
inline typename std::enable_if<!std::is_pointer<T>::value && std::is_same<T, std::string>::value, std::string>::type ConvertValue(int i)
{
	return std::string(static_cast<char>(i - startValue), repsForString);
}