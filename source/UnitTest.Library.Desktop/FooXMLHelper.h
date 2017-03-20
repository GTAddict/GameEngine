#pragma once

#include "IXMLParseHelper.h"

namespace GameEngine
{
	namespace Library
	{
		class FooXMLHelper : public IXMLParseHelper
		{
		public:

			class FooSharedData : public XMLParseMaster::SharedData
			{
				RTTI_DECLARATIONS(FooSharedData, SharedData)

			public:
				FooSharedData() = default;
				~FooSharedData() override = default;
				SharedData* Clone() const override;
			};

			bool StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes) override;
			bool EndElementHandler(const std::string& element) override;
			bool CharDataHandler(const char* content, const std::uint32_t length) override;
			virtual IXMLParseHelper* Clone() override;
		};
	}
}