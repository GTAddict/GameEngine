#pragma once

class GameTime;

namespace GameEngine
{
	namespace Library
	{
		class WorldState final
		{

		public:

			const GameTime& GetGameTime();
			void SetGameTime(const GameTime& gameTime);

		private:

			class World* mpWorld;
			class Sector* mpSector;
			class Entity* mpEntity;
			class Action* mpAction;

			const GameTime* mpGameTime;

		};
	}
}