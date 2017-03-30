#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Sector;
		class WorldState;

		class Entity : public Attributed
		{
		public:

			Entity();
			virtual ~Entity() = default;
			const std::string& Name() const;
			void SetName(const std::string& name);
			const Sector& GetSector() const;
			void Update(const WorldState& worldState);

		private:

			std::string mName;
		};
	}
}