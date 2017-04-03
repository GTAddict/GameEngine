template <typename T>
inline GameEngine::Library::Stack<T>::Stack()
	: mContainer()
{
}

template <typename T>
inline GameEngine::Library::Stack<T>::Stack(const Vector<T>& container)
	: mContainer(container)
{
}

template <typename T>
inline GameEngine::Library::Stack<T>::Stack(const Stack& rhs)
	: mContainer(rhs.mContainer)
{
}

template <typename T>
inline GameEngine::Library::Stack<T>::Stack(Stack&& rhs)
	: mContainer(std::move(rhs.mContainer))
{
}

template <typename T>
inline GameEngine::Library::Stack<T>& GameEngine::Library::Stack<T>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		mContainer = rhs.mContainer;
	}

	return *this;
}

template <typename T>
inline GameEngine::Library::Stack<T>& GameEngine::Library::Stack<T>::operator=(Stack&& rhs)
{
	if (this != &rhs)
	{
		mContainer = std::move(rhs.mContainer);
	}

	return *this;
}

template <typename T>
inline bool GameEngine::Library::Stack<T>::operator==(const Stack& rhs) const
{
	return mContainer == rhs.mContainer;
}

template <typename T>
inline bool GameEngine::Library::Stack<T>::operator!=(const Stack& rhs) const
{
	return !(*this == rhs);
}

template <typename T>
inline std::uint32_t GameEngine::Library::Stack<T>::Size() const
{
	return mContainer.Size();
}

template <typename T>
inline bool GameEngine::Library::Stack<T>::IsEmpty() const
{
	return mContainer.IsEmpty();
}

template <typename T>
inline void GameEngine::Library::Stack<T>::Push(const T& data)
{
	mContainer.PushBack(data);
}

template <typename T>
inline void GameEngine::Library::Stack<T>::Pop()
{
	mContainer.PopBack();
}

template <typename T>
inline T& GameEngine::Library::Stack<T>::Top()
{
	return mContainer.Back();
}

template <typename T>
inline const T& GameEngine::Library::Stack<T>::Top() const
{
	return mContainer.Back();
}