#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#define GLM_FORCE_CXX98
#include <glm/glm.hpp>
#include "RTTI.h"

namespace GameEngine
{
	namespace Library
	{
		class Datum
		{
			typedef GameEngine::Library::RTTI* RTTIPointer;

			union DatumValues
			{
				std::int32_t*	pInt;
				float*			pFloat;
				glm::vec4*		pVec4;
				glm::mat4x4*	pMat4;
				std::string*	pString;
				RTTI**			ppRTTI;
			};

		public:

			enum class DatumType
			{
				Unknown = -1,
				Integer = 0,
				Float,
				Vector,
				Matrix,
				Table,
				String,
				Pointer
			};

			Datum();
			Datum(const Datum& rhs);
			Datum(Datum&& rhs);
			virtual ~Datum();
			 
			Datum& operator=(const Datum& rhs);
			Datum& operator=(Datum&& rhs);

			template <typename T>
			Datum& operator=(const T& rhs);

			bool operator==(const Datum& rhs) const;
			bool operator!=(const Datum& rhs) const;

			template <typename T>
			bool operator==(const T& rhs) const;
			template <typename T>
			bool operator!=(const T& rhs) const;


			const DatumType&		Type() const;
			void					SetType(const DatumType& type);
			
			std::uint32_t			Size() const;
			void					SetSize(const std::uint32_t size);

			void					Clear();

			template <typename T>
			void					Set(const T& value, const std::uint32_t index = 0);

			template <typename T>
			T&						Get(const uint32_t index = 0) const;

			template <typename T>
			std::string				ToString(const std::uint32_t index);

			void					SetFromString(std::string& inputString, const std::uint32_t index = 0);

		private:

			template <typename T>
			void					Clear_Imp();

			void					Reserve(const std::uint32_t capacity);
			
			template <typename T>
			void					SetSize_Imp(const std::uint32_t size);

			template <typename T>
			void					Reserve_Imp(const std::uint32_t capactiy);

			template <typename T>
			T*						GetDataPointer() const;

			template <typename T>
			void					SetDataPointer(T* dataPointer);

			DatumValues		mData;
			DatumType		mType;
			std::uint32_t	mSize;
			std::uint32_t	mCapacity;

		};

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
		inline T* Library::Datum::GetDataPointer() const
		{
			static_assert(false, "You need to provide implementation for your class.");
			return nullptr;
		}

		template <>
		inline std::int32_t* Library::Datum::GetDataPointer() const
		{
			return mData.pInt;
		}

		template <>
		inline float* Library::Datum::GetDataPointer() const
		{
			return mData.pFloat;
		}

		template <>
		inline glm::vec4* Library::Datum::GetDataPointer() const
		{
			return mData.pVec4;
		}

		template <>
		inline glm::mat4x4* Library::Datum::GetDataPointer() const
		{
			return mData.pMat4;
		}

		template <>
		inline std::string* Library::Datum::GetDataPointer() const
		{
			return mData.pString;
		}

		template <>
		inline Datum::RTTIPointer* Library::Datum::GetDataPointer() const
		{
			return mData.ppRTTI;
		}

		template<typename T>
		inline void Datum::SetDataPointer(T* dataPointer)
		{
			static_assert(false, "You need to provide implementation for your class.");
			return nullptr;
		}

		template <>
		inline void Datum::SetDataPointer(std::int32_t* dataPointer)
		{
			mData.pInt = dataPointer;
		}

		template <>
		inline void Datum::SetDataPointer(float* dataPointer)
		{
			mData.pFloat = dataPointer;
		}

		template <>
		inline void Datum::SetDataPointer(glm::vec4* dataPointer)
		{
			mData.pVec4 = dataPointer;
		}

		template <>
		inline void Datum::SetDataPointer(glm::mat4x4* dataPointer)
		{
			mData.pMat4 = dataPointer;
		}

		template <>
		inline void Datum::SetDataPointer(std::string* dataPointer)
		{
			mData.pString = dataPointer;
		}

		template <>
		inline void Datum::SetDataPointer(RTTIPointer* dataPointer)
		{
			mData.ppRTTI = dataPointer;
		}

		template <typename T>
		Datum& Datum::operator=(const T& rhs)
		{
			Set(T);
			return *this;
		}

		template <typename T>
		inline void Datum::Set(const T& value, const std::uint32_t index)
		{
			static_assert("Not implemented.");
		}

		template <>
		inline void Datum::Set(const std::int32_t& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::Integer;
			}
			else if (mType != DatumType::Integer)
			{
				throw std::invalid_argument("Trying to assign std::int32_t to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<std::int32_t>() + index) = value;
		}

		template <>
		inline void Datum::Set(const float& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::Float;
			}
			else if (mType != DatumType::Float)
			{
				throw std::invalid_argument("Trying to assign float to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<float>() + index) = value;
		}

		template <>
		inline void Datum::Set(const glm::mat4x4& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::Matrix;
			}
			else if (mType != DatumType::Matrix)
			{
				throw std::invalid_argument("Trying to assign Matrix to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<glm::mat4x4>() + index) = value;
		}

		template <>
		inline void Datum::Set(const RTTIPointer& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::Pointer;
			}
			else if (mType != DatumType::Pointer)
			{
				throw std::invalid_argument("Trying to assign Pointer to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<RTTIPointer>() + index) = value;
		}

		template <>
		inline void Datum::Set(const std::string& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::String;
			}
			else if (mType != DatumType::String)
			{
				throw std::invalid_argument("Trying to assign String to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<std::string>() + index) = value;
		}

		template <>
		inline void Datum::Set(const glm::vec4& value, const std::uint32_t index)
		{
			if (mType == DatumType::Unknown)
			{
				mType = DatumType::Vector;
			}
			else if (mType != DatumType::Vector)
			{
				throw std::invalid_argument("Trying to assign Vector to Datum of different type.");
			}

			if (index >= Size())
			{
				SetSize(index + 1);
			}

			*(GetDataPointer<glm::vec4>() + index) = value;
		}

		template<typename T>
		inline T& Datum::Get(const std::uint32_t index) const
		{
			if (index >= Size())
			{
				throw std::out_of_range("Out of bounds.");
			}

			return *(GetDataPointer<T>() + index);
		}

		template <typename T>
		inline std::string Datum::ToString(const std::uint32_t index)
		{
			static_assert("Provide implementation for your class.");
		}

		template <>
		inline std::string Datum::ToString<float>(const std::uint32_t index)
		{
			std::stringstream s;
			s << Get<float>(index);
			return s.str();
		}

		template <>
		inline std::string Datum::ToString<std::int32_t>(const std::uint32_t index)
		{
			std::stringstream s;
			s << Get<std::int32_t>(index);
			return s.str();
		}

		template <>
		inline std::string Datum::ToString<glm::mat4x4>(const std::uint32_t index)
		{
			std::stringstream s;
			s << "Length: " << Get<glm::mat4x4>(index).length();
			return s.str();
		}

		template <>
		inline std::string Datum::ToString<glm::vec4>(const std::uint32_t index)
		{
			std::stringstream s;
			s << "Length: " << Get<glm::vec4>(index).length();
			return s.str();
		}

		template <>
		inline std::string Datum::ToString<std::string>(const std::uint32_t index)
		{
			return Get<std::string>(index);
		}

		template <>
		inline std::string Datum::ToString<Datum::RTTIPointer>(const std::uint32_t index)
		{
			return Get<Datum::RTTIPointer>(index)->ToString();
		}
	}
}