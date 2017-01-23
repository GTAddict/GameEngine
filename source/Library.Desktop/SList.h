#pragma once
#include <cstdint>

/**
 *	\class	SList
 *	\brief	Templated simply linked list implementation. Copies data passed to it into
 *			a new node. Nodes are created on the heap. Note that passing in a pointer
 *			will copy the pointer, not the data.
 */
template <typename T>
class SList
{
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

public:

	/**
	*	\class		Iterator
	*	\brief		Iterator class that helps walk the list.
	*/
	class Iterator
	{
		friend class SList;

	public:

		/**
		 *	\brief	Default constructor, initializes current pointer to nullptr.
		 */
		Iterator();

		/**
		 *	\brief		Parametrized constructor, initializes current pointer to Node passed in.
		 *	\param node	Node that the Iterator should be initialized with.
		 *	\param list	List that the node is part of i.e. owner list.
		 */
		Iterator(Node* node, const SList<T>* const list);

		/**
		 *	\brief	Destructor, does nothing here.
		 */
		~Iterator();

		/**
		 *	\brief		Equality operator, checks whether addresses pointed to are same or not.
		 *				In the STL and MS implementations, containers are not checked. This does
		 *				not either.
		 *	\param rhs	The other Iterator to be compared to.
		 *	\return		Whether the two Iterators are equal.
		 */
		bool			operator==(const Iterator& rhs) const;

		/**
		 *	\brief		Inequality operator. Returns the opposite of the equality operator. 
		 *	\param rhs	The other Iterator to be compared to.
		 *	\return		Whether the two Iterators are inequal.
		 */
		bool			operator!=(const Iterator& rhs) const;

		/**
		 *	\brief	Pre-increment operator. Increments pointer and returns this.
		 *	\return	A reference to the instance just incremented.
		 */
		Iterator&	operator++();

		/**
		 *	\brief	Post-increment operator. Stores a copy, increments, and returns the copy.
		 *	\return	A copy of the instance just incremented.
		 */
		Iterator	operator++(int);

		/**
		*	\brief	Dereference operator. This will provide the data inside the Node pointed to
		*			by the Iterator.
		*	\return	A reference to the data contained in the Node pointed to by the Iterator.
		*/
		T&			operator*();

#if _DEBUG
		/**
		*	\brief		Utility function. This is provided so that a ToString function or similar
		*				may access the internal state in order to log or print to console.
		*				This function should not, and will not, be compiled in release mode.
		*	\return		The address of the Node pointed to as an unsigned int.
		*/
		uintptr_t		GetCurrentNodePtr()	const	{ return reinterpret_cast<uintptr_t>(mpCurrent); }

		/**
		*	\brief		Utility function. This is provided so that a ToString function or similar
		*				may access the internal state in order to log or print to console.
		*				This function should not, and will not, be compiled in release mode.
		*	\return		The address of the list associated with the iterator as an unsigned int.
		*/
		uintptr_t		GetOwnerPtr()		const	{ return reinterpret_cast<uintptr_t>(mpOwner);  }
#endif

	private:

		Node* mpCurrent;					/**< Stores pointer to the current node in the list */
		const SList<T>* mpOwner;			/**< Stores pointer to the container on which this iterator is used */
	};

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
	*	\brief		Inserts data after the given iterator.
	*	\param it	Iterator to insert after
	*	\param T	Data  to push
	*/
	void			InsertAfter(const Iterator& it, const T& data);

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
	uint32_t		Size() const;

	/**
	 *	\brief		Removes all the elements in the list.
	 */
	void			Clear();

	/**
	 *	\brief		Returns an iterator to the first element.
	 *	\return		An iterator to the first Node.
	 */
	Iterator		begin() const;
	
	/**
	*	\brief		Returns an iterator to the Node after the last element.
	*	\return		An iterator to the Node after the last Node.
	*/
	Iterator		end() const;
	
	/**
	*	\brief		Returns an iterator to the Node that contains the search element.
	*	\param T	The data to find.
	*	\return		An iterator to the found data.
	*/
	Iterator		Find(const T& data) const;
	
	/**
	*	\brief		Removes the Node that contains the provided data.
	*	\param		The data to be found and removed.
	*/
	void			Remove(const T& data);

protected:

private:

	Node*			mpBegin;				/**< Points to the first Node of the list */
	Node*			mpEnd;					/**< Points to the last Node of the list */
	uint32_t		mSize;					/**< Stores the current number of Nodes in the list */

};

#include "SList.inl"
