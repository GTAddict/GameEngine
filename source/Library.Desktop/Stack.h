#pragma once
#include "Vector.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Stack
		*	\brief	Templated Stack implementation. Uses a Vector as the underlying
		*			implementation.
		*/
		template <typename T>
		class Stack final
		{
		public:

			/**
			*	\brief				Default constructor, uses default Vector construction.
			*/
									Stack();

			/**
			*	\brief				Parametrized constructor. You can pass in the Vector container to use.
			*	\param capacity		Capacity to reserve.
			*/
			explicit				Stack(const Vector<T>& container);

			/**
			*	\brief				Copy constructor. Deep copies the Stack provided into itself.
			*	\param rhs			The Stack to copy from.
			*/
									Stack(const Stack& rhs);

			/**
			*	\brief				Move constructor. Transfers ownership of the list to itself.
			*	\param rhs			The Stack to move data from.
			*/
									Stack(Stack&& rhs);

			/**
			*	\brief				Copy assignment operator. Deep copies the Stack provided into itself.
			*	\param rhs			The Stack to copy from.
			*	\return				A reference to this newly created Stack.
			*/
			Stack&					operator=(const Stack& rhs);

			/**
			*	\brief				Move assignment operator. Transfers ownership of the list to itself.
			*	\param rhs			The Stack to move data from.
			*	\return				A reference to this newly created Stack.
			*/
			Stack&					operator=(Stack&& rhs);

			/**
			*	\brief				Equality operator. Checks whether the two operands are equal.
			*	\param rhs			The Stack to compare to.
			*	\return				True if the two Stacks are equal, false otherwise.
			*/
			bool					operator==(const Stack& rhs) const;

			/**
			*	\brief				Inequality operator. Checks whether the two operands are unequal.
			*	\param rhs			The Stack to compare to.
			*	\return				True if the two Stacks are unequal, false otherwise.
			*/
			bool					operator!=(const Stack& rhs) const;

			/**
			*	\brief				Returns number of elements currently stored in the container.
			*	\return				Number of elements in the container.
			*/
			std::uint32_t			Size() const;

			/**
			*	\brief				Returns whether the stack is empty.
			*	\return				Whether the container is empty.
			*/
			bool					IsEmpty() const;

			/**
			*	\brief				Inserts an element at the top of the container.
			*	\param data			The data to be inserted.
			*/
			void					Push(const T& data);

			/**
			*	\brief				Removes the element at the top of the container, and calls its destructor.
			*	\throw std::out_of_range if the container is empty.
			*/
			void					Pop();

			/**
			*	\brief				Returns the element at the top of the container.
			*	\return				A non-const reference to the data at the top of the container.
			*	\throw std::out_of_range if the container is empty.
			*/
			T&						Top();

			/**
			*	\brief				Returns the element at the top of the container.
			*	\return				A const reference to the data at the top of the container.
			*	\throw std::out_of_range if the container is empty.
			*/
			const T&				Top() const;

		private:

			Vector<T> mContainer;	/**< The contained vector the stack operations are passed through to. */
		};

#include "Stack.inl"

	}
}

