#pragma once
#include <cstdint>
#include <functional>

#define BIND_TO_GETCAPACITYFN(fn)		std::bind(fn, this, std::placeholders::_1, std::placeholders::_2)

namespace GameEngine
{
	namespace Library
	{
		/**
		 *	\class	Vector
		 *	\brief	Vector (dynamically growing array) implementation. Memory is allocated
		 *			contiguously. Reserve the amount of space you expect to use. Every reserve
		 *			call will re-allocate memory.
		 */
		template <typename T>
		class Vector
		{
		public:

			typedef std::function<std::uint32_t(std::uint32_t, std::uint32_t)>	GetCapacityFn_t;

			/**
			 *	\class	Iterator
			 *	\brief	Iterator implementation. This helps walk the Vector and wraps pointer
			 *			implementation inside.
			 */
			class Iterator
			{
				friend class Vector<T>;

			public:

				/**
				 *	\brief			Default constructor. Does not initialize current element or owner.
				 */
									Iterator();

				/**
				 *	\brief			Parametrized constructor. The current element to point to and the owner
				 *					Vector can be passed in.
				 *	\param T*		The current element to point to.
				 *	\param pOwner	The current owner Vector.
				 */
									Iterator(T* element, const Vector* const pOwner);

				/**
				 *	\brief			Copy constructor. This will copy the current element and owner pointer.
				 *	\param rhs		The Iterator to make a copy from.
				 */
									Iterator(const Iterator& rhs);

				/**
				*	\brief			Move constructor. This will transfer ownership of the data to itself.
				*	\param rhs		The Iterator to move from.
				*/
									Iterator(Iterator&& rhs);

				/**
				 *	\brief			Copy assignment operator. This will copy the current element and owner pointer.
				 *	\param rhs		The Iterator to make a copy from.
				 *	\return			A reference to this newly created Iterator.
				 */
				Iterator&			operator=(const Iterator& rhs);

				/**
				*	\brief			Move assignment operator. This transfer ownership of the data to itself.
				*	\param rhs		The Iterator to move from.
				*	\return			A reference to this newly created Iterator.
				*/
				Iterator&			operator=(Iterator&& rhs);

				/**
				 *	\brief			The destructor. Does nothing.
				 */
									~Iterator() = default;

				/**
				*	\brief			Equality operator. Checks whether the two operands are equal.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if both current element pointers are the same, false otherwise.
				*/
				bool				operator==(const Iterator& rhs) const;

				/**
				*	\brief			Inequality operator. Checks whether the two operands are unequal.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if both current element pointers are not the same, false otherwise.
				*/
				bool				operator!=(const Iterator& rhs) const;

				/**
				*	\brief			Less than operator. Checks whether this Iterator is less than the operand passed in.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if the address of the current element pointed to is less than the one of rhs,
				*					false otherwise.
				*	\throw std::invalid_argument if both the iterators do not belong to the same container.
				*/
				bool				operator<(const Iterator& rhs) const;

				/**
				*	\brief			Greater than or equal operator. Checks whether this Iterator is greater than or equal
				*					to the operand passed in.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if the address of the current element pointed to is greater than or equal to the
				*					one of rhs, false otherwise.
				*	\throw std::invalid_argument if both the iterators do not belong to the same container.
				*/
				bool				operator<=(const Iterator& rhs) const;

				/**
				*	\brief			Greater than operator. Checks whether this Iterator is greater than or equal to the
				*					operand passed in.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if the address of the current element pointed to is greater than the one of rhs,
				*					false otherwise.
				*	\throw std::invalid_argument if both the iterators do not belong to the same container.
				*/
				bool				operator>(const Iterator& rhs) const;

				/**
				*	\brief			Greater than or equal operator. Checks whether this Iterator is greater than or equal
				*					to the operand passed in.
				*	\param rhs		The Iterator to compare to.
				*	\return			True if the address of the current element pointed to is greater than or equal to the
				*					one of rhs, false otherwise.
				*	\throw std::invalid_argument if both the iterators do not belong to the same container.
				*/
				bool				operator>=(const Iterator& rhs) const;

				/**
				*	\brief			Addition operator. Adds the specified offset to the Iterator.
				*	\param rhs		The offset.
				*	\return			A new iterator pointing to the data at the specified offset.
				*/
				Iterator			operator+(const std::uint32_t rhs) const;

				/**
				*	\brief			Subtraction operator. Subtracts the specified offset from the Iterator.
				*	\param rhs		The offset.
				*	\return			A new iterator pointing to the data at the specified offset.
				*/
				Iterator			operator-(const std::uint32_t rhs) const;


				/**
				*	\brief			Subtraction operator. Subtracts the two Iterators.
				*	\param rhs		The Iterator to subtract.
				*	\return			The offset between the elements pointed at by the two Iterators.
				*	\throw std::invalid_argument if both the iterators do not belong to the same container.
				*/
				std::int32_t		operator-(const Iterator& rhs) const;

				/**
				*	\brief			Pre-increment operator. Promotes the iterator to the next element
				*					and returns a reference to itself.
				*	\return			A reference to itself.
				*/
				Iterator&			operator++();

				/**
				*	\brief			Post-increment operator. Promotes the iterator to the next element
				*					and returns a previously saved (and thus unmodified) copy of itself.
				*	\return			A copy of its state before this function was called.
				*/
				Iterator			operator++(int rhs);

				/**
				*	\brief			Dereference operator. Returns a copy of the data at the location it is
				*					pointing to.
				*	\return			A copy of the data at the location pointer to by the iterator.
				*	\throw std::out_of_range if the owner is empty or if the iterator is out of bounds.
				*/
				T&					operator*();

			private:

				T*					mpCurrent;				/**< The current element pointed to	*/
				const Vector*		mpOwner;				/**< The owner Vector who owns the Iterator */
			};

			/**
			 *	\brief				Default constructor. It will reserve DEFAULT_CONTAINER_SIZE by default.
			 */
									Vector();

			/**
			 *	\brief				Parametrized constructor. You can pass in the capacity to reserve at instantiation.
			 *	\param capacity		Capacity to reserve.
			 */
									Vector(const std::uint32_t capacity);

			/**
			*	\brief				Parametrized constructor. You can pass in the custom capacity function to call whenever
			*						the container needs to know the new capacity to resize to.
			*	\param customCapacityFn The custom function to call to get the new capacity.
			*	\param initialCapacity  This will override the value returned by customCapacityFn for the first allocation.
			*/
									Vector(const GetCapacityFn_t& customCapacityFn, const std::int32_t initialCapacity = 0);

			/**
			*	\brief				Copy constructor. Deep copies the Vector provided into itself.
			*	\param rhs			The Vector to copy from.
			*/
									Vector(const Vector& rhs);

			/**
			*	\brief				Move constructor. Transfers ownership of the list to itself.
			*	\param rhs			The Vector to move data from.
			*/
									Vector(Vector&& rhs);

			/**
			*	\brief				Copy assignment operator. Deep copies the Vector provided into itself.
			*	\param rhs			The Vector to copy from.
			*	\return				A reference to this newly created Vector.
			*/
			Vector&					operator=(const Vector& rhs);

			/**
			*	\brief				Move assignment operator. Transfers ownership of the list to itself.
			*	\param rhs			The Vector to move data from.
			*	\return				A reference to this newly created Vector.
			*/
			Vector&					operator=(Vector&& rhs);

			/**
			 *	\brief				Destructor. Clears all elements and frees memory.
			 */
									~Vector();

			/**
			 *	\brief				Equality operator. Checks whether the two operands are equal.
			 *	\param rhs			The Vector to compare to.
			 *	\return				True if the two Vectors are equal, false otherwise.
			 */
			bool					operator==(const Vector& rhs) const;

			/**
			*	\brief				Inequality operator. Checks whether the two operands are inequal.
			*	\param rhs			The Vector to compare to.
			*	\return				True if the two Vectors are inequal, false otherwise.
			*/
			bool					operator!=(const Vector& rhs) const;

			/**
			 *	\brief				Allocates memory for the capacity specified, if it hasn't already.
			 *	\param capacity		The number of elements for which to allocate memory.
			 */
			void					Reserve(const std::uint32_t capacity);

			/**
			 *	\brief				Returns max elements that can be stored in the current container.
			 *	\return				Container capacity.
			 */
			std::uint32_t			Capacity() const;

			/**
			 *	\brief				Returns number of elements currently stored in the container.
			 *	\return				Number of elements in the container.
			 */
			std::uint32_t			Size() const;

			/**
			 *	\brief				Returns whether the vector is empty.
			 *	\return				Whether the container is empty.
			 */
			bool					IsEmpty() const;

			/**
			 *	\brief				Inserts an element at the end of the container.
			 *	\param T			The data to be inserted.
			 *	\return				A copy of an iterator pointing to the data just pushed.
			 */
			Iterator				PushBack(const T& data);

			/**
			 *	\brief				Removes the element at the back of the container, and calls its destructor.
			 *	\throw std::out_of_range if the container is empty.
			 */
			void					PopBack();

			/**
			 *	\brief				Returns the element at the front of the container.
			 *	\return				A non-const reference to the data at the front of the container.
			 *	\throw std::out_of_range if the container is empty.
			 */
			T&						Front();

			/**
			*	\brief				Returns the element at the front of the container.
			*	\return				A const reference to the data at the front of the container.
			*	\throw std::out_of_range if the container is empty.
			*/
			const T&				Front() const;

			/**
			*	\brief				Returns the element at the back of the container.
			*	\return				A non-const reference to the data at the back of the container.
			*	\throw std::out_of_range if the container is empty.
			*/
			T&						Back();

			/**
			*	\brief				Returns the element at the back of the container.
			*	\return				A const reference to the data at the back of the container.
			*	\throw std::out_of_range if the container is empty.
			*/
			const T&				Back() const;

			/**
			*	\brief				Returns an Iterator to the first element in the container.
			*	\return				An Iterator to the first element in the container.
			*/
			Iterator				begin() const;

			/**
			*	\brief				Returns an Iterator to the element after the last element in the container.
			*	\return				An Iterator to the element after the last element in the container.
			*/
			Iterator				end() const;

			/**
			*	\brief				Returns the element at the specified index.
			*	\param index		The index whose data to retrieve.
			*	\return				A non-const reference to the data at the specified index.
			*	\throw std::out_of_range if the index is out of bounds.
			*/
			T&						At(const std::uint32_t index);

			/**
			*	\brief				Returns the element at the specified index.
			*	\param index		The index whose data to retrieve.
			*	\return				A const reference to the data at the specified index.
			*	\throw std::out_of_range if the index is out of bounds.
			*/
			const T&				At(const std::uint32_t index) const;

			/**
			*	\brief				Returns the element at the specified index.
			*	\param index		The index whose data to retrieve.
			*	\return				A non-const reference to the data at the specified index.
			*	\throw std::out_of_range if the index is out of bounds.
			*/
			T&						operator[](const std::uint32_t index);

			/**
			*	\brief				Returns the element at the specified index.
			*	\param index		The index whose data to retrieve.
			*	\return				A const reference to the data at the specified index.
			*	\throw std::out_of_range if the index is out of bounds.
			*/
			const T&				operator[](const std::uint32_t index) const;

			/**
			*	\brief				Searches for an element of specified value.
			*	\param T			The data to search for.
			*	\return				An Iterator pointing to the found data, or end() if it is not found.
			*/
			Iterator				Find(const T& data) const;

			/**
			*	\brief				Searches for and removes an element of specified value.
			*	\param T			The data to be searched for and removed.
			*/
			void					Remove(const T& data);

			/**
			*	\brief				Removes a specified range of elements, from rangeBegin to
			*						rangeEnd (both inclusive).
			*	\param rangeBegin	The Iterator from where to start removing elements.
			*	\param rangeEnd		The Iterator from where to end removing elements.
			*	\throw std::out_of_range if either Iterator provided is out of bounds, or if
			*	\					rangeBegin is greater than rangeEnd.
			*/
			void					Remove(const Iterator& rangeBegin, const Iterator& rangeEnd);

			/**
			 *	\brief				Removes all elements from the list, and also calls their destructors.
			 */
			void					Clear();

			/**
			 *	\brief				Reduces the capacity of the container to its size.
			 */
			void					ShrinkToFit();

			/**
			*	\brief				Checks whether the provided Iterator is within the valid range of data.
			*	\return				Whether the Iterator is a valid Iterator on this container.
			*/
			bool					IsValid(const Iterator& it) const;

		private:

			/**
			*	\brief				Returns the new capacity that is to be allocated given the current size
			*						and current capacity. This is the default implementation that will be
			*						assigned to fnGetCapacity if the user doesn't provide his own.
			*	\param size			The number of elements in the Vector right now.
			*	\param oldCapacity	Where to move the elements from
			*	\return				The new capacity to reserve.
			*/
			std::int32_t			GetNewCapacity(const std::uint32_t size, const std::uint32_t oldCapacity) const;

			/**
			 *	\brief				Reserves any capacity requested. The exposed Reserve checks to see whether
			 *						the requested capacity is greater than the current capacity. This does not.
			 *						This is useful to functions of this class such as Resize or ShrinkToFit.
			 *	\param capacity		The new capacity to reserve.
			 */
			void					Reserve_Internal(const std::uint32_t capacity);

			/**
			*	\brief				Moves the elements to a new location after operations such as Remove.
			*	\param destination	Where to move the elements
			*	\param source		Where to move the elements from
			*	\param count		How many elements to move
			*/
			void					MoveElements(Iterator destination, Iterator source, const std::uint32_t count);

			T*		mpBegin;		/**< Points to the beginning of the vector. */
			T*		mpEnd;			/**< Points to the position after the last element of the vector. */
			T*		mpCapacity;		/**< Pointer to the end of the container. */

			GetCapacityFn_t			mfnGetCapacity;	/**< Function object that returns the new capacity to allocate. */
		};

#include "Vector.inl"

	}	// namespace Library
}		// namespace GameEngine