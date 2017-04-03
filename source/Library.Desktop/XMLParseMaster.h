#pragma once
#include "SList.h"
#include "RTTI.h"
#include <cstdint>
#include <string>

// Forward declarations to avoid including
// expat in the header
struct XML_ParserStruct;
typedef struct XML_ParserStruct *XML_Parser;


namespace GameEngine
{
	namespace Library
	{
		class IXMLParseHelper;
		
		/**
		*	\class	XMLParseMaster
		*	\brief	Implements the chain of responsibility pattern for
		*			XML files to be parsed. Reads the file and passes
		*			callbacks from the Expat library on to each helper
		*			registered with the Master.
		*/
		class XMLParseMaster final
		{

		public:

			/**
			*	\class	SharedData
			*	\brief	This is a base class that is shared between all the helpers
			*			and the master. It can be derived from and customized by each
			*			helper, and should be embedded in its respective helper class.
			*/
			class SharedData : public RTTI
			{
				RTTI_DECLARATIONS(SharedData, RTTI);

			public:

				/**
				*	\brief			Default constructor. Initializes member variables.
				*/
									SharedData();

				/**
				*	\brief			Copy constructor. This operation is not defined,
				*					use Clone() instead.
				*/
									SharedData(const SharedData& rhs) = delete;

				/**
				*	\brief			Copy assignment operator. This operation is not defined,
				*					use Clone() instead.
				*/
				SharedData&			operator=(const SharedData& rhs) = delete;

				/**
				*	\brief			This is akin to the copy constructor/assignment operator.
				*					However, we avoid those operators.
				*	\return			A cloned instance of SharedData. This has similar, but not
				*					same, state.
				*/
				virtual				SharedData* Clone() const = 0;

				/**
				*	\brief			This sets the XMLParseMaster associated with this SharedData.
				*	\param parseMaster This is the XMLParseMaster to associated this SharedData with.
				*/
				void				SetXMLParseMaster(XMLParseMaster* parseMaster);

				/**
				*	\brief			This gets the XMLParseMaster associated with this SharedData.
				*	\return			Returns the XMLParseMaster associated with this SharedData.
				*/
				XMLParseMaster*		GetXMLParseMaster() const;

				/**
				*	\brief			This increases the current "depth" or "indentation" of the parse.
				*/
				void				IncrementDepth();

				/**
				*	\brief			This decreases the current "depth" or "indentation" of the parse.
				*/
				void				DecrementDepth();

				/**
				*	\brief			This returns the current "depth" or "indentation" of the parse.
				*	\return			The current depth of the parse.
				*/
				std::uint32_t		GetDepth() const;

			private:

				XMLParseMaster*		mpParseMaster;							/**< The XMLParseMaster associated with this SharedData. */
				std::uint32_t		mDepth;									/**< The current depth of the parse. */
			};

			/**
			*	\brief				Default constructor. Sets the shared data and creates the parser.
			*	\param data			The SharedData associated with this XMLParseMaster.
			*/
			explicit				XMLParseMaster(SharedData* data);

			/**
			*	\brief				Copy constructor. This operation is not defined,
			*						use Clone() instead.
			*/
									XMLParseMaster(const XMLParseMaster& rhs) = delete;

			/**
			*	\brief				Move constructor. This operation is not defined.
			*/
									XMLParseMaster(XMLParseMaster&& rhs) = delete;

			/**
			*	\brief				Copy assignment operator. This operation is not defined,
			*						use Clone() instead.
			*/
			XMLParseMaster&			operator=(const XMLParseMaster& rhs) = delete;

			/**
			*	\brief				Move assignment operator. This operation is not defined.
			*/
			XMLParseMaster&			operator=(XMLParseMaster&& rhs) = delete;

			/**
			*	\brief				Destructor. Destroys the parser and deletes any cloned helpers and
			*						shared data. Does not touch helpers and shared data that is not cloned.
			*/
									~XMLParseMaster();

			/**
			*	\brief				This is akin to the copy constructor/assignment operator.
			*						However, since you cannot perfectly replicate the internal
			*						state of the parser, we avoid those operators. Clones helpers
			*						and SharedData as well, thus allocating memory.
			*	\return				A cloned instance of SharedData. This has similar behavior
			*						but not similar state.
			*/
			virtual XMLParseMaster*	Clone() const;

			/**
			*	\brief				Adds helpers to this class, adding on to the chain in the
			*						chain of responsibility pattern.
			*	\param helper		The helper to add.
			*/
			void					AddHelper(IXMLParseHelper* helper);

			/**
			*	\brief				Removes helpers from this class, removing it from the chain in
			*						the chain of responsibility pattern.
			*	\param helper		The helper to remove.
			*/
			void					RemoveHelper(IXMLParseHelper* helper);

			/**
			*	\brief				Calls the XML_Parse function from Expat.
			*	\param data			The buffer to parse.
			*	\param length		The length of the passed in buffer.
			*	\param isFinal		Denotes whether this is the last chunk passed in.
			*/
			void					Parse(const char* data, const std::uint32_t length, bool isInitial, bool isFinal);

			/**
			*	\brief				Opens a file, allocates a buffer, reads it in and calls Parse.
			*						Basically a wrapper to Parse with File I/O.
			*	\param filename		The name of the file to read in and parse.
			*/
			void					ParseFromFile(const std::string& filename);

			/**
			*	\brief				Returns the name of the file currently being parsed.
			*	\return				A reference to the name of the file currently being parsed.
			*/
			const std::string&		GetFileName() const;

			/**
			*	\brief				Returns the SharedData associated with this instance.
			*	\return				The SharedData associated with this class instance.
			*/
			SharedData*				GetSharedData() const;

			/**
			*	\brief				Sets the SharedData associated with this instance. This in turn
			*						will set the data's XMLParseMaster association to this instance.
			*	\param data			The SharedDatat to be associated with this instance.
			*/
			void					SetSharedData(SharedData* data);

			/**
			*	\brief				Returns the list of helpers added.
			*	\return				The list of helpers added to this instance.
			*/
			const SList<IXMLParseHelper*>&	GetHelperList();

		private:

			/**
			*	\brief				Resets the state of the parser and registers its callbacks.
			*/
			void					ResetParser();

			/**
			*	\brief				The static callback Expat should call on finding a start tag.
			*	\param data			We set Expat to pass back an XMLParseMaster as the first argument as a void*.
			*	\param element		The name of the parsed tag.
			*	\param attribute	A vector of strings of the attributes contained in this tag.
			*/
			static void				StartElementHandler(void* data, const char* element, const char** attribute);
			
			/**
			*	\brief				The static callback Expat should call on finding an end tag.
			*	\param data			We set Expat to pass back an XMLParseMaster as the first argument as a void*.
			*	\param element		The name of the parsed tag.
			*/
			static void				EndElementHandler(void* data, const char* element);

			/**
			*	\brief				The static callback Expat should call on finding content between a start and end tag.
			*	\param data			We set Expat to pass back an XMLParseMaster as the first argument as a void*.
			*	\param content		The string found in between the tags.
			*	\param length		The length of the content found.
			*/
			static void				CharDataHandler(void* data, const char* content, int length);

			SList<IXMLParseHelper*>	mHelperList;							/**< The list of helpers added to implement chain of responsibility. */
			SharedData*				mpSharedData;							/**< The SharedData associated with this class instance. */
			std::string				mFileName;								/**< The filename of the current file being parsed. */
			XML_Parser				mParser;								/**< The Expat parser instance used in the parsing process. */
			bool					mIsClone;								/**< Stores whether or not this instance is a clone, so that it can delete memory. */
		};
	}
}