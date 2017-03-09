#pragma once

#pragma once
#include "RTTI.h"
#include "Attributed.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>

using namespace GameEngine::Library;

class AttributedFoo : public Attributed
{
	RTTI_DECLARATIONS(AttributedFoo, Attributed)

public:

	AttributedFoo() {};
	AttributedFoo(
		const int integer,
		const float floating,
		const glm::vec4&	vector4,
		const glm::mat4x4& matrix4x4,
		const std::string& theString,
		AttributedFoo* foo,
		RTTI* rtti
		);

private:

	int				mInteger;
	int				mIntegerArray[10];
	float			mFloat;
	glm::vec4		mVector;
	glm::mat4x4		mMatrix;
	std::string		mString;
	AttributedFoo*	mpNestedAttributedFoo;
	Scope*			mpUnknownScope;
	RTTI*			mpRTTI;
};

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
	AddNestedScope("NestedFoo", mpNestedAttributedFoo);
	AddNestedScope("NestedFoo", nullptr);
	AddNestedScope("UnknownScope");
	AddNestedScope("UnknownScope");
}