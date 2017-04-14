#pragma once

namespace GameEngine
{
	namespace Library
	{
		class GameTime;

		/**
		*	\class	WorldState
		*	\brief	This class holds the current World, Sector
		*			and Entity being simulated in addition to
		*			a GameTime pointer that tracks game time.
		*/
		class WorldState final
		{
		public:

			/**
			*	\brief			Returns a reference to the GameTime
			*					object.
			*	\return			A const reference to a GameTime object.
			*/
			const GameTime&		GetGameTime();

			/**
			*	\brief			Sets the GameTime object.
			*	\param gameTime	The GameTime object to be set.
			*/
			void				SetGameTime(const GameTime& gameTime);

			class World*		mpWorld;		/**< A pointer to the current World	being simulated. */
			class Sector*		mpSector;		/**< A pointer to the current Sector being simulated. */
			class Entity*		mpEntity;		/**< A pointer to the current Entity being simulated. */
			class Action*		mpAction;		/**< A pointer to the current Action being simulated. */
			class EventQueue*	mpEventQueue;	/**< A pointer to the Event Queue that processes Events. */

		private:
			const GameTime*		mpGameTime;		/**< A pointer to the GameTime object. */
		};
	}
}