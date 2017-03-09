#pragma once
#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"
#include "RTTI.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	Scope
		*	\brief	Scope is a table of String-Datum pairs. The Datum
		*			itself can contain any type of data, including
		*			more Scopes.
		*/
		class Scope : public RTTI
		{
			typedef			std::pair<std::string, Datum>		ElementType;
			typedef			Vector<ElementType*>				VectorType;
			typedef			HashMap<std::string, Datum>			HashMapType;
			static const	std::uint32_t						DEFAULT_SIZE = 10;

			RTTI_DECLARATIONS(Scope, RTTI);

		public:

			/**
			*	\brief				Default constructor. You can specify the Vector size
			*						to reserve, i.e. the number of entries in the Scope
			*						if you know it.
			*/
			explicit				Scope(const std::uint32_t size = DEFAULT_SIZE);

			/**
			*	\brief				Copy constructor. Deep copies the Scope provided into itself.
			*						This will copy all Datum data. If it encounters Scope pointers,
			*						it will allocate memory and copy its internal data.
			*	\param rhs			The Scope to copy from.
			*/
									Scope(const Scope& rhs);

			/**
			*	\brief				Move constructor. Transfers ownership of the data to itself.
			*	\param rhs			The Scope to move data from.
			*/
									Scope(Scope&& rhs);
									
			/**
			*	\brief				Copy assignment operator. Deep copies the Scope provided into itself.
			*						This will copy all Datum data. If it encounters Scope pointers,
			*						it will allocate memory and copy its internal data.
			*	\param rhs			The Scope to copy from.
			*	\return				A reference to the Scope assigned to.
			*	\throw std::runtime_error if it tries to copy into a Datum a type that is not.
			*/
			Scope&					operator=(const Scope& rhs);

			/**
			*	\brief				Move assignment operator. Transfers ownership of the data to itself.
			*	\param rhs			The Scope to move data from.
			*	\return				A reference to the Scope assigned to.
			*/
			Scope&					operator=(Scope&& rhs);

			/**
			*	\brief				Destructor. Clears all elements and frees memory.
			*/
			virtual					~Scope();

			/**
			*	\brief				Equality operator. Checks whether the two operands are equal.
			*	\param rhs			The Scope to compare to.
			*	\return				True if the two Scopes are equal, false otherwise.
			*/
			bool					operator==(const Scope& rhs) const;

			/**
			*	\brief				Inequality operator. Checks whether the two operands are unequal.
			*	\param rhs			The Datum to compare to.
			*	\return				True if the two Datums are unequal, false otherwise.
			*/
			bool					operator!=(const Scope& rhs) const;
			
			/**
			*	\brief				Returns a reference to the Datum with the specified name.
			*						If no entry is found, one is created.
			*	\param name			The name whose Datum to retrieve.
			*	\return				A non-const reference to the Datum with the specified name.
			*/
			Datum&					operator[](const std::string& name);

			/**
			*	\brief				Returns a reference to the Datum inserted in the specified order number.
			*	\param index		The order number at which the Datum was inserted.
			*	\return				A non-const reference to the Datum with the specified insert order number.
			*/
			Datum&					operator[](const std::uint32_t index);

			/**
			*	\brief				Returns a reference to the Datum with the specified name.
			*	\param name			The name whose Datum to retrieve.
			*	\return				A const reference to the Datum with the specified name.
			*	\throw std::out_of_range if an invalid name is specified.
			*/
			const Datum&			operator[](const std::string& name) const;

			/**
			*	\brief				Returns a reference to the Datum inserted in the specified order number.
			*	\param index		The order number at which the Datum was inserted.
			*	\return				A const reference to the Datum with the specified insert order number.
			*/
			const Datum&			operator[](const std::uint32_t index) const;

			/**
			*	\brief				Returns a pointer to the Datum with the specified name contained within
			*						the current scope.
			*	\param name			The name to search for.
			*	\return				A pointer to the Datum with the specified name if it exists, nullptr otherwise.
			*/
			Datum*					Find(const std::string& name) const;

			/**
			*	\brief				Returns a pointer to the first occurrence of the Datum with the specified name
			*						contained within the current scope or any parent Scopes.
			*	\param name			The name to search for.
			*	\param outScope		The scope the Datum was found in if at all, nullptr otherwise.
			*	\return				A pointer to the Datum with the specified name if it exists, nullptr otherwise.
			*/
			Datum*					Search(const std::string& name, Scope** outScope = nullptr);
			
			/**
			*	\brief				Adds a new String-Datum pair into the current table.
			*	\param name			The name to add into the current Scope.
			*	\return				A reference to the newly created datum.
			*/
			Datum&					Append(const std::string& name);

			/**
			*	\brief				Adds a new String-Scope pair into the current table.
			*	\param name			The name to add into the current Scope.
			*	\param scope		If passed in, a new scope will not be created on the
			*						heap, rather the scope passed in will be appended.
			*	\return				A reference to the newly created scope.
			*/
			Scope&					AppendScope(const std::string& name, Scope* scope = nullptr);

			/**
			*	\brief				Returns the parent of the Scope, i.e. the Scope containing
			*						the Datum housing the Scope.
			*	\return				A pointer to the parent of the Scope.
			*/
			Scope*					GetParent() const;

			/**
			*	\brief				Finds the name of the Datum containing the Scope in the
			*						current Scope.
			*	\param scope		The Scope whose name is to be found.
			*	\return				The name of the Scope passed in.
			*/
			std::string				FindName(const Scope& scope) const;

			/**
			*	\brief				Orphans the Scope from its parent and adds it to itself.
			*	\param child		The Scope to Adopt.
			*	\param name			The name under which to Adopt.
			*/
			void					Adopt(Scope& child, const std::string& name);

			/**
			*	\brief				Removes all elements, calls destructors, and recursively
			*						deletes all Scopes.
			*/
			void					Clear();

		private:

			/**
			*	\brief				Un-childs itself from its parent by looking through its parent
			*						table for its entry, removing it, and marking its parent as nullptr.
			*/
			void					Orphan();

			VectorType				mVector;			//*< The internal Vector used to keep track of the insertion order of Datums. */
			HashMapType				mHashMap;			//*< The internal Vector used to keep track of the table i.e. Scope. */
			Scope*					mpParent;			//*< The parent of this Scope. */
		};
	}
}