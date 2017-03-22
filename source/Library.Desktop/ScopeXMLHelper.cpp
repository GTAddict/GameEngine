#include "pch.h"
#include "ScopeXMLHelper.h"
#include "Scope.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(ScopeXMLHelper::ScopeSharedData)

		using namespace ScopeConstants;

		ScopeXMLHelper::ScopeSharedData::ScopeSharedData()
			: mScope(nullptr)
		{
		}

		ScopeXMLHelper::ScopeSharedData::~ScopeSharedData()
		{
			delete mScope;
		}

		XMLParseMaster::SharedData* ScopeXMLHelper::ScopeSharedData::Clone() const
		{
			return new ScopeSharedData();
		}

		Scope* ScopeXMLHelper::ScopeSharedData::GetScope() const
		{
			return mScope;
		}

		bool ScopeXMLHelper::StartElementHandler(const std::string& element, const HashMap<std::string, std::string> attributes)
		{
			if (!mbIsInitialized || !mpSharedData->Is(ScopeSharedData::TypeIdClass()))	return false;

			ScopeSharedData* sharedData = static_cast<ScopeSharedData*>(mpSharedData);

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

		bool ScopeXMLHelper::EndElementHandler(const std::string& element)
		{
			if (!mbIsInitialized || !mpSharedData->Is(ScopeSharedData::TypeIdClass()))	return false;

			ScopeSharedData* sharedData = static_cast<ScopeSharedData*>(mpSharedData);

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

		bool ScopeXMLHelper::CharDataHandler(const char* content, const std::uint32_t length)
		{
			ENGINE_UNUSED(content);
			ENGINE_UNUSED(length);
			return false;
		}

		IXMLParseHelper* ScopeXMLHelper::Clone()
		{
			return new ScopeXMLHelper();
		}
	}
}
