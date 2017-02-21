#include "HashMap.h"
#pragma once

template <typename TKey, typename TValue, typename HashFunctor>
HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator()
	: mpOwner(nullptr)
{
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor>::Iterator::Iterator(const HashMap* const owner, const VectorIteratorType& vectorIt, const SListIteratorType& slistIt)
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
		mpOwner		= rhs.mpOwner;
		mItSlist	= rhs.mItSlist;
		mItVector	= rhs.mItVector;
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
	if (!mpOwner)
	{
		throw std::out_of_range("Cannot increment iterator pointing to nullptr.");
	}

	if (mItVector == mpOwner->mVector.end())
	{
		throw std::out_of_range("Trying to increment past end of hashmap!");
	}

	if (mItSlist == mpOwner->SListAt(mItVector).end() || ++mItSlist == mpOwner->SListAt(mItVector).end())
	{
		while (++mItVector != mpOwner->mVector.end() && mpOwner->SListAt(mItVector).IsEmpty());
		
		if (mItVector != mpOwner->mVector.end())
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
	: mVector(numBuckets)
	, mSize(0)
{
	if (numBuckets == 0)
	{
		throw std::out_of_range("Bucket size needs to be greater than 0.");
	}

	for (std::uint32_t i = 0; i < numBuckets; ++i)
	{
		mVector.PushBack(SList<PairType>());
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
		mVector = rhs.mVector;
		mSize = rhs.mSize;
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline HashMap<TKey, TValue, HashFunctor> HashMap<TKey, TValue, HashFunctor>::operator=(HashMap&& rhs)
{
	if (this != &rhs)
	{
		mVector = std::move(rhs.mVector);
		mSize = std::move(rhs.mSize);
	}

	return *this;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::operator==(const HashMap& rhs) const
{
	return mSize == rhs.mSize && mVector == rhs.mVector;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::operator!=(const HashMap& rhs) const
{
	return !(*this == rhs);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline bool HashMap<TKey, TValue, HashFunctor>::Insert(const PairType& entry, Iterator& outIterator)
{
	outIterator = Find(entry.first);

	if (outIterator == end())
	{
		++mSize;
		std::uint32_t bucketNumber = GetBucketNumber(entry.first);
		outIterator = Iterator(this, mVector.begin() + bucketNumber, SListAt(bucketNumber).PushBack(entry));
		return true;
	}
	else
	{
		return false;
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
		return Iterator(this, mVector.begin() + bucketNumber, it);
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
	Iterator it;
	Insert(std::pair<TKey, TValue>(key, TValue()), it);
	return it->second;
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
	for (SList<PairType>& slist : mVector)
	{
		slist.Clear();
	}
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::Iterator HashMap<TKey, TValue, HashFunctor>::begin() const
{
	VectorIteratorType it = mVector.begin(), itEnd = mVector.end();

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
	return Iterator(this, mVector.end(), SListIteratorType());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline std::uint32_t HashMap<TKey, TValue, HashFunctor>::Size() const
{
	return mSize;
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const std::uint32_t index)
{
	return mVector.At(index);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline const typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const std::uint32_t index) const
{
	return mVector.At(index);
}

template<typename TKey, typename TValue, typename HashFunctor>
inline typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const VectorIteratorType it)
{
	return mVector.At(it - mVector.begin());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline const typename HashMap<TKey, TValue, HashFunctor>::SListType& HashMap<TKey, TValue, HashFunctor>::SListAt(const VectorIteratorType it) const
{
	return mVector.At(it - mVector.begin());
}

template<typename TKey, typename TValue, typename HashFunctor>
inline std::uint32_t HashMap<TKey, TValue, HashFunctor>::GetBucketNumber(const TKey& key) const
{
	return mHashFunctor(key) % mVector.Size();
}