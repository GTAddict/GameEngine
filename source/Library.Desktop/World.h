#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Sector;
		class WorldState;

		/**
		*	\class	World
		*	\brief	This is a container that holds Sectors.
		*			On simulation, it iterates over contained 
		*			Sectors and updates their simulations.
		*/
		class World final : public Attributed
		{
			RTTI_DECLARATIONS(World, Attributed);

		public:
			
			/**
			*	\brief				Default constructor. Calls Populate.
			*/
									World();

			/**
			*	\brief				Copy constructor. World is non-copyable.
			*/
									World(const World& rhs) = delete;

			/**
			*	\brief				Move constructor.
			*/
									World(World&& rhs);

			/**
			*	\brief				Copy assignment operator. World is
			*						non-copyable.
			*/
			World&					operator=(const World& rhs) = delete;

			/**
			*	\brief				Move assignment operator.
			*	\return				A reference to this World.
			*/
			World&					operator=(World&& rhs);

			/**
			*	\brief				Returns the name of this World.
			*	\return				A const string reference to the this World's name.
			*/
			const std::string&		Name() const;

			/**
			*	\brief				Sets the name of this World.
			*	\param name			The name of this World to set.
			*	\throw std::invalid_argument if name is empty.
			*/
			void					SetName(const std::string& name);

			/**
			*	\brief				Returns a Datum containing the Sectors in this
			*						world.
			*	\return				A reference to the Datum containing the Sectors in
			*						this World.
			*/
			Datum&					Sectors();

			/**
			*	\brief				Creates a new Sector and adopts it into itself.
			*	\return				A reference to the Sector just created.
			*/
			Sector&					CreateSector();

			/**
			*	\brief				Runs the simulation. Also runs the simulation on
			*						contained Sectors by calling their Update methods.
			*	\param worldState	The current world state encapsulated as a WorldState
			*						object.
			*/
			void					Update(WorldState& worldState);

			/**
			*	\brief				Adopts the provided Sector into the Sectors table.
			*	\param				The Sector to be adopted.
			*/
			void					AdoptSector(Sector& sector);

			/**
			*	\brief				Calls Parent Populate and Adds Name and Sectors
			*						as Attributes.
			*/
			void					Populate() override;

		private:

			std::string mName;		/**< The name of this World. */
			Datum*		mpSectors;	/**< The cached table of contained Sectors. */

		};
	}
}
