#include "pch.h"
#include "AttributedFoo.h"

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo(
	const int integer,
	const float floating,
	const glm::vec4&	vector4,
	const glm::mat4x4& matrix4x4,
	const std::string& theString,
	AttributedFoo* foo,
	RTTI* rtti
)
	: mInteger(integer)
	, mFloat(floating)
	, mVector(vector4)
	, mMatrix(matrix4x4)
	, mString(theString)
	, mpNestedAttributedFoo(foo)
	, mpRTTI(rtti)
{
	for (int i = 0; i < 10; ++i)
	{
		mIntegerArray[i] = integer;
	}

	AddPrescribedAttributeExternal("Integer", mInteger);
	AddPrescribedAttributeExternal("IntegerArray", mIntegerArray, 10);
	AddPrescribedAttributeExternal("Float", mFloat);
	AddPrescribedAttributeExternal("Vector", mVector);
	AddPrescribedAttributeExternal("Matrix", mMatrix);
	AddPrescribedAttributeExternal("String", mString);
	AddPrescribedAttributeExternal("RTTI", mpRTTI);

	AddNestedScope("NestedFoo", mpNestedAttributedFoo);
}