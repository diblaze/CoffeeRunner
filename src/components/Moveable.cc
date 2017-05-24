//
// Created by frabe808 on 24/11/16.
//


#include <iostream>
#include "Moveable.h"
#include "../objects/Object.h"

/**
 * Constructor for Moveable component.
 * @param maxVelocity - Max velocity for object assigned to this Moveable.
 */
Moveable::Moveable(double maxVelocity)
		:_maxVelocity(maxVelocity)
{
	Init();
}

/**
 * Initializes the Moveable component.
 */
void Moveable::Init()
{

}

/**
 * Update logic for Movable component.
 * Checks if parent object is turning in a corner.
 * @param time - Amount of elapsed time since last game tick.
 */
void Moveable::Update(double time)
{

	if (_isTurning && _turnCounter.getElapsedTime().asSeconds() >= 1)
	{
		_isTurning = false;
		_turnCounter.restart();
	}

}

/**
 * Handles events for Moveable component.
 * @param event - Event to handle.
 */
void Moveable::HandleEvent(sf::Event event)
{

}

/**
 * Teleports parent object to a specific location.
 * @param x - Game World X position to teleport to.
 * @param y - Game World Y position to teleport to.
 */
void Moveable::Teleport(float x, float y)
{
	_parent->setPosition(x, y);
}

/**
 * Teleports parent object to a specific location.
 * @param pos - Vector2f of Game World postion.
 */
void Moveable::Teleport(sf::Vector2f pos)
{
	_parent->setPosition(pos.x, pos.y);
}

/**
 * Moves parent object in a specific direction using a vector.
 * @param directionVector - Vector2f of direction to move in.
 */
void Moveable::Move(sf::Vector2f directionVector)
{
	_parent->move(directionVector * (float) _velocity);
}

/**
 * Moves parent object in a specific direction using x and y.
 * @param offsetX - X units to move
 * @param offsetY - Y units to move
 */
void Moveable::Move(int offsetX, int offsetY)
{
	_parent->move(offsetX, offsetY);
}

/**
 * Adds velocity to parent object.
 * @param amount - Amount of velocity to add.
 */
void Moveable::AddVelocity(double amount)
{
	if (_velocity + amount < _maxVelocity)
		_velocity += amount;
	else
		_velocity = _maxVelocity;
}

/**
 * Removes velocity from parent object.
 * @param amount - Amount of velocity to remove.
 */
void Moveable::RemoveVelocity(double amount)
{
	if (_velocity - amount > 0)
		_velocity -= amount;
	else
		_velocity = 0;
}


/**
 * Sets velocity for parent object.
 * @param amount - Velocity to set to.
 */
void Moveable::SetVelocity(double amount)
{
	if (GetVelocity() - amount < 0)
	{
		AddVelocity(-1 * GetVelocity() - amount);
	} else if (GetVelocity() - amount > 0)
	{
		RemoveVelocity(GetVelocity() - amount);
	}

}

/**
 * Calculates direction vector that moves forward of parent object.
 * @return Direction vector that specifies forward direction.
 */
sf::Vector2f Moveable::Forward() const
{
	double _rotation = _parent->getRotation();

	sf::Vector2f directionForward;

	//going down
	if (_rotation == 0)
	{
		directionForward = {0, 1};
	}
		//going right
	else if (_rotation == 90)
	{
		directionForward = {-1, 0};
	} else if (_rotation == 180)
	{
		directionForward = {0, -1};

	} else if (_rotation == 270)
	{
		directionForward = {1, 0};
	}

	return directionForward;
}

/**
 * Calculates direction vector that moves backwards of parent object.
 * @return Direction vector that specifies backwards direction.
 */
sf::Vector2f Moveable::Backward() const
{
	double _rotation = _parent->getRotation();

	sf::Vector2f directionForward;

	//going down
	if (_rotation == 0)
	{
		directionForward = {0, -1};
	}
		//going right
	else if (_rotation == 90)
	{
		directionForward = {1, 0};
	} else if (_rotation == 180)
	{
		directionForward = {0, 1};

	} else if (_rotation == 270)
	{
		directionForward = {-1, 0};
	}

	return directionForward;
}

/**
 * Calculates direction vector that moves right of parent object.
 * @return Direction vector that specifies right direction.
 */
sf::Vector2f Moveable::Right() const
{
	double _rotation = _parent->getRotation();
	sf::Vector2f directionForward;

	//going down
	if (_rotation == 0)
	{
		directionForward = {Forward().y, Forward().x};
	}
		//going right
	else if (_rotation == 90)
	{
		directionForward = {Backward().y, Backward().x};
	} else if (_rotation == 180)
	{
		directionForward = {Forward().y, Forward().x};

	} else if (_rotation == 270)
	{
		directionForward = {Backward().y, Backward().x};
	}

	return directionForward;
}

/**
 * Calculates direction vector that moves left of parent object.
 * @return Direction vector that specifies left direction.
 */
sf::Vector2f Moveable::Left() const
{
	double _rotation = _parent->getRotation();
	sf::Vector2f directionForward;

	//going down
	if (_rotation == 0)
	{
		directionForward = {Backward().y, Backward().x};
	}
		//going right
	else if (_rotation == 90)
	{
		directionForward = {Forward().y, Forward().x};
	} else if (_rotation == 180)
	{
		directionForward = {Backward().y, Backward().x};

	} else if (_rotation == 270)
	{
		directionForward = {Forward().y, Forward().x};
	}

	return directionForward;
}


/**
 * Turns parent object to left.
 * @param co - Turn tile that collided with parent object.
 */
void Moveable::ChangeLeft(Object* co)
{
	if (IsTurning())
		return;

	float dirFactor{1};

	if (Left().x == 1 || Left().x == -1)
	{ dirFactor = Left().x * -1; };

	if (Left().y == 1 || Left().y == -1)
	{ dirFactor = Left().y; };

	_turnCounter.restart();
	_isTurning = true;
	_parent->setRotation(_parent->getRotation() + dirFactor * 90);
	Teleport(co->getPosition());

}
/**
 * Turns parent object to right.
 * @param co - Turn tile that collided with parent object.
 */
void Moveable::ChangeRight(Object* co)
{
	if (IsTurning())
		return;

	float dirFactor{1};

	if (Right().x == 1 || Right().x == -1)
	{ dirFactor = Right().x * -1; };

	if (Right().y == 1 || Right().y == -1)
	{ dirFactor = Right().y; };

	_turnCounter.restart();
	_isTurning = true;
	_parent->setRotation(_parent->getRotation() + dirFactor * 90);
	Teleport(co->getPosition());
}

/**
 * Gets velocity of parent object.
 * @return Velocity of parent object.
 */
double Moveable::GetVelocity() const
{
	return _velocity;
}

bool Moveable::IsTurning() const
{
	return _isTurning;
}

double Moveable::GetMaxVelocity() const
{
	return _maxVelocity;
}






