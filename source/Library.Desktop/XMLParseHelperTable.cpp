#include "pch.h"
#include "XMLParseHelperTable.h"
#include "Scope.h"
#include "Datum.h"

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

		bool XMLParseHelperTable::StartElementHandler(const std::string& element, const HashMapType attributes)
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
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Integer), attributes);
			}
			else if (element == FLOAT_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Float), attributes);
			}
			else if (element == MATRIX_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Matrix), attributes);
			}
			else if (element == VECTOR_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::Vector), attributes);
			}
			else if (element == STRING_IDENTIFIER)
			{
				return PopulateDatum(sharedData, static_cast<std::int32_t>(Datum::DatumType::String), attributes);
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

		bool XMLParseHelperTable::PopulateDatum(XMLParseHelperTable::SharedDataTable* sharedData, std::int32_t type, const HashMapType attributes)
		{
			assert(sharedData->mScope != nullptr);
			Datum& datum = sharedData->mScope->Append(attributes[NAME_IDENTIFIER]);
			datum.SetType(static_cast<Datum::DatumType>(type));
			HashMapType::Iterator indexIt = attributes.Find(INDEX_IDENTIFIER);
			std::uint32_t index = (indexIt == attributes.end() ? 0 : stoi(indexIt->second));
			datum.SetFromString(attributes[VALUE_IDENTIFIER], index);
			return true;
		}
	}
}
