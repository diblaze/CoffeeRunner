//
// Created by deniii on 12/8/16.
//

#include <SFML/Window/Keyboard.hpp>
#include <math.h>
#include "PlayerController.h"
#include "../objects/Object.h"

#define LANE_LENGTH (float)(_tileSize)
#define JUMP_DUR .5f
#define FALL_DUR 1.f
#define GEAR_AMOUNT 3

/**
 * Initializes the PlayerController component.
 */
void PlayerController::Init()
{
	//sets starting lane.
	_currentLane = Lane::MiddleL;

	_playerComponent = _parent->Fetch<PlayerComponent>();
	if (!_playerComponent)
	{
		throw std::runtime_error(
				"PlayerController can not work without a Player component!");
	}

	/* Move player */
	_moveableComponent = _parent->Fetch<Moveable>();
	if (!_moveableComponent)
	{
		throw std::runtime_error(
				"PlayerController can not work without a Moveable component!");
	}


	//initializes velocity gears
	InitGears(_moveableComponent->GetMaxVelocity());
}


/**
 * Handles input events.
 * @param event - Event to handle
 */
void PlayerController::HandleEvent(sf::Event event)
{

	if(_playerComponent->IsFalling())
	{
		return;
	}

	switch (event.type)
	{
		case sf::Event::KeyReleased:
			//Extra krav
			/*if (event.key.code == sf::Keyboard::Up)
			{

				if (_playerComponent->IsJumping())
					return;
				_playerComponent->DrinkCoffee(5);
			}
			if (event.key.code == sf::Keyboard::Down)
			{

				if (_playerComponent->IsJumping())
					return;
			}*/
			if (event.key.code == sf::Keyboard::W)
			{

				if (_playerComponent->IsJumping())
					return;
				IncreaseVelocity();
			}
			if (event.key.code == sf::Keyboard::S)
			{

				if (_playerComponent->IsJumping())
					return;
				DecreaseVelocity();
			}
			if (event.key.code == sf::Keyboard::D)
			{

				if (_playerComponent->IsJumping())
					return;
				HopLeft();
			}

			if (event.key.code == sf::Keyboard::A)
			{

				if (_playerComponent->IsJumping())
					return;
				HopRight();
			}

			if (event.key.code == sf::Keyboard::Space)
			{

				if (_playerComponent->IsJumping())
					return;
				Jump();
			}

			if (event.key.code == sf::Keyboard::Left)
			{
				_playerComponent->PlayerPressedLeft = true;
			} else if (event.key.code == sf::Keyboard::Right)
			{
				_playerComponent->PlayerPressedRight = true;
			}
			break;
	}

}

/**
 * Updates the PlayerController component.
 * @param time - Amount of elapsed time since last game tick.
 */
void PlayerController::Update(double time)
{
	//calculates falling time
	if (_playerComponent->IsFalling() &&
	    _fallTimer.getElapsedTime().asSeconds() >= FALL_DUR)
	{
		_parent->setColor(sf::Color::White);
		_playerComponent->SetFalling(false);
	}

	//calculates jumping time
	if (_playerComponent->IsJumping() &&
	    _jumpTimer.getElapsedTime().asSeconds() >= JUMP_DUR)
	{
		_parent->setColor(sf::Color::White);
		_playerComponent->SetJumping(false);
	}

	if(_playerComponent->IsFalling())
	{
		return;
	}

	//moves player in forward direction.
	sf::Vector2f _currentDirection = _moveableComponent->Forward();
	_moveableComponent->Move(_currentDirection * (float)time);


}


/**
 * Increases player's velocity.
 */
void PlayerController::IncreaseVelocity()
{
	if (_moveableComponent->GetVelocity() + velocityPerGear >
	    _moveableComponent->GetMaxVelocity())
	{
		return;
	}
	_moveableComponent->AddVelocity(velocityPerGear);
}

/**
 * Decreases player's velocity
 */
void PlayerController::DecreaseVelocity()
{
	if (_moveableComponent->GetVelocity() - velocityPerGear <= 0)
	{
		return;
	}

	_moveableComponent->RemoveVelocity(velocityPerGear);
}

/**
 * Jumps to the lane left of player if possible.
 */
void PlayerController::HopLeft()
{
	sf::Vector2f directionVector = _moveableComponent->Left();

	switch (_currentLane)
	{

		case Lane::MiddleL:

			_moveableComponent->Teleport(
					(directionVector * LANE_LENGTH) + _parent->getPosition());
			_currentLane = Lane::LeftL;

			break;

		case Lane::RightL:
			_moveableComponent->Teleport(
					(directionVector * LANE_LENGTH) + _parent->getPosition());
			_currentLane = Lane::MiddleL;

			break;
		default:
			break;
	}
}

/**
 * Jumps to the lane right of player if possible.
 */
void PlayerController::HopRight()
{
	sf::Vector2f directionVector = _moveableComponent->Right();

	switch (_currentLane)
	{
		case Lane::LeftL:
			_moveableComponent->Teleport(
					(directionVector * LANE_LENGTH) + _parent->getPosition());
			_currentLane = Lane::MiddleL;

			break;

		case Lane::MiddleL:
			_moveableComponent->Teleport(
					(directionVector * LANE_LENGTH) + _parent->getPosition());
			_currentLane = Lane::RightL;

			break;
		default:
			break;
	}
}

/**
 * Initializes gears for player's max velocity.
 * @param maxVelocity - Max velocity player can achieve.
 */
void PlayerController::InitGears(double maxVelocity)
{
	velocityPerGear = maxVelocity / GEAR_AMOUNT;

	velocityPerGear = std::floor(std::pow(10.0f, 2) * velocityPerGear) /
	                  std::pow(10.0f, 2);

}

/**
 * Makes the player jump.
 */
void PlayerController::Jump()
{
	_playerComponent->SetJumping(true);
	_parent->setColor(sf::Color::Green);
	DecreaseVelocity();
	_jumpTimer.restart();


}

/**
 * Makes the player fall.
 */
void PlayerController::Fall()
{
	_playerComponent->SetFalling(true);
	_parent->setColor(sf::Color::Red);
	_playerComponent->RemoveCoffee(20);
	_fallTimer.restart();


}

double PlayerController::GetGearSpeed() const
{
	return velocityPerGear;
}

Lane PlayerController::CurrentLane() const
{
	return _currentLane;
}

void PlayerController::SetTileSize(int size)
{
	_tileSize = size;
}
