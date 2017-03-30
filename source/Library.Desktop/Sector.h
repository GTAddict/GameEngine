#pragma once
#include "Attributed.h"

namespace GameEngine
{
	namespace Library
	{
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
			const World& GetWorld() const;
			void Update(const WorldState& worldState);
			void AdoptEntity(Entity& entity);

		private:

			std::string mName;
			Datum*		mpEntities;
		};
	}
}

