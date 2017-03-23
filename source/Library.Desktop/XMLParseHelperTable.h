#pragma once

#pragma once

#include "IXMLParseHelper.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		namespace TableParserConstants
		{
			const std::string SCOPE_IDENTIFIER		= "scope";
			const std::string INTEGER_IDENTIFIER	= "integer";
			const std::string FLOAT_IDENTIFIER		= "float";
			const std::string VECTOR_IDENTIFIER		= "vector";
			const std::string MATRIX_IDENTIFIER		= "matrix";
			const std::string STRING_IDENTIFIER		= "string";

			const std::string NAME_IDENTIFIER		= "name";
			const std::string VALUE_IDENTIFIER		= "value";

		}

		class Scope;

		class XMLParseHelperTable : public IXMLParseHelper
		{
		public:

			class SharedDataTable : public XMLParseMaster::SharedData
			{
				friend class XMLParseHelperTable;

				RTTI_DECLARATIONS(SharedDataTable, SharedData)

			public:
				SharedDataTable();
				~SharedDataTable() override;
				SharedData* Clone() const override;

				Scope* GetScope() const;

			private:

				Scope* mScope;
			};

			bool StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes) override;
			bool EndElementHandler(const std::string& element) override;
			virtual IXMLParseHelper* Clone() override;
		};
	}
}