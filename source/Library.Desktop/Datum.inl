#pragma once
#include "Datum.h"
#include "Macros.h"

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

template <typename T>
GameEngine::Library::Datum& GameEngine::Library::Datum::operator=(const T& rhs)
{
	Set(rhs);
	return *this;
}

template<typename T>
inline void GameEngine::Library::Datum::SetStorage(const T* dataBlock, const std::uint32_t size)
{
	Clear();
	SetDataPointer<T>(const_cast<T*>(dataBlock));
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
	return std::to_string(Get<float>(index));
}

template <>
inline std::string GameEngine::Library::Datum::ToString<std::int32_t>(const std::uint32_t index) const
{
	return std::to_string(Get<std::int32_t>(index));
}

template <>
inline std::string GameEngine::Library::Datum::ToString<glm::mat4x4>(const std::uint32_t index) const
{
	return glm::to_string(Get<glm::mat4x4>(index));
}

template <>
inline std::string GameEngine::Library::Datum::ToString<glm::vec4>(const std::uint32_t index) const
{
	return glm::to_string(Get<glm::vec4>(index));
}

template <>
inline std::string GameEngine::Library::Datum::ToString<std::string>(const std::uint32_t index) const
{
	return Get<std::string>(index);
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
	ENGINE_UNUSED(data);
	return DatumType::Unknown;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const std::int32_t& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Integer;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const float& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Float;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const glm::vec4& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Vector;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const glm::mat4x4& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Matrix;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const std::string& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::String;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const ScopePointer& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Table;
}

template <>
inline GameEngine::Library::Datum::DatumType GameEngine::Library::Datum::DeduceType(const RTTIPointer& data) const
{
	ENGINE_UNUSED(data);
	return DatumType::Pointer;
}