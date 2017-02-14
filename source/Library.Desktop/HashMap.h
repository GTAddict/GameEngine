#pragma once
#include <cstdint>
#include "SList.h"
#include "Vector.h"
#include "HashMapFunctors.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Hash Map
		*	\brief	An unordered map that stores key-value pairs. Bucket size is to be
		*			allocated by the user. Collisions are resolved by chaining. The
		*			implementation is a Vector of fixed size containing SLists.
		*/
		template <typename TKey, typename TValue, typename HashFunctor = DefaultHashFunctor>
		class HashMap
		{
		public:

			typedef std::pair<TKey, TValue>			PairType;
			typedef SList<PairType>					SListType;
			typedef Vector<SListType>				VectorType;
			typedef typename SListType::Iterator	SListIteratorType;
			typedef typename VectorType::Iterator	VectorIteratorType;

			static const std::uint32_t DEFAULT_BUCKET_SIZE = 10;

			/**
			*	\class	Iterator
			*	\brief	Iterator implementation. This helps walk the HashMap and wraps pointer
			*			implementation inside.
			*/
			class Iterator
			{
				friend class HashMap;

			private:

				/**
				*	\brief			Parametrized constructor. The owner HashMap, bucket iterator and
				*					chain iterator are to be passed in.
				*	\param pOwner	The current owner HashMap.
				*	\param vectorIt	The bucket iterator, whose SList contains slistIt.
				*	\param slistIt	The chain iterator to point to.
				*/
				Iterator(const HashMap* const pOwner, const VectorIteratorType& vectorIt, const SListIteratorType& slistIt);

			public:

				/**
				*	\brief			Default constructor.
				*/
									Iterator();

				/**
				*	\brief			Copy constructor.
				*	\param rhs		The iterator to copy from.
				*/
									Iterator(const Iterator& rhs);

				/**
				*	\brief			Move constructor.
				*	\param rhs		The iterator to move from.
				*/
									Iterator(Iterator&& rhs);

				/**
				*	\brief			Destructor, does nothing.
				*/
				virtual				~Iterator() = default;

				/**
				*	\brief			Copy assignment operator.
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
				*	\brief			Pre-increment operator. Promotes the iterator to the next element
				*					and returns a reference to itself.
				*	\return			A reference to itself.
				*	\throw std::out_of_range if the iterator is out of bounds.
				*/
				Iterator&			operator++();

				/**
				*	\brief			Post-increment operator. Promotes the iterator to the next element
				*					and returns a previously saved (and thus unmodified) copy of itself.
				*	\return			A copy of its state before this function was called.
				*	\throw std::out_of_range if the iterator is out of bounds.
				*/
				Iterator			operator++(int);

				/**
				*	\brief			Dereference operator. Returns a reference to the data at the location it is
				*					pointing to.
				*	\return			A reference to the data at the location pointer to by the iterator.
				*	\throw			Refer to SList::Iterator as this function deferences that internally.
				*/
				PairType&			operator*();

				/**
				*	\brief			Arrow operator. Returns the address of the data at the location it is
				*					pointing to.
				*	\return			A copy of the data at the location pointer to by the iterator.
				*	\throw			Refer to SList::Iterator as this function deferences that internally.
				*/
				PairType*			operator->();
					
			private:

				const HashMap*		mpOwner;				/**< The owner HashMap who owns this Iterator */
				VectorIteratorType	mItVector;				/**< The bucket iterator which contains the mItSlist stored */
				SListIteratorType	mItSlist;				/**< The current element iterator pointed to */

			};

			/**
			*	\brief				Parametrized constructor. You can pass in the bucket size at instantiation.
			*	\param numBuckets	Bucket size of the HashMap.
			*/
			explicit				HashMap(const std::uint32_t numBuckets = DEFAULT_BUCKET_SIZE);

			/**
			*	\brief				Copy constructor. Deep copies the HashMap provided into itself.
			*	\param rhs			The HashMap to copy from.
			*/
									HashMap(const HashMap& rhs);

			/**
			*	\brief				Move constructor. Transfers ownership of the list to itself.
			*	\param rhs			The Vector to move data from.
			*/
									HashMap(HashMap&& rhs);

			/**
			*	\brief				Destructor, does nothing.
			*/
			virtual					~HashMap() = default;

			/**
			*	\brief				Copy assignment operator. Deep copies the HashMap provided into itself.
			*	\param rhs			The HashMap to copy from.
			*	\return				A reference to this newly created HashMap.
			*/
			HashMap&				operator=(const HashMap& rhs);

			/**
			*	\brief				Move assignment operator. Transfers ownership of the HashMap to itself.
			*	\param rhs			The HashMap to move data from.
			*	\return				A reference to this newly created HashMap.
			*/
			HashMap					operator=(HashMap&& rhs);

			/**
			*	\brief				Equality operator. Checks whether the two operands are equal.
			*	\param rhs			The HashMap to compare to.
			*	\return				True if the two HashMaps are equal, false otherwise.
			*/
			bool					operator==(const HashMap& rhs) const;

			/**
			*	\brief				Inequality operator. Checks whether the two operands are uequal.
			*	\param rhs			The HashMap to compare to.
			*	\return				True if the two HashMaps are unequal, false otherwise.
			*/
			bool					operator!=(const HashMap& rhs) const;

			/**
			*	\brief				Inserts an key-value pair based on the hash of the key. You
			*						may provide your own hashing function as a template during
									object declaration, or you may use the default.
			*	\param entry		A key-value std::pair.
			*	\return				A copy of an iterator pointing to the pair just inserted.
			*/
			Iterator				Insert(const PairType& entry);

			/**
			*	\brief				Searches for specified key.
			*	\param key			The key to search for.
			*	\return				An Iterator pointing to the found pair, or end() if it is not found.
			*/
			Iterator				Find(const TKey& key) const;

			/**
			*	\brief				Searches for and removes an pair of specified key.
			*	\param key			The key whose entry is to be removed.
			*	\return				True if the key was found and removed, false otherwise.
			*/
			bool					Remove(const TKey& key);

			/**
			*	\brief				Returns a reference to the pair with the specified key.
			*						If no entry is found, one is created.
			*	\param key			The key whose pair to retrieve.
			*	\return				A non-const reference to the pair with the specified key.
			*/
			TValue&					operator[](const TKey& key);

			/**
			*	\brief				Reports whether a specified key exists in the HashMap.
			*	\param key			The key to search for.
			*	\return				True if the key exists, false otherwise.
			*/
			bool					ContainsKey(const TKey& key) const;

			/**
			*	\brief				Removes all elements from the HashMap, and also calls their destructors.
			*/
			void					Clear();

			/**
			*	\brief				Returns an Iterator to the first non-empty element in the container.
			*	\return				An Iterator to the first non-empty element in the container.
			*/
			Iterator				begin() const;

			/**
			*	\brief				Returns an Iterator to the element after the last element in the container.
			*	\return				An Iterator to the element after the last element in the container.
			*/
			Iterator				end() const;

			/**
			*	\brief				Returns number of non-empty elements currently stored in the container.
			*	\return				Number of non-empty elements in the container.
			*/
			std::uint32_t			Size() const;

		private:

			/**
			*	\brief				Helper function that returns the implementation SList at a specified position
			*						in the implementation Vector, for this HashMap.
			*						This is the non-const version.
			*	\param index		The position of the Vector to retrieve the SList from.
			*	\return				A non-const reference to the SList at a specified position of the Vector used
			*						in implementing this HashMap.
			*/
			SListType&				SListAt(const std::uint32_t index);

			/**
			*	\brief				Helper function that returns the implementation SList at a specified position
			*						in the implementation Vector, for this HashMap.
			*						This is the const version.
			*	\param index		The position of the Vector to retrieve the SList from.
			*	\return				A const reference to the SList at a specified position of the Vector used
			*						in implementing this HashMap.
			*/
			const SListType&		SListAt(const std::uint32_t index) const;

			/**
			*	\brief				Helper function that returns the implementation SList at a specified iterator
			*						position in the implementation Vector, for this HashMap.
			*						This is the non-const version.
			*	\param it			The iterator of the Vector to retrieve the SList from.
			*	\return				A non-const reference to the SList at a specified iterator position of the Vector
			*						used in implementing this HashMap.
			*/
			SListType&				SListAt(const VectorIteratorType it);

			/**
			*	\brief				Helper function that returns the implementation SList at a specified iterator
			*						position in the implementation Vector, for this HashMap.
			*						This is the const version.
			*	\param it			The iterator of the Vector to retrieve the SList from.
			*	\return				A const reference to the SList at a specified iterator position of the Vector
			*						used in implementing this HashMap.
			*/
			const SListType&		SListAt(const VectorIteratorType it) const;

			/**
			*	\brief				Helper function that returns the bucket a specified key belongs to.
			*						This is determined internally by calling the hash functor.
			*	\param key			The key whose bucket is to be found.
			*	\return				The bucket the specified key belongs to.
			*/
			std::uint32_t			GetBucketNumber(const TKey& key) const;

			VectorType				mVector;								/**< The implementation Vector that is used */
			std::uint32_t			mSize;									/**< Stores the current number of non-empty elements in the container */
			const HashFunctor		mHashFunctor;							/**< Instance of the templated hash functor to be used in hashing elements */
		};

#include "HashMap.inl"

	}
}