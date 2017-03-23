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
					sharedData->mScope = &sharedData->mScope->AppendScope(attributes[NAME_IDENTIFIER]);
				}

				return true;
			}
			else if (element == INTEGER_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
				datum.SetType(Datum::DatumType::Integer);
				datum.SetFromString(attributes[VALUE_IDENTIFIER]);
				return true;
			}
			else if (element == FLOAT_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
				datum.SetType(Datum::DatumType::Float);
				datum.SetFromString(attributes[VALUE_IDENTIFIER]);
				return true;
			}
			else if (element == MATRIX_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
				datum.SetType(Datum::DatumType::Matrix);
				datum.SetFromString(attributes[VALUE_IDENTIFIER]);
				return true;
			}
			else if (element == VECTOR_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
				datum.SetType(Datum::DatumType::Vector);
				datum.SetFromString(attributes[VALUE_IDENTIFIER]);
				return true;
			}
			else if (element == STRING_IDENTIFIER)
			{
				assert(sharedData->mScope != nullptr);
				Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
				datum.SetType(Datum::DatumType::String);
				datum.SetFromString(attributes[VALUE_IDENTIFIER]);
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

		IXMLParseHelper* XMLParseHelperTable::Clone()
		{
			return new XMLParseHelperTable();
		}
	}
}
