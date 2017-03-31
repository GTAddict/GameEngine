#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Entity;
		class World;
		class WorldState;

		/**
		*	\class	Sector
		*	\brief	This is a container that holds Entities.
		*			On simulation, it iterates over contained
		*			Entities and updates their simulations.
		*			Sectors themselves are contained by World
		*			objects and can be thought of as chunks.
		*/
		class Sector final : public Attributed
		{
		public:

			/**
			*	\brief				Default constructor. Adds Name and Entities
			*						as Attributes.
			*/
									Sector();

			/**
			*	\brief				Returns the name of this Sector.
			*	\return				A const string reference to the this Sector's name.
			*/
			const std::string&		Name() const;

			/**
			*	\brief				Sets the name of this Sector.
			*	\param name			The name of this Sector to set.
			*	\throw std::invalid_argument if name is empty.
			*/
			void					SetName(const std::string& name);

			/**
			*	\brief				Returns a Datum containing the Entities in this
			*						Sector.
			*	\return				A reference to the Datum containing the Entities in
			*						this Sector.
			*/
			Datum&					Entities();

			/**
			*	\brief				Creates a new Entity from the Entity Factory and
			*						adopts it into itself.
			*	\return				A reference to the Sector just created.
			*/
			Entity&					CreateEntity(const std::string& className, const std::string& instanceName);
			
			/**
			*	\brief				Returns the World that contains this Sector.
			*	\return				A const reference to the World that contains this
			*						Sector.
			*/
			const World&			GetWorld() const;

			/**
			*	\brief				Runs the simulation. Also runs the simulation on
			*						contained Entities by calling their Update methods.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState);

			/**
			*	\brief				Adopts the provided Entity into the Entities table.
			*	\param				The Entity to be adopted.
			*/
			void					AdoptEntity(Entity& entity);

		private:

			std::string mName;		/**< The name of this Sector. */
			Datum*		mpEntities;	/**< The cached table of contained Entities. */
		};
	}
}

