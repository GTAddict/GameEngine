#include "pch.h"
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		RTTI_DEFINITIONS(Attributed);

		Attributed::Attributed()
		{
			RTTIPointer thisPointer = static_cast<RTTIPointer>(this);
			AddPrescribedAttributeInternal("this", &thisPointer, 1);
		}

		template <typename T>
		Datum* Attributed::AddPrescribedAttributeInternal(const std::string& name, const T& data)
		{
			AddPrescribedAttributeInternal(name, &data, 1);
		}

		template <typename T>
		Datum* Attributed::AddPrescribedAttributeInternal(const std::string& name, const T* data, const std::uint32_t size)
		{
			// Already added, return
			if (IsAttribute(name))
			{
				return nullptr;
			}

			if (data == nullptr)
			{
				throw std::runtime_error("Data is null.");
			}

			Datum& datum = Append(name);
			datum.SetSize(size);
			
			for (std::uint32_t i = 0; i < size; ++i)
			{
				datum.Set(*(data + i), i);
			}

			mPrescribedAttributes[TypeIdClass()][name] = datum;

			return &datum;
		}

		/*Datum* Attributed::AddPrescribedRTTIInternal(const std::string& name, const RTTIPointer data)
		{
			return AddPrescribedAttributeInternal(name, &data, 1);
		}

		Datum* Attributed::AddPrescribedRTTIInternal(const std::string& name, const RTTIPointer* data, const std::uint32_t size)
		{
			if (data == nullptr)
			{
				throw std::runtime_error("Data is null.");
			}

			if (data[0]->Is(RTTI::TypeIdClass()))
			{

			}
		}*/

		template <typename T>
		Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const T& data)
		{
			return AddPrescribedAttributeExternal(name, &data, 1);
		}

		template <typename T>
		Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const T* data, const std::uint32_t size)
		{
			// Already added, return
			if (IsAttribute(name))
			{
				return nullptr;
			}

			if (data == nullptr)
			{
				throw std::runtime_error("Data is null.");
			}

			Datum& datum = Append(name);
			datum.SetStorage(data, size);

			mPrescribedAttributes[TypeIdClass()][name] = datum;

			return &datum;
		}

		//Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const RTTIPointer data)
		//{
		//	return AddPrescribedAttributeExternal(name, &data, 1);
		//}

		//Datum* Attributed::AddPrescribedAttributeExternal(const std::string& name, const RTTIPointer* data, const std::uint32_t size)
		//{
		//	// Already added, return
		//	if (IsAttribute(name))
		//	{
		//		return nullptr;
		//	}

		//	if (data == nullptr)
		//	{
		//		throw std::runtime_error("Data is null.");
		//	}

		//	Datum& datum = Append(name);
		//	datum.SetStorage(data, size);

		//	mPrescribedAttributes[TypeIdClass()][name] = datum;

		//	return &datum;
		//}

		Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
		{
			if (IsAttribute(name))
			{
				throw std::invalid_argument("An attribute with the given name already exists.");
			}

			Datum& d = Append(name);

			mAuxiliaryAttributes[name] = d;

			return Append(name);
		}

		bool Attributed::IsPrescribedAttribute(const std::string& name) const
		{
			return mPrescribedAttributes[TypeIdClass()].ContainsKey(name);
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
