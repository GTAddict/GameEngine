#include "pch.h"
#include "FooXMLHelper.h"
#include <windows.h>

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(FooXMLHelper::FooSharedData)

		XMLParseMaster::SharedData* FooXMLHelper::FooSharedData::Clone() const
		{
			return SharedData::Clone();
		}

		bool FooXMLHelper::StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			FooSharedData* sharedData = static_cast<FooSharedData*>(mpSharedData);

			std::string outputString = "([" + std::to_string(sharedData->GetDepth()) + "]" + element;
			for (auto& attribute : attributes)
			{
				outputString += " " + attribute.first + ":" + attribute.second;
			}
			outputString += ")";
			OutputDebugStringA(outputString.c_str());

			return true;
		}

		bool FooXMLHelper::EndElementHandler(const std::string& element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			FooSharedData* sharedData = static_cast<FooSharedData*>(mpSharedData);

			std::string outputString = "(/" + element + "[" + std::to_string(sharedData->GetDepth()) + "])";
			OutputDebugStringA(outputString.c_str());

			return true;
		}

		bool FooXMLHelper::CharDataHandler(const char* content, const std::uint32_t length)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			std::string outputString(content, length);
			OutputDebugStringA(outputString.c_str());
			return true;
		}

		IXMLParseHelper* FooXMLHelper::Clone()
		{
			return new FooXMLHelper();
		}

	}
}