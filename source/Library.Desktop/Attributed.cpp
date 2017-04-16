#include "pch.h"
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(Attributed);

		std::uint32_t Attributed::mInstanceCount = 0;

		HashMap<std::uint64_t, HashMap<std::string, Datum>> Attributed::s_mPrescribedAttributes;

		Attributed::Attributed()
		{
			++mInstanceCount;
			Populate();
		}

		Attributed::~Attributed()
		{
			if (--mInstanceCount == 0)
			{
				s_mPrescribedAttributes.Clear();
			}
		}

		Attributed::Attributed(const Attributed& rhs)
		{
			++mInstanceCount;
			operator=(rhs);
		}

		Attributed::Attributed(Attributed&& rhs)
		{
			++mInstanceCount;
			operator=(std::move(rhs));
		}

		Attributed& Attributed::operator=(const Attributed& rhs)
		{
			Scope::operator=(rhs);

			if (this != &rhs)
			{
				operator[]("this") = PRTTI_CAST(this);
			}

			return *this;
		}

		Attributed& Attributed::operator=(Attributed&& rhs)
		{
			Scope::operator=(std::move(rhs));

			if (this != &rhs)
			{
				operator[]("this") = PRTTI_CAST(this);
			}
			
			return *this;
		}

		Datum* Attributed::AddPrescribedAttributeInternalWithType(const std::string& name, const Datum::DatumType type)
		{
			Datum& datum = Append(name);
			datum.SetType(type);
			s_mPrescribedAttributes[TypeIdInstance()][name] = datum;
			
			return &datum;
		}

		Scope* Attributed::AddNestedScope(const std::string& name)
		{
			Scope& scope = AppendScope(name);
			s_mPrescribedAttributes[TypeIdInstance()][name] = &scope;
			return &scope;
		}

		// If we are checking for nullptr, then accept a Scope& instead of a *
		// one would say, but I wanted the syntax to be uniform across all
		// signatures. So instead of the user dereferencing his scope pointer
		// in the class he can just pass it in.
		void Attributed::AddNestedScope(const std::string& name, Scope* scope)
		{
			if (scope == nullptr)
			{
				return;
			}

			s_mPrescribedAttributes[TypeIdInstance()][name] = scope;
			Adopt(*scope, name);
		}

		Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
		{
			if (IsAttribute(name))
			{
				throw std::invalid_argument("An attribute with the given name already exists.");
			}

			return Append(name);
		}

		std::uint32_t Attributed::GetPrescribedAttributeCount() const
		{
			auto foundIt = s_mPrescribedAttributes.Find(TypeIdInstance());
			return foundIt == s_mPrescribedAttributes.end() ? 0 : foundIt->second.Size();
		}

		void Attributed::Populate()
		{
			AddPrescribedAttributeInternal("this", PRTTI_CAST(this));
		}

		bool Attributed::IsPrescribedAttribute(const std::string& name) const
		{
			return IsAttribute(name) && s_mPrescribedAttributes[TypeIdInstance()].ContainsKey(name);
		}

		bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
		{
			return IsAttribute(name) && !IsPrescribedAttribute(name);
		}

		bool Attributed::IsAttribute(const std::string& name) const
		{
			return Find(name) != nullptr;
		}
	}
}
