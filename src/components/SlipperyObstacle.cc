//
// Created by frabe808 on 15/12/16.
//

#include "SlipperyObstacle.h"
#include "../objects/Object.h"
#include "PlayerComponent.h"
#include "PlayerController.h"

/**
 * Initializes SlipperObstacle component.
 */
void SlipperyObstacle::Init()
{
	_collisionComponent = _parent->Fetch<Collision>();
	if (!_collisionComponent)
	{
		throw std::runtime_error(
				"SlipperyObstacle can not work without a Collision component!");
	}


}

/**
 * Deconstructor for SlipperyObstacle
 */
SlipperyObstacle::~SlipperyObstacle()
{
	_collisionComponent = nullptr;
}


/**
 * Updates the SlipperyObstacle component.
 * @param time - Amount of elapsed time since last game tick.
 */
void SlipperyObstacle::Update(double time)
{
	if( _hasCollided )
		return;

	//did anything collide with us?
	if(auto col =_collisionComponent->HasCollided())
	{
		//was it the player?
		if(auto player = col->Fetch<PlayerComponent>())
		{

			if (player->IsJumping())
				return;

			ApplyEffect(*col);
			_hasCollided = true;

		}
	}

}

/**
 * Handles the events for SlipperyObstacle
 * @param event - Event to handle
 */
void SlipperyObstacle::HandleEvent(sf::Event event)
{

}

/**
 * Applies an effect to object that collided with the obstacle.
 * @param hit - The object that collided with the obstacle.
 */
void SlipperyObstacle::ApplyEffect(Object & hit)
{
	//is it the player?
	if( auto pc = hit.Fetch<PlayerController>() )
	{
		// if not lowest speed
		if(hit.Fetch<Moveable>()->GetVelocity() > pc->GetGearSpeed() )
		{
			pc->Fall();
		}
	}

}
