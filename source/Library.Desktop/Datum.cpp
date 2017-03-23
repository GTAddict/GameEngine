#include "pch.h"
#include "Datum.h"

namespace GameEngine
{
	namespace Library
	{
		Datum::Datum()
			: mData { nullptr }
			, mType(DatumType::Unknown)
			, mSize(0)
			, mCapacity(0)
			, mExternalStorage(false)
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
			, mExternalStorage(rhs.mExternalStorage)
		{
			rhs.mData = { nullptr };
			rhs.mType = DatumType::Unknown;
			rhs.mSize = 0;
			rhs.mCapacity = 0;
			rhs.mExternalStorage = false;
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
				mExternalStorage = rhs.mExternalStorage;

				if (mExternalStorage)
				{
					mSize		= rhs.mSize;
					mCapacity	= rhs.mCapacity;
					mData		= rhs.mData;
				}
				else if (mType != DatumType::Unknown)
				{
					Reserve(rhs.mCapacity);
					SetSize(rhs.mSize);

					switch (mType)
					{
					case DatumType::Float:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<float>			(i)); }	break;
					case DatumType::Integer:	for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<std::int32_t>	(i)); }	break;
					case DatumType::Matrix:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<glm::mat4x4>	(i)); }	break;
					case DatumType::Pointer:	for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<RTTIPointer>	(i)); }	break;
					case DatumType::String:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<std::string>	(i)); }	break;
					case DatumType::Vector:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<glm::vec4>		(i)); }	break;
					case DatumType::Table:		for (std::uint32_t i = 0; i < Size(); ++i) { Set(rhs.Get<ScopePointer>	(i)); }	break;
					default:					throw std::domain_error("Unimplemented.");
					}
				}
			}

			return *this;
		}

		Datum& Datum::operator=(Datum&& rhs)
		{
			if (this != &rhs)
			{
				mData					= rhs.mData;
				mType					= rhs.mType;
				mSize					= rhs.mSize;
				mCapacity				= rhs.mCapacity;
				mExternalStorage		= rhs.mExternalStorage;

				rhs.mData				= { nullptr };
				rhs.mType				= DatumType::Unknown;
				rhs.mSize				= 0;
				rhs.mCapacity			= 0;
				rhs.mExternalStorage	= false;
			}

			return *this;
		}

		bool Datum::operator==(const Datum& rhs) const
		{
			// It doesn't really matter which entries in mData we
			// compare, as they'll all point to the same value
			if (mExternalStorage && rhs.mExternalStorage && mData.pInt == rhs.mData.pInt)
			{
				return true;
			}
			else if (mType == rhs.mType && mSize == rhs.mSize)
			{
				switch (mType)
				{
				case DatumType::Float:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<float>			(i) != rhs.Get<float>				(i))	{ return false; } }	break;
				case DatumType::Integer:	for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<std::int32_t>	(i) != rhs.Get<std::int32_t>		(i))	{ return false; } }	break;
				case DatumType::Matrix:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<glm::mat4x4>	(i) != rhs.Get<glm::mat4x4>			(i))	{ return false; } }	break;
				case DatumType::Pointer:	for (std::uint32_t i = 0; i < Size(); ++i) { if (!Get<RTTIPointer>	(i)->Equals(rhs.Get<RTTIPointer>	(i)))	{ return false; } }	break;
				case DatumType::String:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<std::string>	(i) != rhs.Get<std::string>			(i))	{ return false; } }	break;
				case DatumType::Vector:		for (std::uint32_t i = 0; i < Size(); ++i) { if (Get<glm::vec4>		(i) != rhs.Get<glm::vec4>			(i))	{ return false; } }	break;
				case DatumType::Table:		for (std::uint32_t i = 0; i < Size(); ++i) { if (!Get<RTTIPointer>	(i)->Equals(rhs.Get<RTTIPointer>	(i)))	{ return false; } }	break;
				case DatumType::Unknown:	break; // Don't check data. Don't return false either, as uninitialized are equal.
				default:					throw std::domain_error("Unimplemented.");
				}
				
				return true;
			}

			return false;
		}

		bool Datum::operator!=(const Datum& rhs) const
		{
			return !(*this == rhs);
		}

		Scope& Datum::operator[](const std::uint32_t index)
		{
			return *Get<ScopePointer>(index);
		}

		template<typename T>
		inline T* GameEngine::Library::Datum::GetDataPointer() const
		{
			static_assert(false, "You need to provide implementation for your class.");
			return nullptr;
		}

		template <>
		inline std::int32_t* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::Integer)
			{
				throw std::invalid_argument("Trying to access data as integer when data is not an integer!");
			}

			return mData.pInt;
		}

		template <>
		inline float* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::Float)
			{
				throw std::invalid_argument("Trying to access data as float when data is not a float!");
			}

			return mData.pFloat;
		}

		template <>
		inline glm::vec4* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::Vector)
			{
				throw std::invalid_argument("Trying to access data as vector when data is not a vector!");
			}

			return mData.pVec4;
		}

		template <>
		inline glm::mat4x4* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::Matrix)
			{
				throw std::invalid_argument("Trying to access data as matrix when data is not a matrix!");
			}

			return mData.pMat4;
		}

		template <>
		inline std::string* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::String)
			{
				throw std::invalid_argument("Trying to access data as string when data is not a string!");
			}

			return mData.pString;
		}

		template <>
		inline GameEngine::Library::Datum::RTTIPointer* GameEngine::Library::Datum::GetDataPointer() const
		{
			// You are allowed to access a Table as an RTTIPointer
			if (mType != DatumType::Pointer && mType != DatumType::Table)
			{
				throw std::invalid_argument("Trying to access data as RTTI pointer when data is not an RTTI pointer!");
			}

			return mData.ppRTTI;
		}

		template <>
		inline GameEngine::Library::Datum::ScopePointer* GameEngine::Library::Datum::GetDataPointer() const
		{
			if (mType != DatumType::Table)
			{
				throw std::invalid_argument("Trying to access data as Scope pointer when data is not a Scope pointer!");
			}

			return mData.ppScope;
		}

		template<typename T>
		inline void GameEngine::Library::Datum::SetDataPointer(T* dataPointer)
		{
			static_assert(false, "You need to provide implementation for your class.");
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(std::int32_t* dataPointer)
		{
			mType = DatumType::Integer;
			mData.pInt = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(float* dataPointer)
		{
			mType = DatumType::Float;
			mData.pFloat = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(glm::vec4* dataPointer)
		{
			mType = DatumType::Vector;
			mData.pVec4 = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(glm::mat4x4* dataPointer)
		{
			mType = DatumType::Matrix;
			mData.pMat4 = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(std::string* dataPointer)
		{
			mType = DatumType::String;
			mData.pString = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(ScopePointer* dataPointer)
		{
			mType = DatumType::Table;
			mData.ppScope = dataPointer;
		}

		template <>
		inline void GameEngine::Library::Datum::SetDataPointer(RTTIPointer* dataPointer)
		{
			mType = DatumType::Pointer;
			mData.ppRTTI = dataPointer;
		}

		const Datum::DatumType& Datum::Type() const
		{
			return mType;
		}

		void Datum::SetType(const DatumType& type)
		{
			if (mType == type)
			{
				return;
			}

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
			if (mExternalStorage)
			{
				throw std::domain_error("You cannot resize external storage.");
			}

			if (mType == DatumType::Unknown)
			{
				throw std::domain_error("Type has not been set yet, do not know how much size to allocate.");
			}

			switch (mType)
			{
			case DatumType::Float:		SetSize_Imp<float>			(size);		break;
			case DatumType::Integer:	SetSize_Imp<std::int32_t>	(size);		break;
			case DatumType::Matrix:		SetSize_Imp<glm::mat4x4>	(size);		break;
			case DatumType::Pointer:	SetSize_Imp<RTTIPointer>	(size);		break;
			case DatumType::String:		SetSize_Imp<std::string>	(size);		break;
			case DatumType::Vector:		SetSize_Imp<glm::vec4>		(size);		break;
			case DatumType::Table:		SetSize_Imp<ScopePointer>	(size);		break;
			default:					throw std::domain_error		("Unimplemented.");
			}
		}

		void Datum::Clear()
		{
			if (mExternalStorage)
			{
				return;
			}

			switch (mType)
			{
			case DatumType::Integer:	Clear_Imp<int>();			break;
			case DatumType::Float:		Clear_Imp<float>();			break;
			case DatumType::Vector:		Clear_Imp<glm::vec4>();		break;
			case DatumType::Matrix:		Clear_Imp<glm::mat4x4>();	break;
			case DatumType::String:		Clear_Imp<std::string>();	break;
			case DatumType::Pointer:	Clear_Imp<RTTIPointer>();	break;
			case DatumType::Table:		Clear_Imp<ScopePointer>();	break;
			default:												break;
			}
		}

		void Datum::SetFromString(const std::string& inputString, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				throw std::domain_error("Datum type needs to be set.");
			}
			if (inputString.empty())
			{
				throw std::invalid_argument("Input string is empty.");
			}

			switch (mType)
			{
				case DatumType::Integer:	Set(stoi(inputString), index);	break;
				case DatumType::Float:		Set(stof(inputString), index);	break;
				case DatumType::Vector:
				{
					glm::vec4 data;
					sscanf_s(inputString.c_str(), "vec4(%f, %f, %f, %f)", &data[0], &data[1], &data[2], &data[3]);
					Set(data, index);
					break;
				}
				case DatumType::Matrix:
				{
					glm::mat4x4 data;
					sscanf_s(inputString.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))"
						, &data[0][0], &data[0][1], &data[0][2], &data[0][3]
						, &data[1][0], &data[1][1], &data[1][2], &data[1][3]
						, &data[2][0], &data[2][1], &data[2][2], &data[2][3]
						, &data[3][0], &data[3][1], &data[3][2], &data[3][3]);
					Set(data, index);
					break;
				}
				case DatumType::String:		Set(inputString, index);	break;
				default:
					throw std::invalid_argument("Unknown datatype, parse error, or invalid assignment to datum of different type.");
			}
		}

		void Datum::Reserve(const std::uint32_t capacity)
		{
			if (mExternalStorage)
			{
				throw std::domain_error("You cannot reserve external storage.");
			}

			switch (mType)
			{
			case DatumType::Integer:	Reserve_Imp<int>			(capacity);		break;
			case DatumType::Float:		Reserve_Imp<float>			(capacity);		break;
			case DatumType::Vector:		Reserve_Imp<glm::vec4>		(capacity);		break;
			case DatumType::Matrix:		Reserve_Imp<glm::mat4x4>	(capacity);		break;
			case DatumType::String:		Reserve_Imp<std::string>	(capacity);		break;
			case DatumType::Pointer:	Reserve_Imp<RTTIPointer>	(capacity);		break;
			case DatumType::Table:		Reserve_Imp<ScopePointer>	(capacity);		break;
			default:					throw std::domain_error		("Unimplemented.");
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
			if (size > mCapacity)
			{
				Reserve(size);
			}

			while (mSize < size)
			{
				T* currentElement = GetDataPointer<T>() + mSize;
				new (currentElement) T();
				++mSize;
			}

			while (mSize > size)
			{
				T* currentElement = GetDataPointer<T>() + mSize - 1;
				currentElement->~T();
				--mSize;
				ENGINE_UNUSED(currentElement);		// Destructor cannot be invoke on built-in types
													// so "local variable not referenced" warning pops up
			}
		}

		template<typename T>
		void Library::Datum::Reserve_Imp(const std::uint32_t capacity)
		{
			if (capacity > 0)
			{
				T* dataPointer = GetDataPointer<T>();
				dataPointer = static_cast<T*>(realloc(dataPointer, sizeof(T) * capacity));
				SetDataPointer(dataPointer);
				mCapacity = capacity;
			}
		}
	}
}