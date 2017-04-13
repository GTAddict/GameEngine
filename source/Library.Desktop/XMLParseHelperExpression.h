#pragma once
#include "IXMLParseHelper.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	XMLParseHelperExpression
		*	\brief	A concrete interface that implements IXMLParseHelper.
		*			This will handle Expressions once inside an Action.
		*/
		class XMLParseHelperExpression : public IXMLParseHelper
		{
		public:

			/**
			*	\brief					Default constructor. Does nothing.
			*/
										XMLParseHelperExpression() = default;

			/**
			*	\brief					Copy constructor. This operation is not defined,
			*							use Clone() instead.
			*/
										XMLParseHelperExpression(const XMLParseHelperExpression& rhs) = delete;

			/**
			*	\brief					Copy assignment operator. This operation is not defined,
			*							use Clone() instead.
			*/
			XMLParseHelperExpression&	operator=(const XMLParseHelperExpression& rhs) = delete;

			/**
			*	\brief					The handler for the start tag. Creates an Expression if
			*							the parser is currently immediately inside an ActionExpression.
			*	\param element			The name of the tag.
			*	\param attributes		A hashmap of Key-Value attributes.
			*	\return					True if this instance handled the call, false otherwise.
			*/
			bool						StartElementHandler(const std::string& element, const HashMapType attributes) override;

			/**
			*	\brief					The handler for the end tag.
			*	\param element			The name of the tag.
			*	\return					True if this instance handled the call, false otherwise.
			*/
			bool						EndElementHandler(const std::string& element) override;

			/**
			*	\brief					This is akin to the copy constructor/assignment operator.
			*							However, we avoid those operators.
			*	\return					A cloned instance of XMLParseHelperExpression. This has similar,
			*							but not same, state.
			*/
			virtual IXMLParseHelper*	Clone() override;
		};
	}
}