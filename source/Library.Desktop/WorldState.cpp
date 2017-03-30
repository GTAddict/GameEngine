#include "pch.h"
#include "WorldState.h"
#include "GameTime.h"

namespace GameEngine
{
	namespace Library
	{
		const GameTime& WorldState::GetGameTime()
		{
			return *mpGameTime;
		}

		void WorldState::SetGameTime(const GameTime& gameTime)
		{
			mpGameTime = &gameTime;
		}
	}
}
