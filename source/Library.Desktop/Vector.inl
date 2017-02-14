#include "Vector.h"
#pragma once

template <typename T>
inline Vector<T>::Vector(const std::uint32_t capacity)
	: Vector(BIND_TO_GETCAPACITYFN(&Vector<T>::GetNewCapacity), capacity)
{
}

template<typename T>
inline Vector<T>::Vector(const GetCapacityFn_t& customCapacityFn, const std::int32_t initialCapacity)
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mpCapacity(nullptr)
	, mfnGetCapacity(customCapacityFn)
{
	Reserve(initialCapacity ? initialCapacity : mfnGetCapacity(Size(), Capacity()));
	mpEnd = mpBegin;
}

template<typename T>
inline Vector<T>::Vector(const Vector& rhs)
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mpCapacity(nullptr)
{
	operator=(rhs);
}

template<typename T>
inline Vector<T>::Vector(Vector&& rhs)
	: mpBegin(nullptr)
	, mpEnd(nullptr)
	, mpCapacity(nullptr)
{
	*this = std::move(rhs);
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		Clear();
		Reserve(rhs.Capacity());

		for (auto& value : rhs)
		{
			PushBack(value);
		}
	}

	return *this;
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& rhs)
{
	if (this != &rhs)
	{
		Clear();
		free(mpBegin);

		mpBegin = rhs.mpBegin;
		mpEnd = rhs.mpEnd;
		mpCapacity = rhs.mpCapacity;
		mfnGetCapacity = std::move(rhs.mfnGetCapacity);

		rhs.mpBegin = nullptr;
		rhs.mpEnd = nullptr;
		rhs.mpCapacity = nullptr;
		rhs.mfnGetCapacity = nullptr;
	}

	return *this;
}

template <typename T>
inline Vector<T>::~Vector()
{
	Clear();
	free(mpBegin);
}

template<typename T>
inline bool Vector<T>::operator==(const Vector& rhs) const
{
	if (Size() != rhs.Size())	return false;
	
	Iterator thisIt = begin(), thisEnd = end(), rhsIt = rhs.begin();

	for (; thisIt != thisEnd; ++thisIt, ++rhsIt)
	{
		if (*thisIt != *rhsIt)
		{
			return false;
		}
	}

	return true;
}

template<typename T>
inline bool Vector<T>::operator!=(const Vector& rhs) const
{
	return !(*this == rhs);
}

template <typename T>
inline Vector<T>::Iterator::Iterator()
	: mpCurrent(nullptr)
	, mpOwner(nullptr)
{
}

template<typename T>
inline Vector<T>::Iterator::Iterator(T* element, const Vector<T>* const pOwner)
	: mpCurrent(element)
	, mpOwner(pOwner)
{
}

template<typename T>
inline Vector<T>::Iterator::Iterator(const Iterator& rhs)
{
	operator=(rhs);
}

template<typename T>
inline Vector<T>::Iterator::Iterator(Iterator&& rhs)
{
	*this = std::move(rhs);
}

template<typename T>
inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
{
	if (this != &rhs)
	{
		mpCurrent	= rhs.mpCurrent;
		mpOwner		= rhs.mpOwner;
	}

	return *this;
}

template<typename T>
inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(Iterator&& rhs)
{
	if (this != &rhs)
	{
		mpCurrent = rhs.mpCurrent;
		mpOwner = rhs.mpOwner;

		rhs.mpCurrent = nullptr;
		rhs.mpOwner = nullptr;
	}

	return *this;
}

template <typename T>
inline bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
{
	return mpOwner == rhs.mpOwner && mpCurrent == rhs.mpCurrent;
}

template <typename T>
inline bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
inline bool Vector<T>::Iterator::operator<(const Iterator& rhs) const
{
	if (mpOwner != rhs.mpOwner)
	{
		throw std::invalid_argument("The two iterators do not belong to the same container.");
	}

	return mpCurrent < rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator<=(const Iterator& rhs) const
{
	if (mpOwner != rhs.mpOwner)
	{
		throw std::invalid_argument("The two iterators do not belong to the same container.");
	}

	return mpCurrent <= rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>(const Iterator& rhs) const
{
	if (mpOwner != rhs.mpOwner)
	{
		throw std::invalid_argument("The two iterators do not belong to the same container.");
	}

	return mpCurrent > rhs.mpCurrent;
}

template<typename T>
inline bool Vector<T>::Iterator::operator>=(const Iterator& rhs) const
{
	if (mpOwner != rhs.mpOwner)
	{
		throw std::invalid_argument("The two iterators do not belong to the same container.");
	}

	return mpCurrent >= rhs.mpCurrent;
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+(const std::uint32_t rhs) const
{
	if (mpCurrent == nullptr)
	{
		throw std::out_of_range("Cannot add to iterator pointing to nullptr.");
	}

	return Iterator (mpCurrent + rhs, mpOwner);
}

template<typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-(const std::uint32_t rhs) const
{
	if (mpCurrent == nullptr)
	{
		throw std::out_of_range("Cannot subtract from iterator pointing to nullptr.");
	}

	return Iterator(mpCurrent - rhs, mpOwner);
}

template<typename T>
inline std::int32_t Vector<T>::Iterator::operator-(const Iterator& rhs) const
{
	if (mpOwner != rhs.mpOwner)
	{
		throw std::invalid_argument("The two iterators do not belong to the same container.");
	}

	return static_cast<std::int32_t>(mpCurrent - rhs.mpCurrent);
}

template <typename T>
inline typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
	if (mpCurrent == nullptr)
	{
		throw std::out_of_range("Cannot increment iterator pointing to nullptr.");
	}

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
	if (!mpOwner || mpOwner->IsEmpty() || !mpOwner->IsValid(*this))
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
inline typename Vector<T>::Iterator Vector<T>::PushBack(const T& data)
{
	if (mpEnd == mpCapacity)
	{
		Reserve(mfnGetCapacity(Size(), Capacity()));
	}

	mpEnd = new (mpEnd) T(data);

	return Iterator(mpEnd++, this);
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
inline T& Vector<T>::Front()
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->Front());
}

template<typename T>
inline const T& Vector<T>::Front() const
{
	if (IsEmpty())
	{
		throw std::out_of_range("Vector is empty.");
	}

	return *mpBegin;
}

template<typename T>
inline T& Vector<T>::Back()
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->Back());
}

template<typename T>
inline const T& Vector<T>::Back() const
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
	return Iterator(mpEnd, this);
}

template<typename T>
inline T& Vector<T>::At(const std::uint32_t index)
{
	return operator[](index);
}

template<typename T>
inline const T& Vector<T>::At(const std::uint32_t index) const
{
	return operator[](index);
}

template<typename T>
inline T& Vector<T>::operator[](const std::uint32_t index)
{
	return const_cast<T&>(const_cast<const Vector<T>*>(this)->operator[](index));
}

template<typename T>
inline const T& Vector<T>::operator[](const std::uint32_t index) const
{
	if (index >= Size())
	{
		throw std::out_of_range("Out of bounds.");
	}

	return *(mpBegin + index);
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
		if (foundIt + 1 != end())
		{
			MoveElements(foundIt, foundIt + 1, end() - foundIt + 1);
		}
		--mpEnd;
	}
}

template<typename T>
inline void Vector<T>::Remove(const Iterator& rangeBegin, const Iterator& rangeEnd)
{
	if (!(IsValid(rangeBegin) && IsValid(rangeEnd)) || rangeBegin > rangeEnd)
	{
		throw std::out_of_range("Invalid iterator. Check that both iterators are within array bounds and that rangeBegin is less than rangeEnd.");
	}

	for (Iterator it = rangeBegin; it <= rangeEnd; ++it)
	{
		(*it).~T();
	}

	if (rangeEnd + 1 != end())
	{
		MoveElements(rangeBegin, rangeEnd, end() - rangeEnd);
	}

	mpEnd -= rangeEnd - rangeBegin + 1;
}

template<typename T>
inline void Vector<T>::Clear()
{
	while (!IsEmpty())
	{
		PopBack();
	}
}

template<typename T>
inline void Vector<T>::ShrinkToFit()
{
	Reserve_Internal(Size());
}

template<typename T>
inline bool Vector<T>::IsValid(const Iterator& it) const
{
	return Size() > 0 && it >= begin() && it < end();
}

template<typename T>
inline std::int32_t Vector<T>::GetNewCapacity(const std::uint32_t currentSize, const std::uint32_t currentCapacity) const
{
	currentSize;	// Currently unused in default implementation

	if (currentCapacity == 0)
	{
		return DEFAULT_CONTAINER_CAPACITY;
	}
	else
	{
		return static_cast<std::uint32_t>(currentCapacity * 1.5f);
	}
}

template<typename T>
inline void Vector<T>::Reserve_Internal(const std::uint32_t capacity)
{
	std::uint32_t size = Size();
	mpBegin = static_cast<T*> (realloc(mpBegin, sizeof(T) * capacity));
	mpEnd = mpBegin + size;
	mpCapacity = mpBegin + capacity;
}

template <typename T>
inline void Vector<T>::Reserve(const std::uint32_t capacity)
{
	if (capacity <= 0 || capacity <= Capacity())		return;

	Reserve_Internal(capacity);
}

template<typename T>
inline void Vector<T>::MoveElements(const Iterator& destination, const Iterator& source, const std::uint32_t count)
{
	memmove(destination.mpCurrent, source.mpCurrent, count * sizeof(T));
}