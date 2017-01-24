#include "Vector.h"
#pragma once

#define DEFAULT_CONTAINER_SIZE 5
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
inline std::uint32_t Vector<T>::Capacity() const
{
	return mpCapacity - mpBegin;
}

template <typename T>
inline std::uint32_t Vector<T>::Size() const
{
	return mpEnd - mpBegin;
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
	if (mpEnd == mpBegin)
	{
		throw std::out_of_range("Vector is empty.");
	}

	--mpEnd;
	mpEnd->~T();
}

template<typename T>
inline const T& Vector<T>::operator[](const T& index) const
{
	return *(mpBegin + index);
}

template<typename T>
inline T& Vector<T>::operator[](const T& index)
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->operator[](index));
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

