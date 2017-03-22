#pragma once

#pragma once

#include "IXMLParseHelper.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		namespace ScopeConstants
		{
			const std::string SCOPE_IDENTIFIER = "scope";
			const std::string SCOPE_NAME_IDEFNTIFIER = "name";
		}

		class Scope;

		class ScopeXMLHelper : public IXMLParseHelper
		{
		public:

			class ScopeSharedData : public XMLParseMaster::SharedData
			{
				friend class ScopeXMLHelper;

				RTTI_DECLARATIONS(ScopeSharedData, SharedData)

			public:
				ScopeSharedData();
				~ScopeSharedData() override;
				SharedData* Clone() const override;

				Scope* GetScope() const;

			private:

				Scope* mScope;
			};

			bool StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes) override;
			bool EndElementHandler(const std::string& element) override;
			bool CharDataHandler(const char* content, const std::uint32_t length) override;
			virtual IXMLParseHelper* Clone() override;
		};
	}
}