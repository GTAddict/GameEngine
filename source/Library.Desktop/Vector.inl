#include "Vector.h"
#pragma once

const std::uint32_t DEFAULT_CONTAINER_SIZE = 5;

template <typename T>
inline Vector<T>::Vector()
	: Vector(DEFAULT_CONTAINER_SIZE)
{
}

template <typename T>
inline Vector<T>::Vector(std::uint32_t capacity)
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mpCapacity(nullptr)
{
	Reserve(capacity);
	mpEnd = mpBegin;
}

template <typename T>
inline Vector<T>::~Vector()
{
	Clear();
	free(mpBegin);
}

template <typename T>
inline Vector<T>::Iterator::Iterator()
{
	// Leave current element unintialized.
}

template<typename T>
inline Vector<T>::Iterator::Iterator(T* element, const Vector<T>* const pOwner)
{
	mpCurrent = element;
	mpOwner	  = pOwner;
}

template<typename T>
inline Vector<T>::Iterator::Iterator(const Iterator& rhs)
{
	*this = rhs;
}

template<typename T>
inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator & rhs)
{
	if (this != &rhs)
	{
		mpCurrent	= rhs.mpCurrent;
		mpOwner		= rhs.mpOwner;
	}

	return *this;
}

template <typename T>
inline Vector<T>::Iterator::~Iterator()
{
}

template <typename T>
inline bool Vector<T>::Iterator::operator==(const Iterator & rhs) const
{
	return mpCurrent == rhs.mpCurrent;
}

template <typename T>
inline bool Vector<T>::Iterator::operator!=(const Iterator & rhs) const
{
	return !(*this == rhs);
}

template<typename T>
inline bool Vector<T>::Iterator::operator<(const Iterator & rhs) const
{
	return mpCurrent < rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator<=(const Iterator & rhs) const
{
	return mpCurrent <= rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>(const Iterator & rhs) const
{
	return mpCurrent > rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>=(const Iterator & rhs) const
{
	return mpCurrent >= rhs.mpCurrent;
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+(uint32_t rhs)
{
	return Iterator (mpCurrent + rhs, mpOwner);
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-(uint32_t rhs)
{
	return Iterator(mpCurrent - rhs, mpOwner);
}

template<typename T>
inline std::int32_t Vector<T>::Iterator::operator-(const Iterator & rhs)
{
	return static_cast<std::int32_t>(mpCurrent - rhs.mpCurrent);
}

template <typename T>
inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	++mpCurrent;
	return *this;
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
	Iterator prevState = *this;
	++mpCurrent;
	return prevState;
}

template <typename T>
inline T& Vector<T>::Iterator::operator*()
{
	if (mpOwner->IsEmpty() || *this < mpOwner->begin() || *this >= mpOwner->end())
	{
		throw std::out_of_range("Out of bounds.");
	}

	return *mpCurrent;
}

template <typename T>
inline std::uint32_t Vector<T>::Capacity() const
{
	return static_cast<std::uint32_t>(mpCapacity - mpBegin);
}

template <typename T>
inline std::uint32_t Vector<T>::Size() const
{
	return static_cast<std::uint32_t>(mpEnd - mpBegin);
}

template <typename T>
inline bool Vector<T>::IsEmpty() const
{
	return mpBegin == mpEnd;
}

template<typename T>
inline void Vector<T>::PushBack(const T& data)
{
	if (mpEnd == mpCapacity)
	{
		std::uint32_t capacity = Capacity();
		Reserve(capacity > 0 ? 2 * capacity : 1);
	}

	mpEnd = new (mpEnd) T(data);
	++mpEnd;
}

template<typename T>
inline void Vector<T>::PopBack()
{
	if (IsEmpty())
	{
		throw std::out_of_range("Vector is empty.");
	}

	--mpEnd;
	mpEnd->~T();
}

template<typename T>
inline T & Vector<T>::Front()
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->Front());
}

template<typename T>
inline const T & Vector<T>::Front() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("Vector is empty.");
	}

	return *mpBegin;
}

template<typename T>
inline T & Vector<T>::Back()
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->Back());
}

template<typename T>
inline const T & Vector<T>::Back() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("Vector is empty.");
	}

	return *(mpEnd - 1);
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::begin() const
{
	return Iterator(mpBegin, this);
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::end() const
{
	return Iterator(mpEnd - 1, this);
}

template<typename T>
inline const T & Vector<T>::At(std::uint32_t index) const
{
	return operator[](index);
}

template<typename T>
inline T & Vector<T>::At(std::uint32_t index)
{
	return operator[](index);
}

template<typename T>
inline const T& Vector<T>::operator[](std::uint32_t index) const
{
	if (index >= Size())
	{
		throw std::out_of_range("Out of bounds.");
	}

	return *(mpBegin + index);
}

template<typename T>
inline T& Vector<T>::operator[](std::uint32_t index)
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->operator[](index));
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::Find(const T& data) const
{
	Iterator it = begin(), itEnd = end();

	for (; it != itEnd; ++it)
	{
		if (*it == data)
		{
			break;
		}
	}

	return it;
}

template<typename T>
inline void Vector<T>::Remove(const T& data)
{
	Iterator foundIt = Find(data);

	if (foundIt != end())
	{
		(*foundIt).~T();
		MoveElements(foundIt, foundIt + 1, end() - foundIt + 1);
		--mpEnd;
	}
}

template<typename T>
inline void Vector<T>::Clear()
{
	while (!IsEmpty())
	{
		PopBack();
	}
}

template <typename T>
inline void Vector<T>::Reserve(std::uint32_t capacity)
{
	if (capacity <= 0 || capacity <= Capacity())		return;

	uint32_t size = Size();
	mpBegin = static_cast<T*> (realloc(mpBegin, sizeof(T) * capacity));
	mpEnd = mpBegin + size;
	mpCapacity = mpBegin + capacity;
}

template<typename T>
inline void Vector<T>::MoveElements(Iterator destination, Iterator source, uint32_t count)
{
	memmove(destination.mpCurrent, source.mpCurrent, count * sizeof(T));
}