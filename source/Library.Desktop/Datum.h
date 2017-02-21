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
		class Scope;
		class RTTI;

		/**
		 *	\class	Datum
		 *	\brief	Datum is a homogeneous Vector whose type is defined at runtime.
		 */
		class Datum
		{
			typedef RTTI*	RTTIPointer;
			typedef Scope*	ScopePointer;

			/**
			 *	\union	DatumValues
			 *	\brief	This union stores the pointers to the array of values this
			 *			container will store. A union is chosen because only one of
			 *			these types can be valid at any time.
			 */
			union DatumValues
			{
				std::int32_t*	pInt;						/**< Pointer to the array treated as ints */
				float*			pFloat;						/**< Pointer to the array treated as float */
				glm::vec4*		pVec4;						/**< Pointer to the array treated as vectors */
				glm::mat4x4*	pMat4;						/**< Pointer to the array treated as matrices */
				std::string*	pString;					/**< Pointer to the array treated as strings */
				ScopePointer*	ppScope;					/**< Pointer to the array treated as Scope pointers */
				RTTIPointer*	ppRTTI;						/**< Pointer to the array treated as RTTI pointers */
			};

		public:

			/**
			 *	\enum	DatumType
			 *	\brief	This enum stores the different types
			 *			of data this container can store.
			 */
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

			/**
			 *	\brief				Default constructor.
			 */
									Datum();

			/**
			 *	\brief				Copy constructor. Deep copies the Datum provided into itself.
			 *	\param rhs			The Datum to copy from.
			 */
									Datum(const Datum& rhs);

			/**
			 *	\brief				Move constructor. Transfers ownership of the data to itself.
			 *	\param rhs			The Datum to move data from.
			 */
									Datum(Datum&& rhs);

			/**
			 *	\brief				Destructor. Clears all elements and frees memory.
			 */
			virtual					~Datum();

			/**
			 *	\brief				Copy assignment operator. Deep copies the Datum provided into itself.
			 *	\param rhs			The Datum to copy from.
			 *	\return				A reference to the Datum assigned to.
			 */
			Datum&					operator=(const Datum& rhs);

			/**
			 *	\brief				Move assignment operator. Transfers ownership of the data to itself.
			 *	\param rhs			The Datum to move data from.
			 *	\return				A reference to the Datum assigned to.
			 */
			Datum&					operator=(Datum&& rhs);

			/**
			 *	\brief				Templated assignment operator for scalar assignment. Assigns zeroth
			 *						element to the operand if the type is defined and matches.
			 *	\param rhs			The scalar to assign.
			 *	\return				A reference to the Datum assigned to.
			 */
			template <typename T>
			Datum&					operator=(const T& rhs);

			/**
			 *	\brief				Equality operator. Checks whether the two operands are equal.
			 *	\param rhs			The Datum to compare to.
			 *	\return				True if the two Datums are equal, false otherwise.
			 */
			bool					operator==(const Datum& rhs) const;

			/**
			 *	\brief				Inequality operator. Checks whether the two operands are unequal.
			 *	\param rhs			The Datum to compare to.
			 *	\return				True if the two Vectors are unequal, false otherwise.
			 */
			bool					operator!=(const Datum& rhs) const;

			/**
			 *	\brief				Equality operator. Checks whether the two operands are equal.
			 *	\param rhs			The scalar to compare with.
			 *	\return				True if the type matches and the zeroth element equals operand,
			 *						false otherwise.
			 */
			template <typename T>
			bool					operator==(const T& rhs) const;

			/**
			 *	\brief				Inequality operator. Checks whether the two operands are unequal.
			 *	\param rhs			The scalar to compare with.
			 *	\return				False if the type matches and the zeroth element equals operand,
			 *						true otherwise.
			 */
			template <typename T>
			bool					operator!=(const T& rhs) const;

			/**
			*	\brief				Operator to simplify access to nested scopes.
			*	\param index		The index offset to retrieve the scope from.
			*	\return				A reference to the Scope at the specified index.
			*/
			Scope&					operator[](const std::uint32_t index);

			/**
			 *	\brief				Returns the type of data currently stored in the Datum.
			 *	\return				The type of data currently stored in the Datum.
			 */
			const DatumType&		Type() const;
			
			/**
			 *	\brief				Sets the type of data to be stored in the Datum.
			 *	\param type			The type of data to be stored in the Datum.
			 */
			void					SetType(const DatumType& type);

			/**
			 *	\brief				Returns the population of elements in the Datum.
			 *	\return				The population of elements in the Datum.
			 */ 
			std::uint32_t			Size() const;

			/**
			 *	\brief				Sets the size of the Datum. Reserves capacity
			 *						if needed.
			 *	\param size			The size to increase the Datum to.
			 */
			void					SetSize(const std::uint32_t size);

			/**
			 *	\brief				Removes all elements from the list, and also calls their destructors.
			 */
			void					Clear();

			/**
			 *	\brief				Allows user to specify external storage, thereby letting a different
			 *						part of the program do the memory management.
			 *	\param dataBlock	The external memory array.
			 *	\param size			The size of the array.
			 */
			template <typename T>
			void					SetStorage(T* dataBlock, const std::uint32_t size);

			/**
			*	\brief				Pushes data to the end of the Datum.
			*	\param value		Data to push.
			*/
			template <typename T>
			void					PushBack(const T& value);

			/**
			*	\brief				Removes the element that contains the provided data and calls its destructor.
			*	\param value		The data to be found and removed.
			*	\param return		True if the element is found and removed, false otherwise.
			*/
			template <typename T>
			bool					Remove(const T& value);

			/**
			*	\brief				Assigns value to element at index. Checks type compatibility
			*						and increases size/capacity if necessary.
			*	\param value		The value to set.
			*	\param index		The location to be set at.
			*/
			template <typename T>
			void					Set(const T& value, const std::uint32_t index = 0);

			/**
			*	\brief				Gets value at index.
			*	\param index		The location to get the value from.
			*	\return				A reference to the requested element.
			*/
			template <typename T>
			T&						Get(const uint32_t index = 0) const;

			/**
			*	\brief				Returns requested element as a string.
			*	\param index		The location to get the value from.
			*	\return				A copy of the data as an std::string.
			*/
			template <typename T>
			std::string				ToString(const std::uint32_t index = 0) const;

			/**
			*	\brief				Parses string, sets type and sets parsed value at
			*						specified index. DatumType needs to be set in order
			*						for this function to be called.
			*	\param inputString	The string to parse.
			*	\param index		The location to be set at.
			*/
			void					SetFromString(const std::string& inputString, const std::uint32_t index = 0);

		private:

			/**
			*	\brief				The templated implementation of Clear().
			*/
			template <typename T>
			void					Clear_Imp();

			/**
			*	\brief				Reserves the specified capacity by calling realloc.
			*	\param capacity		The capacity to be reserved.
			*/
			void					Reserve(const std::uint32_t capacity);

			/**
			*	\brief				The templated implementation of SetSize().
			*	\param size			The size to increase Datum to.
			*/
			template <typename T>
			void					SetSize_Imp(const std::uint32_t size);

			/**
			*	\brief				The templated implementation of Reserve().
			*	\param capacity		The capacity to be reserved.
			*/
			template <typename T>
			void					Reserve_Imp(const std::uint32_t capactiy);

			/**
			*	\brief				Templated function that returns the correct
			*						data pointer based on the templated type.
			*	\return				The internal data pointer in mData corresponding
			*						to the templated type.
			*/
			template <typename T>
			T*						GetDataPointer() const;

			/**
			*	\brief				Templated function that sets the correct data
			*						pointer based on the templated type.
			*	\param dataPointer	The address to set the internal data pointer in
			*						mData corresponding to the templated type to.
			*/
			template <typename T>
			void					SetDataPointer(T* dataPointer);

			DatumValues		mData;					/**< The wrapper to the pointer to the beginning of the data. */
			DatumType		mType;					/**< The type of data currently stored in the Datum. */
			std::uint32_t	mSize;					/**< The current population of the Datum. */
			std::uint32_t	mCapacity;				/**< The current memory reserved for the Datum. */
			bool			mExternalStorage;		/**< Whether the container is handling external storage */

		};

#include "Datum.inl"

	}
}