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

template<typename T>
inline void GameEngine::Library::Datum::SetDataPointer(T* dataPointer)
{
	static_assert(false, "You need to provide implementation for your class.");
	return nullptr;
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

template <typename T>
inline void GameEngine::Library::Datum::Set(const T& value, const std::uint32_t index)
{
	static_assert(false, "Not implemented.");
}

template <>
inline void GameEngine::Library::Datum::Set(const std::int32_t& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Integer;
	}
	else if (mType != DatumType::Integer)
	{
		throw std::invalid_argument("Trying to assign std::int32_t to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<std::int32_t>() + index) = value;
}

template <>
inline void GameEngine::Library::Datum::Set(const float& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType =DatumType::Float;
	}
	else if (mType != DatumType::Float)
	{
		throw std::invalid_argument("Trying to assign float to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<float>() + index) = value;
}

template <>
inline void GameEngine::Library::Datum::Set(const glm::mat4x4& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Matrix;
	}
	else if (mType != DatumType::Matrix)
	{
		throw std::invalid_argument("Trying to assign Matrix to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<glm::mat4x4>() + index) = value;
}

template <>
inline void GameEngine::Library::Datum::Set(const RTTIPointer& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Pointer;
	}
	else if (mType != DatumType::Pointer)
	{
		throw std::invalid_argument("Trying to assign Pointer to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<RTTIPointer>() + index) = value;
}

template <>
inline void GameEngine::Library::Datum::Set(const std::string& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::String;
	}
	else if (mType != DatumType::String)
	{
		throw std::invalid_argument("Trying to assign String to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<std::string>() + index) = value;
}

template <>
inline void GameEngine::Library::Datum::Set(const glm::vec4& value, const std::uint32_t index)
{
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Vector;
	}
	else if (mType != DatumType::Vector)
	{
		throw std::invalid_argument("Trying to assign Vector to GameEngine::Library::Datum of different type.");
	}

	if (index >= Size())
	{
		SetSize(index + 1);
	}

	*(GetDataPointer<glm::vec4>() + index) = value;
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
