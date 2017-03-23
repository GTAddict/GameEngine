#include "pch.h"
#include "IXMLParseHelper.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		IXMLParseHelper::IXMLParseHelper()
			: mbIsInitialized(false)
			, mpSharedData(nullptr)
		{
		}

		void IXMLParseHelper::Initialize(XMLParseMaster::SharedData* sharedData)
		{
			if (sharedData != nullptr)
			{
				mpSharedData = sharedData;
				mbIsInitialized = true;
			}
		}

		void IXMLParseHelper::Finalize()
		{
			mpSharedData = nullptr;
			mbIsInitialized = false;
		}

		bool IXMLParseHelper::CharDataHandler(const char* content, const std::uint32_t length)
		{
			ENGINE_UNUSED(content);
			ENGINE_UNUSED(length);
			return false;
		}
	}
}