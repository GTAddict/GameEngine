#pragma once
#include <cstdint>
#include "SList.h"
#include "Vector.h"
#include "HashMapFunctors.h"

namespace GameEngine
{
	namespace Library
	{
		template <typename TKey, typename TValue, typename HashFunctor = DefaultHashFunctor>
		class HashMap
		{
		public:

			typedef std::pair<TKey, TValue>			PairType;
			typedef SList<PairType>					SListType;
			typedef Vector<SListType>				VectorType;
			typedef typename SListType::Iterator	SListIteratorType;
			typedef typename VectorType::Iterator	VectorIteratorType;

			class Iterator
			{
				friend class HashMap;

			public:

				Iterator() = delete;
				Iterator(HashMap* owner, VectorIteratorType vectorIt, SListIteratorType slistIt);
				Iterator(const Iterator& rhs);
				Iterator(Iterator&& rhs);
				~Iterator() = default;

				Iterator& operator=(const Iterator& rhs);
				Iterator& operator=(Iterator&& rhs);

				bool operator==(const Iterator& rhs);
				bool operator!=(const Iterator& rhs);

				Iterator& operator++();
				Iterator operator++(int);

				PairType& operator*();
				PairType* operator->();
					
			private:

				HashMap*							mpOwner;
				VectorIteratorType					mItVector;
				SListIteratorType					mItSlist;

			};

			HashMap() = delete;
			HashMap(std::uint32_t numBuckets);
			HashMap(const HashMap& rhs);
			HashMap(HashMap&& rhs);
			~HashMap() = default;

			HashMap& operator=(const HashMap& rhs);
			HashMap operator=(HashMap&& rhs);

			bool operator==(const HashMap& rhs);
			bool operator!=(const HashMap& rhs);

			Iterator	Insert(const PairType& entry);
			Iterator	Find(const TKey& key);
			bool		Remove(const TKey& key);
			TValue&		operator[](TKey& key);

			bool		ContainsKey(const TKey& key);

			void		Clear();

			Iterator	begin();
			Iterator	end();

			std::uint32_t	Size() const;

		private:

			VectorType&		Vector() { return mData; };
			SListType&		SListAt(std::uint32_t index) { return Vector().At(index); }
			SListType&		SListAt(VectorIteratorType it) { return Vector().At(it - Vector().begin()); }

			std::uint32_t	GetBucketNumber(const TKey& key);
			std::uint32_t	GetBucketSize();

			VectorType		mData;
			HashFunctor		mHashFunctor;
			std::uint32_t	mSize;
		};

#include "HashMap.inl"

	}
}