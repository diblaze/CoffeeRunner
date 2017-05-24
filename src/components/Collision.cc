//
// Created by frabe808 on 08/12/16.
//

#include <iterator>
#include <algorithm>
#include <iostream>
#include "../objects/Object.h"
#include "Collision.h"


/**
 * Constructor for the Collision component.
 * Checks if component is in the collision list.
 * If not, puts into list.
 */
Collision::Collision()
{
	if ((std::find(collisions.begin(), collisions.end(), this) ==
	     collisions.end()))
	{
		collisions.emplace_back(this);
	}


}

/**
 * Initialize the static collision list.
 */
std::vector<Collision*> Collision::collisions;

/**
 * NOT USED
 */
void Collision::Init()
{
}

/**
 * Runs the update logic for collision component.
 * @param time - Amount of time elapsed since last game tick.
 */
void Collision::Update(double time)
{

	_collisionBox = Parent()->getGlobalBounds();
	_collisionBox.width *= _collisionScale;
	_collisionBox.height *= _collisionScale;

}

/**
 * Deconstructor for Collision component.
 * Removes current collision component from list of all collision components.
 */
Collision::~Collision()
{
	collisions.erase(std::remove(collisions.begin(), collisions.end(), this),
			collisions.end());
}

/**
 * Checks if an object has collided with another object.
 * Both objects needs a collision component to be able to collide.
 * @return Object that collided with current object.
 */
Object* Collision::HasCollided() const
{

	//goes through all collisions in list
	for (auto& c : collisions)
	{
		//if the object we do the checking from is found, continue to next
		if (c == this)
			continue;

		//check if this object and the object in list are colliding by intersect
		if (c->CollisionBox().intersects(
				_collisionBox))
		{
			return c->Parent();
		}
	}
	//return nullptr if no collision has occurred.
	return nullptr;
}

/**
 * Checks if an object has collided with another object on a x and y axis.
 * Both objects needs a collision component to be able to collide.
 * @param x - Game World X position
 * @param y - Game World Y position.
 * @return
 */
Object* Collision::HasCollided(float x, float y) const
{
	//Temp rectangle
	sf::Rect<float> pr{{_collisionBox.left + x, _collisionBox.top + y},
	                   {_collisionBox.width,    _collisionBox.height}};

	for (auto& c : collisions)
	{
		if (c == this)
			continue;

		if (pr.intersects(c->Parent()->getGlobalBounds()))
		{
			return c->Parent();
		}
	}
	return nullptr;
}

/**
 * Checks if an object has collided with another object on a x and y axis.
 * Both objects needs a collision component to be able to collide.
 * @param pos - Vector2f with Game World X and Game World Y postions.
 * @return Object that collided with current object.
 */
Object* Collision::HasCollided(sf::Vector2f pos) const
{
	return HasCollided(pos.x, pos.y);
}


/**
 * Handles events for collision components.
 * Not used at the moment.
 */
void Collision::HandleEvent(sf::Event)
{

}

/**
 * Constructor for the Collision component.
 * Checks if component is in the collision list.
 * If not, puts into list.
 * Sets collision scale
 */
Collision::Collision(float collisionScale)
		:_collisionScale{collisionScale}
{
	if ((std::find(collisions.begin(), collisions.end(), this) ==
	     collisions.end()))
	{
		collisions.emplace_back(this);
	}

}

sf::Rect<float> Collision::CollisionBox() const
{
	return _collisionBox;
}

