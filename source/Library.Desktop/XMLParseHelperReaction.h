#pragma once
#include "IXMLParseHelper.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	XMLParseHelperAction
		*	\brief	A concrete interface that implements IXMLParseHelper.
		*			This will handle Actions.
		*/
		class XMLParseHelperReaction : public IXMLParseHelper
		{
		public:

			/**
			*	\brief				Default constructor. Does nothing.
			*/
									XMLParseHelperReaction() = default;

			/**
			*	\brief				Copy constructor. This operation is not defined,
			*						use Clone() instead.
			*/
									XMLParseHelperReaction(const XMLParseHelperReaction& rhs) = delete;

			/**
			*	\brief				Copy assignment operator. This operation is not defined,
			*						use Clone() instead.
			*/
			XMLParseHelperReaction&	operator=(const XMLParseHelperReaction& rhs) = delete;

			/**
			*	\brief				The handler for the start tag. Creates an Reaction if
			*						the parser is currently immediately inside an Entity.
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
			*	\return				A cloned instance of XMLParseHelperReaction. This has similar,
			*						but not same, state.
			*/
			virtual IXMLParseHelper* Clone() override;
		};
	}
}