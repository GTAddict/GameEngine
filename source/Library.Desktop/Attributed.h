#pragma once
#include "Scope.h"
#include "RTTI.h"

#define PRTTI_CAST(x)	static_cast<RTTI*>(x)
#define PSCOPE_CAST(x)	static_cast<Scope*>(x)

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Attributed
		*	\brief	Mirrors native data and makes it accessible through
		*			text, thus making it available for scripting.
		*/
		class Attributed : public Scope
		{
			RTTI_DECLARATIONS(Attributed, Scope);

		public:

			/**
			*	\brief			Default constructor. Adds "this" as a prescribed attribute.
			*/
								Attributed();

			/**
			*	\brief			Destructor. Clears the hashmap when no class instances are left.
			*/
			virtual				~Attributed() override;

			/**
			*	\brief			Copy constructor. Deep copies the Attributed provided into itself.
			*					This will copy all Scope data. 
			*	\param rhs		The Attributed to copy from.
			*/
								Attributed(const Attributed& rhs);

			/**
			*	\brief			Move constructor. Transfers ownership of the data to itself.
			*	\param rhs		The Attributed to move data from.
			*/
								Attributed(Attributed&& rhs);

			/**
			*	\brief			Copy assignment operator. Deep copies the Attributed provided into itself.
			*					This will copy all Scope data.
			*	\param rhs		The Attributed to copy from.
			*	\return			A reference to the Attributed assigned to.
			*/
			Attributed&			operator=(const Attributed& rhs);

			/**
			*	\brief			Move assignment operator. Transfers ownership of the data to itself.
			*	\param rhs		The Attributed to move data from.
			*	\return			A reference to the Attributed assigned to.
			*/
			Attributed&			operator=(Attributed&& rhs);

			/**
			*	\brief			Checks whether the given name is a prescribed attribute of the class.
			*	\param name		The name of the attribute to check.
			*	\return			Whether there is a prescribed attribute of given name in the class.
			*/
			bool				IsPrescribedAttribute(const std::string& name) const;

			/**
			*	\brief			Checks whether the given name is an auxiliary attribute of the class instance.
			*	\param name		The name of the attribute to check.
			*	\return			Whether there is an auxiliary attribute of given name in the class instance.
			*/
			bool				IsAuxiliaryAttribute(const std::string& name) const;

			/**
			*	\brief			Checks whether the given name is an attribute of the class or class instance.
			*	\param name		The name of the attribute to check.
			*	\return			Whether there is an attribute of given name in the class or the class instance.
			*/
			bool				IsAttribute(const std::string& name) const;

			/**
			*	\brief			Adds the specified attribute into the Scope. Adds it to the list of attributes.
			*	\param name		The name of the entry to be created.
			*	\param data		The data value to add associate the name with.
			*	\return			A pointer to the new Datum created or the associated Datum if one already exists.
			*					nullptr if an entry with name already exists.
			*	\throw std::runtime_error if data is nullptr.
			*/
			template <typename T>
			Datum*				AddPrescribedAttributeInternal(const std::string& name, const T& data);
			
			/**
			*	\brief			Adds the specified attribute array into the Scope. Adds it to the list of attributes.
			*	\param name		The name of the entry to be created.
			*	\param data		The data values to add associate the name with.
			*	\param size		The size of the data value array passed in.
			*	\return			A pointer to the new Datum created or the associated Datum if one already exists.
			*					nullptr if an entry with name already exists.
			*	\throw std::runtime_error if data is nullptr.
			*/
			template <typename T>
			Datum*				AddPrescribedAttributeInternal(const std::string& name, const T* data, const std::uint32_t size);

			/**
			*	\brief			Appends a new datum and sets its type. Adds it to the prescribed attribute list.
			*	\param name		The name of the entry to be created.
			*	\param type		The type to set the newly created Datum to.
			*	\return			A pointer to the new Datum created or the associated Datum if one already exists.
			*					nullptr if an entry with name already exists.
			*/
			Datum*				AddPrescribedAttributeInternalWithType(const std::string& name, const Datum::DatumType type);

			/**
			*	\brief			Adds the specified attribute into the Scope. Adds it to the list of attributes.
			*	\param name		The name of the entry to be created.
			*	\param data		The external storage to associate the name with.
			*	\return			A pointer to the new Datum created or the associated Datum if one already exists.
			*					nullptr if an entry with name already exists.
			*	\throw std::runtime_error if data is nullptr.
			*/
			template <typename T>
			Datum*				AddPrescribedAttributeExternal(const std::string& name, const T& data);
			
			/**
			*	\brief			Adds the specified attribute array into the Scope. Adds it to the list of attributes.
			*	\param name		The name of the entry to be created.
			*	\param data		The external storage array to add associate the name with.
			*	\param size		The size of the external storage passed in.
			*	\return			A pointer to the new Datum created or the associated Datum if one already exists.
			*					nullptr if an entry with name already exists.
			*	\throw std::runtime_error if data is nullptr.
			*/
			template <typename T>
			Datum*				AddPrescribedAttributeExternal(const std::string& name, const T* data, const std::uint32_t size);

			/**
			*	\brief			Appends the specified name into Scope.
			*	\param name		The name of the entry to be created.
			*	\return			The new Scope created or the associated Scope if one already exists.
			*/
			Scope*				AddNestedScope(const std::string& name);

			/**
			*	\brief			Adopts the specified scope into the entry specified by name.
			*	\param name		The name under which the passed in Scope should be adopted.
			*	\param scope	The Scope to adopt.
			*/
			void				AddNestedScope(const std::string& name, Scope* scope);
			
			/**
			*	\brief			Adds the specified attribute into the Scope. Adds it to the list of attributes.
			*	\param name		The name of the entry to be created.
			*	\return			A references to the new Datum created or the associated Datum if one already exists.
			*	\throw std::invalid_argument if name matches an already existing attribute.
			*/
			Datum&				AppendAuxiliaryAttribute(const std::string& name);

		private:

			static HashMap<std::uint64_t, HashMap<std::string, Datum>>	s_mPrescribedAttributes;		/**< A static HashMap of all the prescribed attributes per class type. */
			static std::uint32_t mInstanceCount;														/**< Holds current class instance count. */
		};

#include "Attributed.inl"

	}
}