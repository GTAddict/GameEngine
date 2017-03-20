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
	}
}