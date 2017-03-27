#include "Factory.h"

template <typename T>
typename GameEngine::Library::Factory<T>::MapType GameEngine::Library::Factory<T>::m_sFactoryMap;

template <typename T>
inline GameEngine::Library::Factory<T>* Factory<T>::Find(const std::string& classname)
{
	auto it = m_sFactoryMap.Find(classname);
	if (it != m_sFactoryMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

template<typename T>
inline T* GameEngine::Library::Factory<T>::Create(const std::string& classname)
{
	auto factory = Find(classname);
	if (factory != nullptr)
	{
		return factory->Create();
	}
	return nullptr;
}

template <typename T>
inline void GameEngine::Library::Factory<T>::Add(Factory<T>* factory)
{
	assert(factory != nullptr);
	m_sFactoryMap[factory->GetClassName()] = factory;
}

template <typename T>
inline void GameEngine::Library::Factory<T>::Remove(Factory<T>* factory)
{
	assert(factory != nullptr);
	m_sFactoryMap.Remove(factory->GetClassName());
}
		
template<typename T>
inline typename GameEngine::Library::Factory<T>::MapType::Iterator Factory<T>::begin() const
{
	return m_sFactoryMap.begin();
}

template<typename T>
inline typename GameEngine::Library::Factory<T>::MapType::Iterator Factory<T>::end() const
{
	return m_sFactoryMap.end();
}