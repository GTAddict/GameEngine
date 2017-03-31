#pragma once
#include "IXMLParseHelper.h"

namespace GameEngine
{
	namespace Library
	{
		class XMLParseHelperWorld : public IXMLParseHelper
		{
		public:

			/**
			*	\brief				Default constructor. Does nothing.
			*/
									XMLParseHelperWorld() = default;

			/**
			*	\brief				Copy constructor. This operation is not defined,
			*						use Clone() instead.
			*/
									XMLParseHelperWorld(const XMLParseHelperWorld& rhs) = delete;

			/**
			*	\brief				Copy assignment operator. This operation is not defined,
			*						use Clone() instead.
			*/
			XMLParseHelperWorld&	operator=(const XMLParseHelperWorld& rhs) = delete;
			
			/**
			*	\brief				The handler for the start tag. Creates a World if one
			*						does not already exist.
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
			*	\return				A cloned instance of XMLParseHelperWorld. This has similar,
			*						but not same, state.
			*/
			virtual IXMLParseHelper* Clone() override;
		};
	}
}

