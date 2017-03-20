#pragma once

#include "IXMLParseHelper.h"

using namespace GameEngine::Library;

class FooXMLHelper : public IXMLParseHelper
{
	void Initialize() override;
	bool StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes) override;
	virtual bool EndElementHandler(const std::string& element) override;
	virtual bool CharDataHandler(const char* content, const std::uint32_t length) override;
	virtual IXMLParseHelper* Clone() override;
};