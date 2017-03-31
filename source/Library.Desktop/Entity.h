#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Sector;
		class WorldState;

		/**
		*	\class	Entity
		*	\brief	This is a base class that automatically
		*			populates its Scope. It is contained
		*			within a Sector.
		*/
		class Entity : public Attributed
		{
		public:

			/**
			*	\brief				Default constructor. Adds Name as an
			*						Attribute.
			*/
									Entity();

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
			*	\brief				Runs the simulation.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(const WorldState& worldState);

		private:

			std::string mName;		/**< The name of this Entity. */
		};
	}
}