#pragma once
#include "Attributed.h"
#include "Factory.h"

namespace GameEngine
{
	namespace Library
	{
		class WorldState;

		/**
		*	\class	Action
		*	\brief	This is a base class that executes
		*			instructions on the Update method.
		*/
		class Action : public Attributed
		{
			RTTI_DECLARATIONS(Action, Attributed);

		public:

			/**
			*	\brief				Default constructor. Calls Populate.
			*/
									Action();

			/**
			*	\brief				Default destructor. Does nothing.
			*/
			virtual					~Action() = default;
			
			/**
			*	\brief				Returns the name of this Action.
			*	\return				A const string reference to the this
			*						Action's name.
			*/
			const std::string&		Name() const;

			/**
			*	\brief				Sets the name of this Action.
			*	\param name			The name of this Action to set.
			*	\throw std::invalid_argument if name is empty.
			*/
			void					SetName(const std::string& name);

			/**
			*	\brief				Runs the simulation.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			virtual void			Update(WorldState& worldState) = 0;

			/**
			*	\brief				Calls parent Populate and adds Name as an Attribute.
			*/
			virtual void			Populate() override;

		private:

			std::string mName;		/**< The name of this Action. */
		};

#define ActionFactory(ConcreteAction)	ConcreteFactory(Action, ConcreteAction)

	}
}
