//
// Created by frabe808 on 13/12/16.
//

#include "ImmobileObstacle.h"
#include "PlayerComponent.h"
#include "Moveable.h"

/**
 * Initializes the ImmobileObstacle.
 * Fetches and assigns the Collision component to the obstacle.
 */
void ImmobileObstacle::Init()
{
	_collisionComponent = _parent->Fetch<Collision>();
	if (!_collisionComponent)
	{
		throw std::runtime_error(
				"ImmobileObstacle can not work without a Collision component!");
	}


}

/**
 * Deconstructor for ImmobileObstacle.
 */
ImmobileObstacle::~ImmobileObstacle()
{
	_collisionComponent = nullptr;

}

/**
 * Update logic for ImmobileObstacle.
 * Checks if player has collided with current obstacle.
 * @param time - Amount of elapsed time since last game tick.
 */
void ImmobileObstacle::Update(double time)
{

	if( _hasCollided )
		return;

	//if obstacle has collided
	if(auto col =_collisionComponent->HasCollided())
	{
		//if it is a player
		if(auto player = col->Fetch<PlayerComponent>())
		{

			//if player is jumping then do nothing
			if(player->IsJumping())
				return;

			player->RemoveCoffee(10);
			_hasCollided = true;


		}
	}

}
/**
 * Handles events for ImmobileObstacles.
 * @param event - event to handle
 */
void ImmobileObstacle::HandleEvent(sf::Event event)
{

}


