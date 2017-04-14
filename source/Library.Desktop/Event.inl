template <typename T>
RTTI_DEFINITIONS(GameEngine::Library::Event<T>);

template <typename T>
Vector<EventSubscriber*> Event<T>::mSubscribers;

template <typename T>
inline GameEngine::Library::Event<T>::Event(const T& message, bool deleteAfterPublishing)
	: EventPublisher(mSubscribers, deleteAfterPublishing)
	, mMessage(message)
{
}

template <typename T>
inline void GameEngine::Library::Event<T>::Subscribe(EventSubscriber& subscriber)
{
	assert(mSubscribers.Find(&subscriber) == mSubscribers.end());
	mSubscribers.PushBack(&subscriber);
}

template<typename T>
inline void GameEngine::Library::Event<T>::Unsubscribe(EventSubscriber& subscriber)
{
	assert(mSubscribers.Find(&subscriber) != mSubscribers.end());
	mSubscribers.Remove(&subscriber);
}

template<typename T>
inline void GameEngine::Library::Event<T>::UnsubscribeAll()
{
	mSubscribers.Clear();
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