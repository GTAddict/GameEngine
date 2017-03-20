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

		std::string& FooXMLHelper::FooSharedData::GetConstructedString()
		{
			return mConstructedString;
		}

		bool FooXMLHelper::StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			FooSharedData* sharedData = static_cast<FooSharedData*>(mpSharedData);

			sharedData->mConstructedString += "<" + element;
			for (auto& attribute : attributes)
			{
				sharedData->mConstructedString += " " + attribute.first + "=\"" + attribute.second + "\"";
			}
			sharedData->mConstructedString += ">";

			return true;
		}

		bool FooXMLHelper::EndElementHandler(const std::string& element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			FooSharedData* sharedData = static_cast<FooSharedData*>(mpSharedData);
			sharedData->mConstructedString += "</" + element + ">";
			return true;
		}

		bool FooXMLHelper::CharDataHandler(const char* content, const std::uint32_t length)
		{
			if (!mbIsInitialized || !mpSharedData->Is(FooSharedData::TypeIdClass()))	return false;

			FooSharedData* sharedData = static_cast<FooSharedData*>(mpSharedData);
			sharedData->mConstructedString += std::string(content, length);
			return true;
		}

		IXMLParseHelper* FooXMLHelper::Clone()
		{
			return new FooXMLHelper();
		}

	}
}