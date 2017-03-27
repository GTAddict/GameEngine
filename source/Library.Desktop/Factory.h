#pragma once

namespace GameEngine
{
	namespace Library
	{
		template <typename T>
		class Factory
		{
		public:

			typedef HashMap<std::string, Factory<T>*> MapType;

			static Factory<T>* Find(const std::string& classname);
			static T* Create(const std::string& classname);

			static void Add(Factory<T>* factory);
			static void Remove(Factory<T>* factory);

			virtual T* Create()	= 0;
			virtual std::string GetClassName() const = 0;

			typename MapType::Iterator begin()	const;
			typename MapType::Iterator end()		const;

		private:
			static MapType m_sFactoryMap;
		};

#include "Factory.inl"

#define ConcreteFactory(AbstractProductT, ConcreteProductT)								\
		class ConcreteProductT ## Factory : public Factory<AbstractProductT>					\
		{																				\
		public:																			\
			ConcreteProductT ## Factory()				{ Add(this); }					\
			~ConcreteProductT ## Factory()				{ Remove(this); }				\
			virtual std::string GetClassName() const	{ return # ConcreteProductT; }	\
			virtual AbstractProductT* Create()											\
			{																			\
				AbstractProductT* product = new ConcreteProductT();						\
				assert(product != nullptr);												\
				return product;															\
			}																			\
		};																				
	}
}