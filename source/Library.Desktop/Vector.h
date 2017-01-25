#pragma once
#include <cstdint>

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
		Iterator(T* element, const Vector<T>* const pOwner);

		/**
		 *	\brief			Copy constructor. This will copy the current element and owner pointer.
		 *	\param rhs		The Iterator to make a copy from.
		 */
		Iterator(const Iterator& rhs);

		/**
		 *	\brief			Assignment operator. This will copy the current element and owner pointer.
		 *	\param rhs		The Iterator to make a copy from.
		 *	\return			A copy of this newly created Iterator.
		 */
		Iterator& operator=(const Iterator& rhs);

		/**
		 *	\brief			The destructor. Does nothing.
		 */
		~Iterator();

		/**
		*	\brief			Equality operator. Checks whether the two operands are equal.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if both current element pointers are the same, false otherwise.
		*/
		bool operator==(const Iterator& rhs) const;
		
		/**
		*	\brief			Inequality operator. Checks whether the two operands are inequal.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if both current element pointers are not the same, false otherwise.
		*/
		bool operator!=(const Iterator& rhs) const;

		/**
		*	\brief			Less than operator. Checks whether this Iterator is less than the operand passed in.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if the address of the current element pointed to is less than the one of rhs,
		*					false otherwise.
		*/
		bool operator<(const Iterator& rhs) const;

		/**
		*	\brief			Greater than or equal operator. Checks whether this Iterator is greater than or equal
		*					to the operand passed in.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if the address of the current element pointed to is greater than or equal to the
		*					one of rhs, false otherwise.
		*/
		bool operator<=(const Iterator& rhs) const;

		/**
		*	\brief			Greater than operator. Checks whether this Iterator is greater than or equal to the
		*					operand passed in.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if the address of the current element pointed to is greater than the one of rhs,
		*					false otherwise.
		*/
		bool operator>(const Iterator& rhs) const;

		/**
		*	\brief			Greater than or equal operator. Checks whether this Iterator is greater than or equal
		*					to the operand passed in.
		*	\param rhs		The Iterator to compare to.
		*	\return			True if the address of the current element pointed to is greater than or equal to the
		*					one of rhs, false otherwise.
		*/
		bool operator>=(const Iterator& rhs) const;

		/**
		*	\brief			Addition operator. Adds the specified offset to the Iterator.
		*	\param rhs		The offset.
		*	\return			A new iterator pointing to the data at the specified offset.
		*/
		Iterator operator+(const std::uint32_t rhs);

		/**
		*	\brief			Subtraction operator. Subtracts the specified offset from the Iterator.
		*	\param rhs		The offset.
		*	\return			A new iterator pointing to the data at the specified offset.
		*/
		Iterator operator-(const std::uint32_t rhs);


		/**
		*	\brief			Subtraction operator. Subtracts the two Iterators.
		*	\param rhs		The Iterator to subtract.
		*	\return			The offset between the elements pointed at by the two Iterators.
		*/
		std::int32_t operator-(const Iterator& rhs);

		/**
		*	\brief			Pre-increment operator. Promotes the iterator to the next element
		*					and returns a reference to itself.
		*	\return			A reference to itself.
		*/
		Iterator& operator++();
		
		/**
		*	\brief			Post-increment operator. Promotes the iterator to the next element
		*					and returns a previously saved (and thus unmodified) copy of itself.
		*	\return			A copy of its state before this function was called.
		*/
		Iterator operator++(int rhs);

		/**
		*	\brief			Dereference operator. Returns a copy of the data at the location it is
		*					pointing to.
		*	\return			A copy of the data at the location pointer to by the iterator.
		*/
		T& operator*();

	private:

		T*					mpCurrent;				/**< The current element pointed to	*/
		const Vector<T>*	mpOwner;				/**< The owner Vector who owns the Iterator */
	};

	/** 
	 *	\brief				Default constructor. It will reserve DEFAULT_CONTAINER_SIZE by default.
	 */
							Vector();

	/**
	 *	\brief				Parametrized constructor. You can pass in the capacity to reserve at instantiation.
	 *	\param capacity		Capacity to reserve.
	 */
							Vector(std::uint32_t capacity);

	/**
	*	\brief				Parametrized constructor. Deep copies the Vector provided into itself.
	*	\param rhs			The Vector to copy from.
	*/
							Vector(const Vector& rhs);

	/**
	*	\brief				Assignment operator. Deep copies the Vector provided into itself.
	*	\param rhs			The Vector to copy from.
	*	\return				A reference to this newly created Vector.
	*/
	Vector&					operator=(const Vector& rhs);

	/**
	 *	\brief				Destructor. Clears all elements and frees memory.
	 */
							~Vector();

	/**
	 *	\brief				Allocates memory for the capacity specified, if it hasn't already.
	 *	\param capacity		The number of elements for which to allocate memory.
	 */
	void					Reserve(std::uint32_t capacity);

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
	 */
	void					PushBack(const T& data);

	/**
	 *	\brief				Removes the element at the back of the container, and calls its destructor.
	 */
	void					PopBack();

	/**
	 *	\brief				Returns the element at the front of the container.
	 *	\return				A non-const reference to the data at the front of the container.
	 */
	T&						Front();

	/**
	*	\brief				Returns the element at the front of the container.
	*	\return				A const reference to the data at the front of the container.
	*/
	const T&				Front() const;

	/**
	*	\brief				Returns the element at the back of the container.
	*	\return				A non-const reference to the data at the back of the container.
	*/
	T&						Back();

	/**
	*	\brief				Returns the element at the back of the container.
	*	\return				A const reference to the data at the back of the container.
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
	*/
	T&						At(std::uint32_t index);

	/**
	*	\brief				Returns the element at the specified index.
	*	\param index		The index whose data to retrieve.
	*	\return				A const reference to the data at the specified index.
	*/
	const T&				At(std::uint32_t index) const;
	
	/**
	*	\brief				Returns the element at the specified index.
	*	\param index		The index whose data to retrieve.
	*	\return				A const reference to the data at the specified index.
	*/
	const T&				operator[](const std::uint32_t index) const;

	/**
	*	\brief				Returns the element at the specified index.
	*	\param index		The index whose data to retrieve.
	*	\return				A non-const reference to the data at the specified index.
	*/
	T&						operator[](const std::uint32_t index);

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
	*/
	void					Remove(const Iterator& rangeBegin, const Iterator& rangeEnd);

	/**
	*	\brief				Removes all elements from the list, and also calls their destructors.
	*/
	void					Clear();

	/**
	*	\brief				Checks whether the provided Iterator is within the valid range of data.
	*	\return				Whether the Iterator is a valid Iterator on this container.
	*/
	bool					IsValid(const Iterator& it);

private:

	/**
	*	\brief				Moves the elements to a new location after operations such as Remove.
	*	\param destination	Where to move the elements
	*	\param source		Where to move the elements from
	*	\param count		How many elements to move
	*/
	void					MoveElements(Iterator destination, Iterator source, uint32_t count);

	T*		mpBegin;		/**< Points to the beginning of the vector. */
	T*		mpEnd;			/**< Points to the position after the last element of the vector. */
	T*		mpCapacity;		/**< Pointer to the end of the container. */
};

#include "Vector.inl"
