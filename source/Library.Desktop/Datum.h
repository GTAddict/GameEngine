#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#define GLM_FORCE_CXX98
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
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

#include "Datum.inl"

	}
}