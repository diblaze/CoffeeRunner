//
// Created by frabe808 on 15/12/16.
//

#include "AIStudent.h"
#include "../objects/Object.h"

/**
 * Initilizes the AIStudent component.
 * Fetches and assigns moveable component and
 * collision component from parent class.
 */
void AIStudent::Init()
{
	_moveableComponent = _parent->Fetch<Moveable>();
	if (!_moveableComponent)
	{
		throw std::runtime_error(
				"AIStudent can not work without a Moveable component!");
	}

	_collisionComponent = _parent->Fetch<Collision>();
	if (!_collisionComponent)
	{
		throw std::runtime_error(
				"AIStudent can not work without a Collision component!");
	}

	_moveableComponent->AddVelocity(_moveableComponent->GetMaxVelocity());
	_direction = _moveableComponent->Forward();

}

/**
 * Updates the AIStudent component by moving the
 * AIStudent in a specific direction.
 * @param time - Amount of time elapsed since last game tick.
 */
void AIStudent::Update(double time)
{
	_moveableComponent->Move(_direction * (float) time);
}

void AIStudent::HandleEvent(sf::Event event)
{

}

void AIStudent::SetDirection(sf::Vector2f direction)
{
	_direction = direction;
}
