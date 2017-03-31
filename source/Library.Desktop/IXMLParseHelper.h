#pragma once

#include <string>
#include "HashMap.h"
#include "XMLParseMaster.h"

namespace GameEngine
{
	namespace Library
	{
		class SharedData;

		/**
		*	\class	IXMLParseHelper
		*	\brief	The abstract interface to be extended and passed into
		*			XMLParseMaster. It should attempt to handle data
		*			passed into it, and return whether it did or not.
		*/
		class IXMLParseHelper
		{
		protected:
			typedef HashMap<std::string, std::string> HashMapType;

		public:


			/**
			*	\brief				Default constructor. Initializes member variables.
			*/
									IXMLParseHelper();

			/**
			*	\brief				Copy constructor. This operation is not defined,
			*						use Clone() instead.
			*/
									IXMLParseHelper(const IXMLParseHelper& rhs) = delete;
			
			/**
			*	\brief				Copy assignment operator. This operation is not defined,
			*						use Clone() instead.
			*/
			IXMLParseHelper&		operator=(const IXMLParseHelper& rhs) = delete;

			/**
			*	\brief				Called before the parse process begins.
			*	\param sharedData	The SharedData to be associated with this class instance.
			*						The class is not marked initialized if nullptr is passed in.
			*/
			virtual void			Initialize(XMLParseMaster::SharedData* sharedData);

			/**
			*	\brief				Called after the parse process is complete.
			*/
			virtual void			Finalize();

			/**
			*	\brief				The handler for the start tag. It should return true if handled, false otherwise.
			*	\param element		The name of the tag.
			*	\param attributes	A hashmap of Key-Value attributes.
			*	\return				True if this instance handled the call, false otherwise.
			*/
			virtual bool			StartElementHandler(const std::string& element, const HashMapType attributes) = 0;
			
			/**
			*	\brief				The handler for the end tag. It should return true if handled, false otherwise.
			*	\param element		The name of the tag.
			*	\return				True if this instance handled the call, false otherwise.
			*/
			virtual bool			EndElementHandler(const std::string& element) = 0;

			/**
			*	\brief				The handler for the content between the start and end tags.
			*						It should return true if handled, false otherwise.
			*	\param content		The content to be handled.
			*	\param length		The length of the content to be handled.
			*	\return				True if this instance handled the call, false otherwise.
			*/
			virtual bool			CharDataHandler(const char* content, const std::uint32_t length);

			/**
			*	\brief				This is akin to the copy constructor/assignment operator.
			*						However, since you cannot perfectly replicate the internal
			*						state of the parser, we avoid those operators.
			*	\return				A cloned instance of IXMLParseHelper. This has similar behavior
			*						but not similar state.
			*/
			virtual					IXMLParseHelper* Clone() = 0;
			
			/**
			*	\brief				Destructor. Does nothing.
			*/
			virtual					~IXMLParseHelper() = default;

		protected:

			bool							mbIsInitialized;				/**< Flag that stores whether or not this instance's Initialize function has been called with a valid SharedData pointer. */
			XMLParseMaster::SharedData*		mpSharedData;					/**< The SharedData associated with this class instance. */
		};
	}
}