#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Sector;
		class WorldState;
		class Action;
		class Reaction;

		/**
		*	\class	Entity
		*	\brief	This is a base class that automatically
		*			populates its Scope. It is contained
		*			within a Sector.
		*/
		class Entity : public Attributed
		{
			RTTI_DECLARATIONS(Entity, Attributed);

		public:

			/**
			*	\brief				Default constructor. Adds Name as an
			*						Attribute.
			*/
									Entity();

			/**
			*	\brief				Copy constructor. Entity is non-copyable.
			*/
									Entity(const Entity& rhs) = delete;

			/**
			*	\brief				Move constructor.
			*/
									Entity(Entity&& rhs);

			/**
			*	\brief				Copy assignment operator. Entity is
			*						non-copyable.
			*/
			Entity&					operator=(const Entity& rhs) = delete;

			/**
			*	\brief				Move assignment operator.
			*	\return				A reference to this Entity.
			*/
			Entity&					operator=(Entity&& rhs);

			/**
			*	\brief				Default destructor. Does nothing.
			*/
			virtual					~Entity() = default;

			/**
			*	\brief				Returns the name of this Entity.
			*	\return				A const string reference to the this
			*						Entity's name.
			*/
			const std::string&		Name() const;

			/**
			*	\brief				Sets the name of this Entity.
			*	\param name			The name of this Entity to set.
			*	\throw std::invalid_argument if name is empty.
			*/
			void					SetName(const std::string& name);

			/**
			*	\brief				Returns the Sector that contains this Entity.
			*	\return				A const reference to the Sector that contains this
			*						Entity.
			*/
			const Sector&			GetSector() const;

			/**
			*	\brief				Returns a Datum containing the Actions in this
			*						Entity.
			*	\return				A reference to the Datum containing the Actions in
			*						this Entity.
			*/
			Datum&					Actions() const;

			/**
			*	\brief				Creates a new Action from the Action Factory and
			*						adopts it into itself.
			*	\return				A reference to the Action just created.
			*/
			Action&					CreateAction(const std::string& className, const std::string& instanceName);

			/**
			*	\brief				Creates a new Reaction from the Reaction Factory and
			*						adopts it into itself.
			*	\return				A reference to the Reaction just created.
			*/
			Reaction&				CreateReaction(const std::string& className, const std::string& instanceName);

			/**
			*	\brief				Runs the simulation.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState);

			/**
			*	\brief				Adopts the provided Action into the Actions table.
			*	\param				The Action to be adopted.
			*/
			void					AdoptAction(Action& action);

			/**
			*	\brief				Adopts the provided Reaction into the Reactions table.
			*	\param				The Reaction to be adopted.
			*/
			void					AdoptReaction(Reaction& action);

			virtual void			Populate();

		private:

			std::string mName;			/**< The name of this Entity. */
			Datum*		mpActions;		/**< The cached table of contained Actions. */
			Datum*		mpReactions;	/**< The cached table of contained Reactions. */
		};
	}
}