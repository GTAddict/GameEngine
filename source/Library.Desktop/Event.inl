template <typename T> RTTI_DEFINITIONS(GameEngine::Library::Event<T>);
template <typename T> Vector<EventSubscriber*> Event<T>::mSubscribers;
template <typename T> std::mutex Event<T>::mSubscribersLock;

template <typename T>
inline GameEngine::Library::Event<T>::Event(const T& message)
	: EventPublisher(mSubscribers, mSubscribersLock)
	, mMessage(message)
{
}

template <typename T>
inline void GameEngine::Library::Event<T>::Subscribe(EventSubscriber& subscriber)
{
	_CRITICAL(mSubscribersLock)
	assert(mSubscribers.Find(&subscriber) == mSubscribers.end());
	mSubscribers.PushBack(&subscriber);
	_CRITICAL_END
}

template<typename T>
inline void GameEngine::Library::Event<T>::Unsubscribe(EventSubscriber& subscriber)
{
	_CRITICAL(mSubscribersLock)
	assert(mSubscribers.Find(&subscriber) != mSubscribers.end());
	mSubscribers.Remove(&subscriber);
	_CRITICAL_END
}

template<typename T>
inline void GameEngine::Library::Event<T>::UnsubscribeAll()
{
	_CRITICAL(mSubscribersLock)
	mSubscribers.Clear();
	_CRITICAL_END
}

template<typename T>
inline const T& GameEngine::Library::Event<T>::Message() const
{
	return mMessage;
}

template<typename T>
inline T& GameEngine::Library::Event<T>::Message()
{
	return mMessage;
}