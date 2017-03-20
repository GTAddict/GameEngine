#pragma once

#include <string>
#include "HashMap.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		class SharedData;

		class IXMLParseHelper
		{
		public:
			IXMLParseHelper();
			virtual void Initialize(XMLParseMaster::SharedData* sharedData);
			virtual bool StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes) = 0;
			virtual bool EndElementHandler(const std::string& element) = 0;
			virtual bool CharDataHandler(const char* content, const std::uint32_t length) = 0;
			virtual IXMLParseHelper* Clone() = 0;
			virtual ~IXMLParseHelper() = default;

		protected:
			bool						mbIsInitialized;
			XMLParseMaster::SharedData* mpSharedData;
		};
	}
}