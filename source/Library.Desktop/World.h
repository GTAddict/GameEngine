#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Sector;
		class WorldState;

		class World final : public Attributed
		{
		public:
			
			World();

			const std::string& Name() const;
			void SetName(const std::string& name);
			Datum& Sectors();
			Sector& CreateSector();
			void Update(const WorldState& worldState);
			void AdoptSector(Sector& sector);

		private:

			std::string mName;
			Datum*		mpSectors;

		};

	}
}
