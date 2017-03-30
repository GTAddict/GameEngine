#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Datum;
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

		private:

			std::string mName;

		};

	}
}
