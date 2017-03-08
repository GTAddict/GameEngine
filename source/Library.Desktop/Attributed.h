#pragma once
#include "Scope.h"

namespace GameEngine
{
	namespace Library
	{
		class Attributed : public Scope
		{
			RTTI_DECLARATIONS(Attributed, Scope);

		public:
			typedef RTTI* RTTIPointer;

		public:

			Attributed();

			bool IsPrescribedAttribute(const std::string& name) const;
			bool IsAuxiliaryAttribute(const std::string& name) const;
			bool IsAttribute(const std::string& name) const;

			std::uint32_t AuxiliaryBegin() const;

		protected:

			template <typename T>
			Datum* AddPrescribedAttributeInternal(const std::string& name, const T& data);
			template <typename T>
			Datum* AddPrescribedAttributeInternal(const std::string& name, const T* data, const std::uint32_t size);
			// Datum* AddPrescribedRTTIInternal(const std::string& name, const RTTIPointer data);
			// Datum* AddPrescribedRTTIbuteInternal(const std::string& name, const RTTIPointer* data, const std::uint32_t size);

			template <typename T>
			Datum* AddPrescribedAttributeExternal(const std::string& name, const T& data);
			template <typename T>
			Datum* AddPrescribedAttributeExternal(const std::string& name, const T* data, const std::uint32_t size);
			// Datum* AddPrescribedAttributeExternal(const std::string& name, const RTTIPointer data);
			// Datum* AddPrescribedAttributeExternal(const std::string& name, const RTTIPointer* data, const std::uint32_t size);
			
			Datum& AppendAuxiliaryAttribute(const std::string& name);

			static HashMap<std::uint64_t, HashMap<std::string, Datum>> mPrescribedAttributes;
			HashMap<std::string, Datum> mAuxiliaryAttributes;
		};
	}
}

class Example : GameEngine::Library::Attributed
{
	RTTI_DECLARATIONS(Example, Attributed);

	std::int32_t foo;
	std::int32_t more[2];

	Example()
	{
		// AddPrescribedAttributeExternal("Foo", foo);
		// AddPrescribedAttributeExternal("More", more, 2);
	}
};

class Another : GameEngine::Library::Attributed
{
	RTTI_DECLARATIONS(Another, Attributed);

	std::int32_t bar;

	Example* ex;

	Another()
	{
		// AddPrescribedAttributeExternal("Bar", &bar, 1);
		AddPrescribedAttributeExternal("ex", ex);
	}
};

RTTI_DEFINITIONS(Example);