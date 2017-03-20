#include "pch.h"
#include "FooXMLHelper.h"
#include <windows.h>
#pragma once

void FooXMLHelper::Initialize()
{
	std::string outputString = "Initializing...\n";
	OutputDebugStringA(outputString.c_str());
}

bool FooXMLHelper::StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
{
	std::string outputString = "<" + element;
	for (auto& attribute : attributes)
	{
		outputString += " " + attribute.first + "=" + attribute.second;
	}
	outputString += ">";
	OutputDebugStringA(outputString.c_str());

	return true;
}

bool FooXMLHelper::EndElementHandler(const std::string& element)
{
	std::string outputString = "</" + element + ">";
	OutputDebugStringA(outputString.c_str());

	return true;
}

bool FooXMLHelper::CharDataHandler(const char* content, const std::uint32_t length)
{
	length;
	OutputDebugStringA(content);
	return true;
}

IXMLParseHelper* FooXMLHelper::Clone()
{
	return new FooXMLHelper();
}
