#include "pch.h"
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(Attributed);

		HashMap<std::uint64_t, HashMap<std::string, Datum>> Attributed::s_mPrescribedAttributes;
		std::int32_t Attributed::s_mInstanceCount = 0;

		Attributed::Attributed()
		{
			++s_mInstanceCount;
			AddPrescribedAttributeInternal("this", PRTTI_CAST(this));
		}

		Attributed::Attributed(const Attributed& rhs)
		{
			operator=(rhs);
		}

		Attributed::Attributed(Attributed&& rhs)
		{
			operator=(std::move(rhs));
		}

		Attributed& Attributed::operator=(const Attributed& rhs)
		{
			Scope::operator=(rhs);

			if (this != &rhs)
			{
				mAuxiliaryAttributes = rhs.mAuxiliaryAttributes;
				operator[]("this") = PRTTI_CAST(this);
			}

			return *this;
		}

		Attributed& Attributed::operator=(Attributed&& rhs)
		{
			Scope::operator=(std::move(rhs));

			if (this != &rhs)
			{
				mAuxiliaryAttributes = std::move(rhs.mAuxiliaryAttributes);
				operator[]("this") = PRTTI_CAST(this);
			}
			
			return *this;
		}

		Attributed::~Attributed()
		{
			--s_mInstanceCount;

			if (s_mInstanceCount == 0)
			{
				s_mPrescribedAttributes.Clear();
			}

			mAuxiliaryAttributes.Clear();
		}

		Scope* Attributed::AddNestedScope(const std::string& name)
		{
			// Already added, return
			if (IsAttribute(name))
			{
				return nullptr;
			}

			Scope& scope = AppendScope(name);
			s_mPrescribedAttributes[TypeIdClass()][name] = &scope;

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

			if (!IsAttribute(name))
			{
				s_mPrescribedAttributes[TypeIdClass()][name] = scope;
			}

			Adopt(*scope, name);
		}

		Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
		{
			if (IsAttribute(name))
			{
				throw std::invalid_argument("An attribute with the given name already exists.");
			}

			Datum& d = Append(name); d;

			mAuxiliaryAttributes[name] = d;

			return Append(name);
		}

		bool Attributed::IsPrescribedAttribute(const std::string& name) const
		{
			return s_mPrescribedAttributes[TypeIdClass()].ContainsKey(name);
		}

		bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
		{
			return mAuxiliaryAttributes.ContainsKey(name);
		}

		bool Attributed::IsAttribute(const std::string& name) const
		{
			return IsPrescribedAttribute(name) || IsAuxiliaryAttribute(name);
		}
	}
}
