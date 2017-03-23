#pragma once

#include "IXMLParseHelper.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		class Datum;
		enum class DatumType;

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
			const std::string INDEX_IDENTIFIER		= "index";

		}

		class Scope;

		class XMLParseHelperTable : public IXMLParseHelper
		{
			typedef HashMap<std::string, std::string> HashMapType;

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

			bool StartElementHandler(const std::string& element, const HashMapType attributes) override;
			bool EndElementHandler(const std::string& element) override;
			virtual IXMLParseHelper* Clone() override;

		private:

			// Casting type to an int back to avoid a Datum depencency in this header. You can't forward-declare
			// an embedded enum.
			bool PopulateDatum(SharedDataTable* sharedData, std::int32_t type, const HashMapType attributes);
		};
	}
}