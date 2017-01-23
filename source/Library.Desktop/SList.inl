#include "SList.h"
#pragma once

template <typename T>
inline SList<T>::SList()
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mSize(0)
{
}

template <typename T>
inline SList<T>::~SList()
{
	Clear();
}

template<typename T>
inline SList<T>::SList(const SList<T>& rhs)
	: SList()
{
	*this = rhs;
}

template<typename T>
inline SList<T> & SList<T>::operator=(const SList<T>& rhs)
{
	if (this != &rhs)
	{
		Clear();

		for (const auto& data : rhs)
		{
			PushBack(data);
		}
	}

	return *this;
}

template <typename T>
inline typename SList<T>::Iterator SList<T>::PushFront(const T& data)
{
	Node* node = new Node();

	node->mData = data;
	++mSize;

	if (mpBegin == nullptr)
	{
		node->mpNext = nullptr;
		mpBegin = mpEnd = node;
	}
	else
	{
		node->mpNext = mpBegin;
		mpBegin = node;
	}

	return Iterator(node, this);
}

template <typename T>
inline void SList<T>::PopFront()
{
	if (mSize == 0)
	{
		throw std::out_of_range("The list is empty.");
	}

	--mSize;
	Node* node = mpBegin;

	if (mpBegin != mpEnd)
	{
		mpBegin = node->mpNext;
	}
	else
	{
		mpBegin = mpEnd = nullptr;
	}

	delete node;
}

template <typename T>
inline typename SList<T>::Iterator SList<T>::PushBack(const T& data)
{
	Node* node = new Node();

	node->mData = data;
	++mSize;

	if (mpEnd == nullptr)
	{
		node->mpNext = nullptr;
		mpBegin = mpEnd = node;
	}
	else
	{
		mpEnd->mpNext = node;
		mpEnd = node;
	}

	return Iterator(node, this);
}

template<typename T>
inline typename SList<T>::Iterator SList<T>::InsertAfter(const Iterator& it, const T& data)
{
	if (it.mpCurrent == nullptr)
	{
		throw std::out_of_range("Cannot insert after end of list.");
	}

	if (it.mpCurrent->mpNext == mpEnd)
	{
		return PushBack(data);
	}

	Node* node = new Node();
	node->mData = data;
	++mSize;

	node->mpNext = it.mpCurrent->mpNext;
	it.mpCurrent->mpNext = node;

	if (node->mpNext == nullptr)
	{
		mpEnd = node;
	}

	return Iterator(node, this);
}

template <typename T>
inline bool SList<T>::IsEmpty() const
{
	return mSize == 0;
}

template <typename T>
inline const T& SList<T>::Front() const
{
	if (mSize == 0)
	{
		throw std::out_of_range("The list is empty.");
	}

	return mpBegin->mData;
}

template <typename T>
inline T& SList<T>::Front()
{
	return const_cast<T&>(const_cast<const SList* const>(this)->Front());
}

template <typename T>
inline const T& SList<T>::Back() const
{
	if (mSize == 0)
	{
		throw std::out_of_range("The list is empty.");
	}

	return mpEnd->mData;
}

template <typename T>
inline T& SList<T>::Back()
{
	return const_cast<T&>(const_cast<const SList* const>(this)->Back());
}

template <typename T>
inline std::uint32_t SList<T>::Size() const
{
	return mSize;
}

template <typename T>
inline void SList<T>::Clear()
{
	while (mSize != 0)
	{
		PopFront();
	}
}

template<typename T>
inline typename SList<T>::Iterator SList<T>::begin() const
{
	return Iterator(mpBegin, this);
}

template<typename T>
inline typename SList<T>::Iterator SList<T>::end() const
{
	if (mpBegin == mpEnd)
	{
		return Iterator(mpBegin, this);
	}
	else
	{
		return Iterator(mpEnd->mpNext, this);
	}
}

template<typename T>
inline typename SList<T>::Iterator SList<T>::Find(const T& data) const
{	
	Iterator it = begin(), itEnd = end();

	for (; it != itEnd; ++it)
	{
		if (*it == data)
		{
			return it;
		}
	}

	return it;
}

template<typename T>
inline typename void SList<T>::Remove(const T& data)
{
	Iterator it = Find(data);

	if (it.mpCurrent != nullptr)
	{
		if (it.mpCurrent == mpBegin)
		{
			PopFront();
		}
		else
		{
			SList<T>::Iterator prevIt = begin();
			while (prevIt.mpCurrent->mpNext != it.mpCurrent)
			{
				++prevIt;
			}

			prevIt.mpCurrent->mpNext = it.mpCurrent->mpNext;
			delete it.mpCurrent;
			--mSize;
		}
	}
}

template<typename T>
inline SList<T>::Iterator::Iterator()
	: mpOwner(nullptr)
{
	// Leave node unitialized.
}

template<typename T>
inline SList<T>::Iterator::Iterator(Node* node, const SList<T>* const list)
	: mpCurrent(node)
	, mpOwner(list)
{
}

template<typename T>
inline SList<T>::Iterator::~Iterator()
{
}

template<typename T>
inline bool SList<T>::Iterator::operator==(const Iterator& rhs) const
{
	return mpOwner && rhs.mpOwner && ((mpOwner == rhs.mpOwner) && (mpCurrent == rhs.mpCurrent));
}

template<typename T>
inline bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
inline typename SList<T>::Iterator& SList<T>::Iterator::operator++()
{
	if (mpCurrent == nullptr)
	{
		throw std::out_of_range("Cannot increment past end of list.");
	}

	mpCurrent = mpCurrent->mpNext;

	return *this;
}

template<typename T>
inline typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
{
	Iterator prevState = *this;
	++*this;
	return prevState;
}

template<typename T>
inline T& SList<T>::Iterator::operator*()
{
	if (mpCurrent == nullptr)
	{
		throw std::runtime_error("Cannot perform operation on nullptr!");
	}

	return mpCurrent->mData;
}