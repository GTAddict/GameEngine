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
	 *	\brief		Default constructor. It will reserve DEFAULT_CONTAINER_SIZE by default.
	 */
	Vector();

	/**
	 *	\brief		Parametrized constructor. You can pass in the capacity to reserve at instantiation.
	 *	\param capacity	Capacity to reserve.
	 */
	Vector(std::uint32_t capacity);

	/**
	 *	\brief		Destructor. Clears all elements and frees memory.
	 */
	~Vector();

	/**
	 *	\brief		Allocates memory for the capacity specified, if it hasn't already.
	 */
	void			Reserve(std::uint32_t capacity);

	/**
	 *	\brief		Returns max elements that can be stored in the current container.
	 *	\return		Container capacity.
	 */
	std::uint32_t	Capacity() const;

	/**
	 *	\brief		Returns number of elements currently stored in the container.
	 *	\return		Number of elements in the container.
	 */
	std::uint32_t	Size() const;

	/**
	 *	\brief		Returns whether the vector is empty.
	 *	\return		Whether the container is empty.
	 */
	bool			IsEmpty() const;

	/**
	 *	\brief		Inserts an element at the end of the container.
	 *	\param T	The data to be inserted.
	 */
	void			PushBack(const T& data);

	/**
	 *	\brief		Removes the element at the back of the container, and calls its destructor.
	 */
	void			PopBack();

	/**
	 *	\brief		Returns the element at the front of the container.
	 *	\return		A non-const reference to the data at the front of the container.
	 */
	T&				Front();

	/**
	*	\brief		Returns the element at the front of the container.
	*	\return		A const reference to the data at the front of the container.
	*/
	const T&		Front() const;

	/**
	*	\brief		Returns the element at the back of the container.
	*	\return		A non-const reference to the data at the back of the container.
	*/
	T&				Back();

	/**
	*	\brief		Returns the element at the back of the container.
	*	\return		A const reference to the data at the back of the container.
	*/
	const T&		Back() const;

	/**
	*	\brief		Returns the element at the specified index.
	*	\return		A non-const reference to the data at the specified index.
	*/
	T&				At(std::uint32_t index);

	/**
	*	\brief		Returns the element at the specified index.
	*	\return		A const reference to the data at the specified index.
	*/
	const T&		At(std::uint32_t index) const;
	
	/**
	*	\brief		Returns the element at the specified index.
	*	\return		A const reference to the data at the specified index.
	*/
	const T&		operator[](const std::uint32_t index) const;

	/**
	*	\brief		Returns the element at the specified index.
	*	\return		A non-const reference to the data at the specified index.
	*/
	T&				operator[](const std::uint32_t index);

	/**
	*	\brief		Removes all elements from the list, and also calls their destructors.
	*/
	void			Clear();

private:

	T*		mpBegin;			/**< Points to the beginning of the vector. */
	T*		mpEnd;				/**< Points to the position after the last element of the vector. */
	T*		mpCapacity;			/**< Pointer to the end of the container. */
};

#include "Vector.inl"
