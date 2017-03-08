#include "Datum.h"
#pragma once

template<typename T>
inline bool GameEngine::Library::Datum::operator==(const T& rhs) const
{
	return (Size() == 1 && Get<T>(0) == rhs);
}

template<typename T>
inline bool GameEngine::Library::Datum::operator!=(const T& rhs) const
{
	return !(*this == rhs);
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
	if (mType != DatumType::Pointer)
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
	mData.pInt = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(float* dataPointer)
{
	mData.pFloat = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(glm::vec4* dataPointer)
{
	mData.pVec4 = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(glm::mat4x4* dataPointer)
{
	mData.pMat4 = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(std::string* dataPointer)
{
	mData.pString = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(ScopePointer* dataPointer)
{
	mData.ppScope = dataPointer;
}

template <>
inline void GameEngine::Library::Datum::SetDataPointer(RTTIPointer* dataPointer)
{
	mData.ppRTTI = dataPointer;
}

template <typename T>
GameEngine::Library::Datum& GameEngine::Library::Datum::operator=(const T& rhs)
{
	Set(rhs);
	return *this;
}

template<typename T>
inline void GameEngine::Library::Datum::SetStorage(T* dataBlock, const std::uint32_t size)
{
	Clear();
	SetDataPointer<T>(dataBlock);
	mSize = size;
	mExternalStorage = true;
}

template<typename T>
inline void GameEngine::Library::Datum::PushBack(const T& value)
{
	Set<T>(value, Size());
}

template<typename T>
inline bool GameEngine::Library::Datum::Remove(const T& value)
{
	T* dataStart = GetDataPointer<T>();

	for (std::uint32_t i = 0; i < Size(); ++i)
	{
		T& data = *(dataStart + i);
		if (data == value)
		{
			(dataStart + i)->~T();
			if (i + 1 != Size())
			{
				memmove(dataStart + i, dataStart + i + 1, (Size() - i + 1) * sizeof(T));
			}
			--mSize;

			return true;
		}
	}

	return false;
}

template<typename T>
inline void GameEngine::Library::Datum::SetType(const T& data)
{
	mType = DeduceType(data);
}

template <typename T>
inline void GameEngine::Library::Datum::Set(const T& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DeduceType(value);
	}
	else if (mType != DeduceType(value))
	{
		throw std::invalid_argument("Trying to assign value to Datum of different type.");
	}
	
	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<T>() + index) = value;
}

template<typename T>
inline T& GameEngine::Library::Datum::Get(const std::uint32_t index) const
{
	if (index >= Size())
	{
		throw std::out_of_range("Out of bounds.");
	}

	return *(GetDataPointer<T>() + index);
}

template <typename T>
inline std::string GameEngine::Library::Datum::ToString(const std::uint32_t index) const
{
	static_assert("Provide implementation for your class.");
}

template <>
inline std::string GameEngine::Library::Datum::ToString<float>(const std::uint32_t index) const
{
	std::stringstream s;
	s << "Float " << Get<float>(index);
	return s.str();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<std::int32_t>(const std::uint32_t index) const
{
	std::stringstream s;
	s << "Integer " << Get<std::int32_t>(index);
	return s.str();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<glm::mat4x4>(const std::uint32_t index) const
{
	std::stringstream s;
	s << "Matrix";
	glm::mat4x4& matrix = Get<glm::mat4x4>(index);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			s << " " << matrix[i][j];
		}
	}

	return s.str();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<glm::vec4>(const std::uint32_t index) const
{
	std::stringstream s;
	s << "Vector";
	glm::vec4& vector = Get<glm::vec4>(index);

	for (int i = 0; i < 4; ++i)
	{
		s << " " << vector[i];
	}

	return s.str();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<std::string>(const std::uint32_t index) const
{
	std::stringstream s;
	s << "String " << Get<std::string>(index);
	return s.str();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<GameEngine::Library::Datum::RTTIPointer>(const std::uint32_t index) const
{
	return Get<GameEngine::Library::Datum::RTTIPointer>(index)->ToString();
}

template <>
inline std::string GameEngine::Library::Datum::ToString<GameEngine::Library::Datum::ScopePointer>(const std::uint32_t index) const
{
	return ToString<RTTIPointer>(index);
}

template <typename T>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const T& data) const
{
	data;
	return DatumType::Unknown;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const std::int32_t& data) const
{
	data;
	return DatumType::Integer;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const float& data) const
{
	data;
	return DatumType::Float;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const glm::vec4& data) const
{
	data;
	return DatumType::Vector;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const glm::mat4x4& data) const
{
	data;
	return DatumType::Matrix;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const std::string& data) const
{
	data;
	return DatumType::String;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const ScopePointer& data) const
{
	data;
	return DatumType::Table;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const RTTIPointer& data) const
{
	data;
	return DatumType::Pointer;
}