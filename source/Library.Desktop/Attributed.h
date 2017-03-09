#pragma once
#include "Scope.h"
#include "RTTI.h"

#define PRTTI_CAST(x)	static_cast<RTTI*>(x)
#define PSCOPE_CAST(x)	static_cast<Scope*>(x)

namespace GameEngine
{
	namespace Library
	{
		class Attributed : public Scope
		{
			RTTI_DECLARATIONS(Attributed, Scope);

		public:

			Attributed();
			Attributed(const Attributed& rhs);
			Attributed(Attributed&& rhs);
			virtual ~Attributed();

			Attributed& operator=(const Attributed& rhs);
			Attributed& operator=(Attributed&& rhs);

			bool IsPrescribedAttribute(const std::string& name) const;
			bool IsAuxiliaryAttribute(const std::string& name) const;
			bool IsAttribute(const std::string& name) const;

			template <typename T>
			Datum* AddPrescribedAttributeInternal(const std::string& name, const T& data);
			template <typename T>
			Datum* AddPrescribedAttributeInternal(const std::string& name, const T* data, const std::uint32_t size);

			template <typename T>
			Datum* AddPrescribedAttributeExternal(const std::string& name, const T& data);
			template <typename T>
			Datum* AddPrescribedAttributeExternal(const std::string& name, const T* data, const std::uint32_t size);

			Scope* AddNestedScope(const std::string& name);
			void AddNestedScope(const std::string& name, Scope* scope);
			
			Datum& AppendAuxiliaryAttribute(const std::string& name);

		private:

			static HashMap<std::uint64_t, HashMap<std::string, Datum>> s_mPrescribedAttributes;
			HashMap<std::string, Datum> mAuxiliaryAttributes;

			static std::int32_t s_mInstanceCount;
		};

#include "Attributed.inl"

	}
}