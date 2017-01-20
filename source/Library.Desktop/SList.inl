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
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mSize(0)
{
	Node* pNode = rhs.mpBegin;

	while (pNode != nullptr)
	{
		PushBack(pNode->mData);
		pNode = pNode->mpNext;
	}
}

template<typename T>
inline SList<T> & SList<T>::operator=(const SList<T>& rhs)
{
	if (this != &rhs)
	{
		Clear();

		Node* pNode = rhs.mpBegin;

		while (pNode != nullptr)
		{
			PushBack(pNode->mData);
			pNode = pNode->mpNext;
		}
	}

	return *this;
}

template <typename T>
inline void SList<T>::PushFront(const T& data)
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
inline void SList<T>::PushBack(const T& data)
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
inline unsigned int SList<T>::Size() const
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