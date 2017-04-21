#pragma once
#include "Vector.h"
#include <future>
#include <mutex>

namespace GameEngine
{
	namespace Library
	{
		class EventPublisher;
		class GameTime;

		/**
		*	\class	EventQueue
		*	\brief	This is a class that keeps track of unpublished
		*			publishers, continually checks for expiry, and
		*			publishes them when appropriate.
		*/
		class EventQueue
		{
			using milliseconds = std::chrono::milliseconds;

		public:
			
			/**
			*	\brief					Adds the provided publisher to the queue, to
			*							be published at the specified time.
			*	\param publisher		The publisher to be added to the queue.
			*	\param gameTime			The GameTime object from which to retrieve time.
			*	\param delay			The delay after which the publisher should be
			*							delivered.
			*	\param
			*/
			void						Enqueue(EventPublisher& publisher, const GameTime& gameTime, const milliseconds& delay);

			/**
			*	\brief					Delivers the publisher immediately.
			*/
			void						Send(EventPublisher& publisher);

			/**
			*	\brief					Iterates through the queue, checks if they have 
			*							expired, and sends them if they have.
			*	\param gameTime			The current GameTime object.
			*/
			void						Update(const GameTime& gameTime);

			/**
			*	\brief					Clears the queue of publishers.
			*/
			void						Clear();

			/**
			*	\brief					Returns whether the queue has any pending
			*							deliveries to make.
			*	\param					Whether there are any queued publishers.
			*/
			bool						IsEmpty() const;
			
			/**
			*	\brief					The number of pending deliveries to make.
			*	\param gameTime			The size of the queued publishers.
			*/
			std::uint32_t				Size() const;

		private:

			Vector<EventPublisher*>		mEventQueue;		/**< The collection of pending EventPublishers. */
			Vector<EventPublisher*>		mSweepQueue;		/**< The collection of EventPublishers to be processed this frame. */
			Vector<std::future<void>>	mFutures;			/**< Vector of futures that async will create. Don't want to stack alloc this vector every frame on Update. */
			mutable std::mutex			mEventQueueLock;	/**< The mutex for access to the Event Queue */
		};
	}
}