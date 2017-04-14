#pragma once

#include "IXMLParseHelper.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		namespace TableParserConstants
		{
			const std::string WORLD_IDENTIFIER			= "world";
			const std::string SECTOR_IDENTIFIER			= "sector";
			const std::string ENTITY_IDENTIFIER			= "entity";

			const std::string ACTION_IDENTIFIER			= "action";
			const std::string REACTION_IDENTIFIER		= "reaction";
			const std::string EXPRESSION_IDENTIFIER		= "expression";

			const std::string INTEGER_IDENTIFIER		= "integer";
			const std::string FLOAT_IDENTIFIER			= "float";
			const std::string VECTOR_IDENTIFIER			= "vector";
			const std::string MATRIX_IDENTIFIER			= "matrix";
			const std::string STRING_IDENTIFIER			= "string";

			const std::string CLASS_IDENTIFIER		= "class";
			const std::string NAME_IDENTIFIER		= "name";
			const std::string VALUE_IDENTIFIER		= "value";
			const std::string INDEX_IDENTIFIER		= "index";
		}

		class Scope;

		/**
		*	\class	XMLParseHelperTable
		*	\brief	A concrete interface that implements IXMLParseHelper.
		*			This will handle ints, floats, matrices,
		*			vectors and strings.
		*/
		class XMLParseHelperTable final : public IXMLParseHelper
		{
		public:

			/**
			*	\class	SharedDataTable
			*	\brief	This the derived class that can be registered to the Parse Master.
			*			This class helps with parsing Scopes and their contained items.
			*/
			class SharedDataTable final : public XMLParseMaster::SharedData
			{
				friend class XMLParseHelperTable;

				RTTI_DECLARATIONS(SharedDataTable, SharedData)

			public:

				/**
				*	\brief			Default constructor. Initializes member variables.
				*/
									SharedDataTable();

				/**
				*	\brief			Copy constructor. This operation is not defined,
				*					use Clone() instead.
				*/
									SharedDataTable(const SharedData& rhs) = delete;

				/**
				*	\brief			Copy assignment operator. This operation is not defined,
				*					use Clone() instead.
				*/
				SharedData&			operator=(const SharedData& rhs) = delete;

				/**
				*	\brief			Destructor. Deletes created Scope.
				*/
									~SharedDataTable() override;
				
				/**
				*	\brief			This is akin to the copy constructor/assignment operator.
				*					However, we avoid those operators.
				*	\return			A cloned instance of SharedDataTable. This has similar,
				*					but not same, state.
				*/
				SharedData*			Clone() const override;

				Scope*				mScope;		/**< The scope being built out of the string passed in. 
														You need to make a copy of this Scope if you want
														retain it, as it gets deleted in the destructor. */
			};

			/**
			*	\brief				The handler for the start tag. Creates a Scope, or a Datum,
			*						depending on the tag passed in.
			*	\param element		The name of the tag.
			*	\param attributes	A hashmap of Key-Value attributes.
			*	\return				True if this instance handled the call, false otherwise.
			*/
			bool					StartElementHandler(const std::string& element, const HashMapType attributes) override;

			/**
			*	\brief				The handler for the end tag.
			*	\param element		The name of the tag.
			*	\return				True if this instance handled the call, false otherwise.
			*/
			bool					EndElementHandler(const std::string& element) override;

			/**
			*	\brief				This is akin to the copy constructor/assignment operator.
			*						However, we avoid those operators.
			*	\return				A cloned instance of XMLParseHelperTable. This has similar,
			*						but not same, state.
			*/
			virtual IXMLParseHelper* Clone() override;

		private:

			/**
			*	\brief				Helper function that Appends data to scopes, sets their types
			*						and sets their data.
			*	\param sharedData	The Shared Data to add the scope to.
			*	\param type			The type of the Datum to Append. We're casting to an int to pass to this
			*						function and then casting it back to Datum::DatumType because we want
			*						avoid a Datum dependency in this header (XMLParseHelperTable.h).
			*	\param attributes	The hashmap of Key-Value attributes.
			*	\return				True if the process was completed successfully, false otherwise.
			*/
			bool					PopulateDatum(SharedDataTable* sharedData, std::int32_t type, const HashMapType attributes);
		};
	}
}