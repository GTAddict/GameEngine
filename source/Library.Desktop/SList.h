#pragma once

/**
 *	\class	SList
 *	\brief	Templated simply linked list implementation. Copies data passed to it into
 *			a new node. Nodes are created on the heap. Note that passing in a pointer
 *			will copy the pointer, not the data.
 */
template <typename T>
class SList
{
public:
	/**
	 *	\brief		Default constructor, initializes the list to empty.
	 */
	SList();

	/**
	 *	\brief		Destructor, clears the list.
	 */
	~SList();

	/**
	 *	\brief		Parametrized constructor, initializes the list
	 *				to empty and then deep copies the list passed in.
	 */
	SList(const SList<T>& rhs);

	/**
	 *	\brief		Assignment operator, clears this list and deep copies
	 *				the list passed in.
	 */
	SList<T>& operator=(const SList<T>& rhs);

	/** 
	 *	\brief		Pushes data to the beginning of the list.
	 *	\param T	Data to push
	 */
	void			PushFront(const T& data);

	/**
	 *	\brief		Pops data from the beginning of the list.
	 *				Does not return the data.
	 */
	void			PopFront();

	/**
	 *	\brief		Pushes data to the end of the list. 
	 *	\param T	Data  to push
	 */
	void			PushBack(const T& data);

	/**
	 *	\brief		Checks whether the list contains any elements.
	 *				The elements are not counted dynamically,
	 *				the size is cached.
	 *	\return		Whether the list has a zero element count.
	 */
	bool			IsEmpty() const;
	
	/**
	 *	\brief		Returns the first element in the list as an
	 *				immutable object.
	 *	\return		const reference to the first element.
	 */
	const	T&		Front() const;	

	/**
	 *	\brief		Returns the first element in the list as a
	 *				mutable object.
	 *	\return		non-const reference to the first element.
	 */
			T&		Front();

	/**
	 *	\brief		Returns the last element in the list as an
	 *				immutable object.
	 *	\return		const reference to the last element.
	 */
	const	T&		Back() const;	

	/**
	 *	\brief		Returns the last element in the list as a
	 *				mutable object.
	 *	\return		non-const reference to the last element.
	 */
			T&		Back();

	/**
	 *	\brief		Returns the number of elements contained in
	 *				the list. They are not counted dynamically,
	 *				the size is cached.
	 *	\return		The number of elements contained in the list.
	 */
	unsigned int	Size() const;

	/**
	 *	\brief		Removes all the elements in the list.
	 */
	void			Clear();

protected:

private:

	/**
	 *	\struct		Node
	 *	\brief		Internal data structure used by SList
	 *				to store the data passed in to it.
	 */
	struct Node
	{
		T mData;							/**< Copy of the data passed in */
		Node* mpNext;						/**< Points to the next node in the list */
	};

	Node*			mpBegin;				/**< Points to the first Node of the list */
	Node*			mpEnd;					/**< Points to the last Node of the list */
	unsigned int	mSize;					/**< Stores the current number of Nodes in the list */
};

#include "SList.inl"
