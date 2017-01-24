#pragma once
#include <cstdint>

template <typename T>
class Vector
{
public:

	Vector();
	Vector(std::uint32_t capacity);

	std::uint32_t	Capacity() const;
	std::uint32_t	Size() const;
	bool			IsEmpty() const;

	void			PushBack(const T& data);
	void			PopBack();

	const T&		operator[](const T& index) const;
	T&				operator[](const T& index);

private:

	// void	Allocate(std::uint32_t capacity);
	void	Reserve(std::uint32_t capacity);

	T*		mpBegin;			/**< Points to the beginning of the vector. */
	T*		mpEnd;				/**< Points to the position after the last element of the vector. */
	T*		mpCapacity;			/**< Pointer to the end of the container. */
};

#include "Vector.inl"
