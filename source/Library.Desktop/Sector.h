#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
		class Datum;
		class Entity;
		class World;
		class WorldState;

		class Sector final : public Attributed
		{
		public:

			Sector();

			const std::string& Name() const;
			void SetName(const std::string& name);
			Datum& Entities();
			Entity& CreateEntity(const std::string& className, const std::string& instanceName);
			void SetWorld(World& world);
			const World& GetWorld() const;
			void Update(const WorldState& worldState);

		private:

			std::string mName;
		};
	}
}

