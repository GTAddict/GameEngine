#include "HashMap.h"
#pragma once

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const HashMap* const owner, VectorIteratorType vectorIt, SListIteratorType slistIt)
	: mpOwner(owner)
	, mItVector(vectorIt)
	, mItSlist(slistIt)
{
}

template <typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const Iterator& rhs)
{
	*this = rhs;
}

template <typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(Iterator&& rhs)
{
	*this = std::move(rhs);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(const Iterator& rhs)
{
	if (this != &rhs)
	{
		mpOwner = rhs.mpOwner;
		mItSlist = rhs.mItSlist;
		mItVector = rhs.mItVector;
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator=(Iterator&& rhs)
{
	if (this != &rhs)
	{
		mpOwner			= rhs.mpOwner;
		mItSlist		= rhs.mItSlist;
		mItVector		= rhs.mItVector;

		rhs.mpOwner		= nullptr;
		rhs.mItSlist	= SListIteratorType();
		rhs.mItVector	= VectorIteratorType();
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
{
	return mpOwner == rhs.mpOwner && mItSlist == rhs.mItSlist;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator& HashMap<TKey, TValue, HashFunctor>::Iterator::operator++()
{
	if (mItVector == mpOwner->Vector().end())
	{
		throw std::out_of_range("Trying to increment past end of hashmap!");
	}

	if (mItSlist == mpOwner->SListAt(mItVector).end() || ++mItSlist == mpOwner->SListAt(mItVector).end())
	{
		while (++mItVector != mpOwner->Vector().end() && mpOwner->SListAt(mItVector).IsEmpty());
		
		if (mItVector != mpOwner->Vector().end())
		{
			mItSlist = mpOwner->SListAt(mItVector).begin();
		}
		else
		{
			mItSlist = SListIteratorType();
		}
	}
	
	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Iterator::operator++(int)
{
	Iterator prevState = *this;
	++*this;
	return prevState;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::PairType& HashMap<TKey, TValue, HashFunctor>::Iterator::operator*()
{
	return *mItSlist;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::PairType* HashMap<TKey, TValue, HashFunctor>::Iterator::operator->()
{
	return &(*mItSlist);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::HashMap(const std::uint32_t numBuckets)
	: mData(numBuckets)
	, mSize(0)
{
	for (std::uint32_t i = 0; i < numBuckets; ++i)
	{
		Vector().PushBack(SList<PairType>());
	}
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::HashMap(const HashMap& rhs)
{
	operator=(rhs);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::HashMap(HashMap&& rhs)
{
	operator=(std::move(rhs));
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>& HashMap<TKey, TValue, HashFunctor>::operator=(const HashMap& rhs)
{
	if (this != &rhs)
	{
		mData = rhs.mData;
		mSize = rhs.mSize;
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor> HashMap<TKey, TValue, HashFunctor>::operator=(HashMap&& rhs)
{
	if (this != &rhs)
	{
		mData = std::move(rhs.mData);
		mSize = std::move(rhs.mSize);
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::operator==(const HashMap& rhs) const
{
	return mSize == rhs.mSize && mData == rhs.mData;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::operator!=(const HashMap& rhs) const
{
	return !(*this == rhs);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Insert(const PairType& entry)
{
	Iterator foundIt = Find(entry.first);

	if (foundIt == end())
	{
		++mSize;
		std::uint32_t bucketNumber = GetBucketNumber(entry.first);
		return Iterator(this, Vector().begin() + bucketNumber, SListAt(bucketNumber).PushBack(entry));
	}
	else
	{
		return foundIt;
	}
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::Find(const TKey& key) const
{
	std::uint32_t bucketNumber = GetBucketNumber(key);
	SListIteratorType it = SListAt(bucketNumber).begin(), itEnd = SListAt(bucketNumber).end();

	for (; it != itEnd; ++it)
	{
		if ((*it).first == key)
		{
			break;
		}
	}

	if (it == itEnd)
	{
		return end();
	}
	else
	{
		return Iterator(this, Vector().begin() + bucketNumber, it);
	}

}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::Remove(const TKey& key)
{
	Iterator foundIt = Find(key);

	if (foundIt != end())
	{
		--mSize;
		SListAt(foundIt.mItVector).Remove(*(foundIt.mItSlist));
		return true;
	}

	return false;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline TValue& HashMap<TKey, TValue, HashFunctor>::operator[](const TKey& key)
{
	return (*Insert(std::pair<TKey, TValue>(key, TValue()))).second;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::ContainsKey(const TKey& key) const
{
	return Find(key) != end();
}

template<typename TKey, typename TValue, typename HashFunctor>
inline void HashMap<TKey, TValue, HashFunctor>::Clear()
{
	mSize = 0;
	Vector().Clear();
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::begin() const
{
	VectorIteratorType it = Vector().begin(), itEnd = Vector().end();

	for (; it != itEnd; ++it)
	{
		if (!(*it).IsEmpty())
		{
			break;
		}
	}

	if (it == itEnd)
	{
		return end();
	}
	else
	{
		return Iterator(this, it, (*it).begin());
	}
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::end() const
{
	return Iterator(this, Vector().end(), SListIteratorType());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline std::uint32_t HashMap<TKey, TValue, HashFunctor>::Size() const
{
	return mSize;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::VectorType& HashMap<TKey, TValue, HashFunctor>::Vector()
{
	return mData;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline const typename HashMap<TKey, TValue, HashFunctor>::VectorType& HashMap<TKey, TValue, HashFunctor>::Vector() const
{
	return mData;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const std::uint32_t index)
{
	return Vector().At(index);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline const typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const std::uint32_t index) const
{
	return Vector().At(index);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const VectorIteratorType it)
{
	return Vector().At(it - Vector().begin());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline const typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const VectorIteratorType it) const
{
	return Vector().At(it - Vector().begin());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline std::uint32_t HashMap<TKey, TValue, HashFunctor>::GetBucketNumber(const TKey& key) const
{
	return mHashFunctor(key) % GetBucketSize();
}

template<typename TKey, typename TValue, typename HashFunctor>
inline std::uint32_t HashMap<TKey, TValue, HashFunctor>::GetBucketSize() const
{
	return Vector().Size();
}

