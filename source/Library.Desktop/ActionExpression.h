#pragma once
#include "Action.h"
#include "Expression.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	ActionExpression
		*	\brief	This is a base class that computes
		*			an expression at runtime.
		*/
		class ActionExpression : public Action
		{
			RTTI_DECLARATIONS(ActionExpression, Action);

		public:

			/**
			*	\brief				Sets the expression associated
			*						with this action.
			*	\param expression	The expression to set.
			*/
			void					SetExpression(Expression expression);

			/**
			*	\brief				Runs the simulation.
			*	\param worldState	Evalutes the expression contained within.
			*/
			virtual void			Update(WorldState& worldState);

		private:

			Expression				mExpression;		/**< The expression to evaluate. */
		};

#define ActionFactory(ConcreteAction)	ConcreteFactory(Action, ConcreteAction)

	}
}
