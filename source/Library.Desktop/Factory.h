#pragma once

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Factory
		*	\brief	Templated abstract factory implementation. This will group factories based
		*			on a given base type. Concrete factories will register themselves to the
		*			templated static base class. Then, when queried, it will create instances
		*			of these derived classes.
		*/
		template <typename T>
		class Factory
		{
			typedef HashMap<std::string, Factory<T>*> MapType;

		public:

			/**
			*	\brief							Returns the concrete Factory associated with this
			*									name.
			*	\param classname				The name of the class to look for.
			*	\return							The concrete Factory as a base Factory template pointer
			*									if it has been registered, nullptr otherwise.
			*/
			static Factory<T>*					Find(const std::string& classname);

			/**
			*	\brief							Returns an instance of the class from the associated
			*									concrete factory if one exists.
			*	\param classname				The name of the class to look for.
			*	\return							A new instance of the class represented by classname
			*									if an associated factory has been registered, nullptr
			*									otherwise.
			*/
			static T*							Create(const std::string& classname);

			/**
			*	\brief							Returns an iterator to the first concrete factory in
			*									the list of factories registered.
			*	\return							An iterator to the first concrete factory in the list.
			*/
			static typename MapType::Iterator	begin();
			
			/**
			*	\brief							Returns an iterator to the factory after the last one
			*									in the list of factories registered.
			*	\return							An iterator to the factory after the last concrete factory
			*									in the list.
			*/
			static typename MapType::Iterator	end();

		protected:

			/**
			*	\brief							Pure virtual method that is overriden by concrete
			*									factory to return a new instance of the class
			*									associated with that concrete factory.
			*	\return							An instance to the newly created class
			*									in the list, nullptr if no associated factory exists.
			*/
			virtual T*							Create() = 0;

			/**
			*	\brief							Pure virtual method that is overridden by concrete
			*									factory to return the name of the class associated
			*									with that factory.
			*	\return							The name of the class associated with this factory.
			*/
			virtual const std::string&			GetClassName() const = 0;

			/**
			*	\brief							Registers a concrete factory with the abstract factory.
			*	\param factory					The concrete factory to register.
			*/
			static void							Add(Factory<T>& factory);

			/**
			*	\brief							Unregisters a concrete factory from the abstract factory.
			*	\param factory					The concrete factory to unregister.
			*/
			static void							Remove(Factory<T>& factory);

		private:

			static MapType m_sFactoryMap;		/**< The hashmap of class strings mapped to their concrete factories */
		};

#include "Factory.inl"

#define ConcreteFactory(AbstractProductT, ConcreteProductT)								\
		class ConcreteProductT ## Factory final : public Factory<AbstractProductT>		\
		{																				\
		public:																			\
			ConcreteProductT ## Factory()												\
				: mClassName(# ConcreteProductT)			{ Add(*this); }				\
			~ConcreteProductT ## Factory()					{ Remove(*this); }			\
			virtual const std::string& GetClassName() const	{ return mClassName; }		\
			virtual AbstractProductT* Create()											\
			{																			\
				AbstractProductT* product = new ConcreteProductT();						\
				assert(product != nullptr);												\
				return product;															\
			}																			\
		private:																		\
			std::string mClassName;														\
		};																				
	}
}