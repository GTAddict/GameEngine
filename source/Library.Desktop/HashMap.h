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
				Iterator(const HashMap* const pOwner, VectorIteratorType vectorIt, SListIteratorType slistIt);
				Iterator(const Iterator& rhs);
				Iterator(Iterator&& rhs);
				~Iterator() = default;

				Iterator&	operator=(const Iterator& rhs);
				Iterator&	operator=(Iterator&& rhs);

				bool		operator==(const Iterator& rhs) const;
				bool		operator!=(const Iterator& rhs) const;

				Iterator&	operator++();
				Iterator	operator++(int);

				PairType&	operator*();
				PairType*	operator->();
					
			private:

				const HashMap*						mpOwner;
				VectorIteratorType					mItVector;
				SListIteratorType					mItSlist;

			};

			HashMap() = delete;
			HashMap(const std::uint32_t numBuckets);
			HashMap(const HashMap& rhs);
			HashMap(HashMap&& rhs);
			~HashMap() = default;

			HashMap& operator=(const HashMap& rhs);
			HashMap operator=(HashMap&& rhs);

			bool operator==(const HashMap& rhs) const;
			bool operator!=(const HashMap& rhs) const;

			Iterator			Insert(const PairType& entry);
			Iterator			Find(const TKey& key) const;
			bool				Remove(const TKey& key);
			TValue&				operator[](const TKey& key);

			bool				ContainsKey(const TKey& key) const;

			void				Clear();

			Iterator			begin() const;
			Iterator			end() const;

			std::uint32_t		Size() const;

		private:

			VectorType&			Vector()									{ return mData; };
			const VectorType&	Vector() const								{ return mData; };
			SListType&			SListAt(const std::uint32_t index)			{ return Vector().At(index); }
			const SListType&	SListAt(const std::uint32_t index) const	{ return Vector().At(index); }
			SListType&			SListAt(VectorIteratorType it)				{ return Vector().At(it - Vector().begin()); }

			std::uint32_t		GetBucketNumber(const TKey& key) const;
			std::uint32_t		GetBucketSize() const;

			VectorType			mData;
			std::uint32_t		mSize;
			const HashFunctor	mHashFunctor;
		};

#include "HashMap.inl"

	}
}