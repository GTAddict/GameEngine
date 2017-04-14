#pragma once

#include "RTTI.h"
#include "Attributed.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include "Factory.h"

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

ConcreteFactory(RTTI, AttributedFoo);