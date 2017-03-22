#include "pch.h"
#include "XMLParseHelperTable.h"
#include "Scope.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(XMLParseHelperTable::SharedDataTable)

		using namespace TableParserConstants;

		XMLParseHelperTable::SharedDataTable::SharedDataTable()
			: mScope(nullptr)
		{
		}

		XMLParseHelperTable::SharedDataTable::~SharedDataTable()
		{
			delete mScope;
		}

		XMLParseMaster::SharedData* XMLParseHelperTable::SharedDataTable::Clone() const
		{
			return new SharedDataTable();
		}

		Scope* XMLParseHelperTable::SharedDataTable::GetScope() const
		{
			return mScope;
		}

		bool XMLParseHelperTable::StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(SharedDataTable::TypeIdClass()))	return false;

			SharedDataTable* sharedData = mpSharedData->As<SharedDataTable>();

			if (element == SCOPE_IDENTIFIER)
			{
				if (sharedData->mScope == nullptr)
				{
					sharedData->mScope = new Scope();
				}
				else
				{
					sharedData->mScope = &sharedData->mScope->AppendScope(attributes[SCOPE_NAME_IDEFNTIFIER]);
				}

				return true;
			}

			return false;
		}

		bool XMLParseHelperTable::EndElementHandler(const std::string& element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(SharedDataTable::TypeIdClass()))	return false;

			SharedDataTable* sharedData = mpSharedData->As<SharedDataTable>();

			if (element == SCOPE_IDENTIFIER)
			{
				if (sharedData->GetDepth() > 1)
				{
					assert(sharedData->mScope->GetParent() != nullptr);
					sharedData->mScope = sharedData->mScope->GetParent();
				}
				
				return true;
			}

			return false;
		}

		bool XMLParseHelperTable::CharDataHandler(const char* content, const std::uint32_t length)
		{
			ENGINE_UNUSED(content);
			ENGINE_UNUSED(length);
			return false;
		}

		IXMLParseHelper* XMLParseHelperTable::Clone()
		{
			return new XMLParseHelperTable();
		}
	}
}
