#pragma once

#include "XMLParseMaster.h"

using namespace GameEngine::Library;

class FooSharedData : public XMLParseMaster::SharedData
{
public:
	FooSharedData() = default;
	~FooSharedData() override = default;
	SharedData* Clone() const override;
};