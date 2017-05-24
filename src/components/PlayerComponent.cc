//
// Created by deniii on 12/8/16.
//
#include <stdlib.h>
#include "PlayerComponent.h"
#include "Moveable.h"
#include "../objects/Object.h"
#include "../utils/Mathf.h"
#include "PlayerController.h"

/**
 * Constructor for Player component.
 * Sets coffee levels and stamina levels.
 * @param coffee - Starting coffee level of Player
 * @param stamina - Starting stamina level of Player
 */
PlayerComponent::PlayerComponent(double coffee, double stamina)
		:coffee{(float) coffee}, _stamina{(float) stamina}
{
}

/**
 * Initializes Player component.
 */
void PlayerComponent::Init()
{

	//init player
}

/**
 * Updates the Player component.
 * @param time
 */
void PlayerComponent::Update(double time)
{
	double currentVelocity = _parent->Fetch<Moveable>()->GetVelocity();

	if (_isFalling)
	{
		return;
	}

	//calculates coffee tilt
	CalculateTilt(time, currentVelocity, PlayerPressedLeft,
			PlayerPressedRight);

	//throw GameOver if coffee tilted or coffee amount is 0.
	if ((coffee.GetCurrentTilt() == 100 || coffee.GetCurrentTilt() == -100) ||
	    coffee.GetAmountOfCoffee() <= 0)
	{
		_droppedCoffee = true;
		_parent->SetActive(false);
	}
}

/**
 * Calculates the coffee tilt of current game tick.
 * Uses LERP to dynamically adjust coffee tilt to velocity.
 * @param time - Amount of elapsed time since last game tick.
 * @param currentVelocity - Current velocity of player.
 * @param playerTiltedLeft - Did player left counter the coffee tilt?
 * @param playerTiltedRight - Did player right counter the coffee tilt?
 */
void PlayerComponent::CalculateTilt(double time, double currentVelocity,
		bool playerTiltedLeft = false, bool playerTiltedRight = false)
{

	double velocityPerGear = _parent->Fetch<PlayerController>()->GetGearSpeed();
	//is coffee is not initialized
	if (!coffee.IsInited())
	{
		//if player is standing still, return
		if (currentVelocity == 0)
		{
			return;
		}

		//set starting tilt to 100
		coffee.SetCurrentTiltDirection(100);
		//set coffee init.
		coffee.Inited();
	}
	//did player left counter tilt?
	if (playerTiltedLeft)
	{
		//tilt back coffee 10 units
		coffee.SetCurrentTilt(coffee.GetCurrentTilt() - 10);
		coffee.SetTiltTime(0);

	}
		//did player right counter tilt?
	else if (playerTiltedRight)
	{
		coffee.SetCurrentTilt(coffee.GetCurrentTilt() + 10);
		coffee.SetTiltTime(0);
	}

	//if player countered tilt, then get a random value
	//and change tilt direction.
	//if random number is 1 (between 1 to 5), then change direction.
	if (playerTiltedLeft || playerTiltedRight)
	{
		if (std::rand() % 5 == 1)
		{
			coffee.SetCurrentTiltDirection(
					coffee.GetCurrentTiltDirection() == 100 ? -100 : 100);
		}
	}
	PlayerPressedLeft = false;
	PlayerPressedRight = false;

	//set current tilt by lerping
	coffee.SetCurrentTilt(
			Mathf::Lerp(coffee.GetCurrentTilt(),
					coffee.GetCurrentTiltDirection(), coffee.GetTiltTime()));


	//set required time to fully tilt relative to current velocity.
	if (currentVelocity <= velocityPerGear)
	{
		coffee.SetTiltTime(coffee.GetTiltTime() + 0.05f * (time / 1000));

	} else if (currentVelocity <= velocityPerGear*2)
	{
		coffee.SetTiltTime(coffee.GetTiltTime() + 0.15f * (time / 1000));

	} else if (currentVelocity <= velocityPerGear*3)
	{
		coffee.SetTiltTime(coffee.GetTiltTime() + 0.25f * (time / 1000));
	}

	//if player dropped coffee, then set coffee to 0.
	// magic numbers - needed because we are getting a float value that
	// almost never goes to -100 or 100 because of lerp.
	if (coffee.GetCurrentTilt() >= 99)
	{
		coffee.SetAmountOfCoffee(0);
	} else if (coffee.GetCurrentTilt() <= -99)
	{
		coffee.SetAmountOfCoffee(0);
	}
}

/**
 * Removes an amount of coffee from player.
 * @param amount - Amount to remove.
 */
void PlayerComponent::RemoveCoffee(double amount)
{
	//if coffee is empty
	if (!coffee.RemoveCoffee(amount))
	{
		_parent->SetActive(false);
	}


}

/**
 * Removes an amount of coffee from player while giving player a stamina boost.
 * @param amount - Amount to drink.
 */
void PlayerComponent::DrinkCoffee(double amount)
{
	//if player can not drink coffee
	if (!coffee.GetAmountOfCoffee() - amount > 0)
	{
		return;
	}
	RemoveCoffee(amount);
	AddStamina(amount);
}

/**
 * Adds an amount of stamina from player.
 * @param amount - Amount to add.
 */
void PlayerComponent::AddStamina(double amount)
{
	_stamina += amount;
	if (_stamina >= 100)
	{
		_stamina = 100;
		return;
	}
}

/**
 * Removes an amount of stamina from player.
 * @param amount - Amount to remove.
 */
void PlayerComponent::RemoveStamina(double amount)
{
	_stamina -= amount;
	if (_stamina <= 0)
	{
		_stamina = 0;
		return;
	}
}

/**
 * Handles events specific to Player component.
 * Only those events that has nothing to do with input.
 * Input is controlled by PlayerController component.
 * @param event - Event to handle.
 */
void PlayerComponent::HandleEvent(sf::Event event)
{
}

/**
 * Sets jumping status.
 * @param status - Status to set to.
 */
void PlayerComponent::SetJumping(bool status)
{
	_isJumping = status;

}

/**
 * @return Amount of coffee left.
 */
float PlayerComponent::GetCoffee() const
{

	return coffee.GetAmountOfCoffee();

}

/**
 * @return Amount of stamina left.
 */
float PlayerComponent::GetStamina() const
{
	return _stamina;
}


/**
 * @return Coffee tilt value.
 */
float PlayerComponent::GetCoffeeTilt() const
{
	return coffee.GetCurrentTilt();
}

/**
 * @return Did Player drop the coffee?
 */
bool PlayerComponent::DroppedCoffee() const
{
	return _droppedCoffee;
}

/**
 * @param status Set player falling
 */
void PlayerComponent::SetFalling(bool status)
{
	_isFalling = status;

}

bool PlayerComponent::IsJumping() const
{
	return _isJumping;
}

bool PlayerComponent::IsFalling() const
{
	return _isFalling;
}

/**
 * @return Amount of Coffee left.
 */
float Coffee::GetAmountOfCoffee() const
{
	return _amountOfCoffee;
}

/**
 * @return Coffee tilt value.
 */
float Coffee::GetCurrentTilt() const
{
	return _currentTilt;
}

/**
 * Sets the current coffee tilt.
 * @param tilt - Value to set.
 */
void Coffee::SetCurrentTilt(float tilt)
{
	_currentTilt = tilt;
}

/**
 * Sets the current coffee value.
 * @param coffee - Value to set.
 */
float Coffee::SetAmountOfCoffee(float coffee)
{
	_amountOfCoffee = coffee;
	return 0;
}

/**
 * Constructor for Coffee.
 * @param AmountOfCoffee - Amount of starting coffee.
 */
Coffee::Coffee(float AmountOfCoffee)
		:_amountOfCoffee{AmountOfCoffee}
{
}

/**
 * Removes an amount of coffee.
 * @param amount - Amount to remove.
 * @return True, if it is possible to remove the amount of coffee.
 */
bool Coffee::RemoveCoffee(double amount)
{
	if (_amountOfCoffee - amount <= 0)
	{
		_amountOfCoffee = 0;
		return false;
	}
	_amountOfCoffee -= amount;
	return true;
}

/**
 * NOT IMPLEMENTED
 * Consumes coffee to get stamina.
 * @param amount - Amount of coffee to consume.
 * @return False
 */
bool Coffee::DrinkCoffee(double amount)
{
	//TODO:Implement Stamina drinking
	return false;
}

/**
 * Sets the required time to fully tilt.
 * @param time
 */
void Coffee::SetTiltTime(double time)
{
	_time = (float) time;

}

/**
 * @return Time required to fully tilt.
 */
float Coffee::GetTiltTime() const
{
	return _time;
}

/**
 * @return Current tilt direction.
 */
int Coffee::GetCurrentTiltDirection() const
{
	//ska denna vara int? returnar ju en float
	return (int) _tiltingTo;
}

/**
 * Sets tilt direction.
 * @param tiltTo - Direction to tilt too. (-100 or 100)
 */
void Coffee::SetCurrentTiltDirection(int tiltTo)
{
	_tiltingTo = tiltTo;
}

/**
 * @return Is coffee initialized?
 */
bool Coffee::IsInited() const
{
	return _inited;
}

/**
 * Initialize coffee parameter.
 */
void Coffee::Inited()
{
	_inited = true;
}
