#include "pch.h"
#include "Datum.h"

namespace GameEngine
{
	namespace Library
	{
		Datum::Datum()
			: mData{ nullptr }
			, mType(DatumType::Unknown)
			, mSize(0)
			, mCapacity(0)
		{
		}

		Datum::Datum(const Datum& rhs)
			: Datum()
		{
			operator=(rhs);
		}

		Datum::Datum(Datum&& rhs)
			: mData(rhs.mData)
			, mType(rhs.mType)
			, mSize(rhs.mSize)
			, mCapacity(rhs.mCapacity)
		{
			rhs.mData = { nullptr };
			rhs.mType = DatumType::Unknown;
			rhs.mSize = 0;
			rhs.mCapacity = 0;
		}

		Datum::~Datum()
		{
			Clear();
		}

		Datum& Datum::operator=(const Datum& rhs)
		{
			if (this != &rhs)
			{
				Clear();
				mType = rhs.mType;
				Reserve(rhs.mCapacity);
				SetSize(rhs.mSize);

				switch (mType)
				{
				case DatumType::Float:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<float>			(i));	}	break;
				case DatumType::Integer:	for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<std::int32_t>	(i));	}	break;
				case DatumType::Matrix:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<glm::mat4x4>	(i));	}	break;
				case DatumType::Pointer:	for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<RTTIPointer>	(i));	}	break;
				case DatumType::String:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<std::string>	(i));	}	break;
				case DatumType::Vector:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<glm::vec4>		(i));	}	break;
				case DatumType::Table:		throw new std::domain_error("Unimplemented.");
				default:					throw new std::domain_error("Unimplemented.");
				}
			}

			return *this;
		}

		Datum& Datum::operator=(Datum&& rhs)
		{
			mData			= rhs.mData;
			mType			= rhs.mType;
			mSize			= rhs.mSize;
			mCapacity		= rhs.mCapacity;

			rhs.mData		= { nullptr };
			rhs.mType		= DatumType::Unknown;
			rhs.mSize		= 0;
			rhs.mCapacity	= 0;

			return *this;
		}

		bool Datum::operator==(const Datum& rhs) const
		{
			if (mType == rhs.mType && mSize == rhs.mSize && mCapacity == rhs.mCapacity)
			{
				switch (mType)
				{
				case DatumType::Float:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<float>			(i) != rhs.Get<float>			(i)) { return false; } }	break;
				case DatumType::Integer:	for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<std::int32_t>	(i) != rhs.Get<std::int32_t>	(i)) { return false; } }	break;
				case DatumType::Matrix:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<glm::mat4x4>	(i) != rhs.Get<glm::mat4x4>		(i)) { return false; } }	break;
				case DatumType::Pointer:	for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<RTTIPointer>	(i) != rhs.Get<RTTIPointer>		(i)) { return false; } }	break;
				case DatumType::String:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<std::string>	(i) != rhs.Get<std::string>		(i)) { return false; } }	break;
				case DatumType::Vector:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<glm::vec4>		(i) != rhs.Get<glm::vec4>		(i)) { return false; } }	break;
				case DatumType::Table:		throw new std::domain_error("Unimplemented.");
				default:					throw new std::domain_error("Unimplemented.");
				}
				
				return true;
			}

			return false;
		}

		bool Datum::operator!=(const Datum& rhs) const
		{
			return !(*this == rhs);
		}

		const Datum::DatumType& Datum::Type() const
		{
			return mType;
		}

		void Datum::SetType(const DatumType& type)
		{
			if (mType != DatumType::Unknown)
			{
				throw std::domain_error("You cannot change the type of data once it is set!");
			}

			mType = type;
		}

		std::uint32_t Datum::Size() const
		{
			return mSize;
		}

		void Datum::SetSize(const std::uint32_t size)
		{
			switch (mType)
			{
			case DatumType::Float:		SetSize_Imp<float>(size);		break;
			case DatumType::Integer:	SetSize_Imp<std::int32_t>(size);		break;
			case DatumType::Matrix:		SetSize_Imp<glm::mat4x4>(size);		break;
			case DatumType::Pointer:	SetSize_Imp<RTTIPointer>(size);		break;
			case DatumType::String:		SetSize_Imp<std::string>(size);		break;
			case DatumType::Vector:		SetSize_Imp<glm::vec4>(size);		break;
			case DatumType::Table:		throw new std::domain_error("Unimplemented.");
			default:					throw new std::domain_error("Unimplemented.");
			}
		}

		void Datum::Clear()
		{
			switch (mType)
			{
			case DatumType::Integer:	Clear_Imp<int>();			break;
			case DatumType::Float:		Clear_Imp<float>();			break;
			case DatumType::Vector:		Clear_Imp<glm::vec4>();		break;
			case DatumType::Matrix:		Clear_Imp<glm::mat4x4>();	break;
			case DatumType::String:		Clear_Imp<std::string>();	break;
			case DatumType::Pointer:	Clear_Imp<RTTIPointer>();			break;
			case DatumType::Table:		throw new std::domain_error("Unimplemented.");
			default:					throw new std::domain_error("Unimplemented.");
			}
		}

		void Datum::SetFromString(std::string& inputString, const std::uint32_t index)
		{
			// Data format:
			// Type Value
			// Examples:
			// Integer 21
			// Float 6.5

			if (mType == DatumType::Unknown)
			{
				throw std::domain_error("Datum type needs to be set.");
			}

			char dataType[11];
			sscanf_s(inputString.c_str(), "%s", dataType, sizeof(dataType));

			std::string dataTypeString(dataType);

			if (dataTypeString == "Integer")
			{
				if (mType != DatumType::Integer)
				{
					throw std::invalid_argument("Trying to assign Integer to Datum of different type.");
				}

				std::int32_t data;
				sscanf_s(inputString.c_str(), "%*s %d", &data);

				Set(data, index);
			}
			else if (dataTypeString == "Float")
			{
				if (mType != DatumType::Float)
				{
					throw std::invalid_argument("Trying to assign Float to Datum of different type.");
				}

				float data;
				sscanf_s(inputString.c_str(), "%*s %f", &data);

				Set(data, index);
			}
			else if (dataTypeString == "Vector")
			{
				if (mType != DatumType::Vector)
				{
					throw std::invalid_argument("Trying to assign Vector to Datum of different type.");
				}

				throw std::domain_error("Unimplemented");
			}
			else if (dataTypeString == "Matrix")
			{
				if (mType != DatumType::Matrix)
				{
					throw std::invalid_argument("Trying to assign Matrix to Datum of different type.");
				}

				throw std::domain_error("Unimplmented");
			}
			else if (dataTypeString == "String")
			{
				if (mType != DatumType::String)
				{
					throw std::invalid_argument("Trying to assign String to Datum of different type.");
				}

				char data[255];
				sscanf_s(inputString.c_str(), "%*s %s", &data, sizeof(data));

				Set(std::string(data), index);
			}
			else if (dataTypeString == "Pointer")
			{
				if (mType != DatumType::Pointer)
				{
					throw std::invalid_argument("Trying to assign Pointer to Datum of different type.");
				}

				throw std::domain_error("Unimplemented.");
			}
		}

		void Datum::Reserve(const std::uint32_t capacity)
		{
			switch (mType)
			{
			case DatumType::Integer:	Reserve_Imp<int>(capacity);		break;
			case DatumType::Float:		Reserve_Imp<float>(capacity);		break;
			case DatumType::Vector:		Reserve_Imp<glm::vec4>(capacity);		break;
			case DatumType::Matrix:		Reserve_Imp<glm::mat4x4>(capacity);		break;
			case DatumType::String:		Reserve_Imp<std::string>(capacity);		break;
			case DatumType::Pointer:	Reserve_Imp<RTTIPointer>(capacity);		break;
			case DatumType::Table:		throw new std::domain_error("Unimplemented.");
			default:					throw new std::domain_error("Unimplemented.");
			}

		}

		template<typename T>
		void Datum::Clear_Imp()
		{
			T* begin = GetDataPointer<T>();

			for (std::uint32_t i = 0; i < Size(); ++i)
			{
				(begin + i)->~T();
			}

			free(begin);
			mSize = 0;
			mCapacity = 0;
			mData = { nullptr };
		}

		template<typename T>
		void Datum::SetSize_Imp(const std::uint32_t size)
		{
			if (mType == DatumType::Unknown)
			{
				throw std::domain_error("Type has not been set yet, do not know how much size to allocate.");
			}

			if (size > mCapacity)
			{
				Reserve(size);
			}

			while (mSize < size)
			{
				T* currentElement = GetDataPointer<T>() + mSize;
				currentElement = new (currentElement) T();
				++mSize;
			}

			while (mSize > size)
			{
				T* currentElement = GetDataPointer<T>() + mSize;
				currentElement->~T();
				--mSize;
				currentElement;		// Destructor cannot be invoke on built-in types
									// so "local variable not referenced warning pops up
			}
		}

		template<typename T>
		void Library::Datum::Reserve_Imp(const std::uint32_t capacity)
		{
			T* dataPointer = GetDataPointer<T>();
			dataPointer = static_cast<T*>(realloc(dataPointer, sizeof(T) * capacity));
			SetDataPointer(dataPointer);
			mCapacity = capacity;
		}
	}
}