#pragma once
#include "Action.h"

namespace GameEngine
{
	namespace Library
	{
		/**
		*	\class	ActionList
		*	\brief	This is a base Action class
		*			that contains other Actions.
		*/
		class ActionList : public Action
		{
			RTTI_DECLARATIONS(ActionList, Action);

		public:

			/**
			*	\brief				Default constructor. Calls populate.
			*/
									ActionList();

			/**
			*	\brief				Default destructor. Does nothing.
			*/
			virtual					~ActionList() = default;

			/**
			*	\brief				Adopts the provided Action into the Actions table.
			*	\param				The Action to be adopted.
			*/
			void					AdoptAction(Action& action);

			/**
			*	\brief				Runs the simulation.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState) override;

			/**
			*	\brief				Calls the Parent Populate and adds a table
			*						of Actions as an Attribute.
			*/
			void					Populate() override;

		private:

			Datum*	mpActions;		/**< The cached table of contained Actions. */
		};

	}
}
