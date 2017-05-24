//
// Created by deniii on 12/8/16.
//

#ifndef TDP005_PLAYER_H
#define TDP005_PLAYER_H


#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "../interfaces/IComponent.h"

class Coffee
{
public:
	Coffee(float AmountOfCoffee);

	bool RemoveCoffee(double amount);

	bool DrinkCoffee(double amount);

	float GetAmountOfCoffee() const;

	float GetCurrentTilt() const;

	void SetCurrentTilt(float tilt);

	float SetAmountOfCoffee(float coffee);

	void SetTiltTime(double);

	float GetTiltTime() const;

	int GetCurrentTiltDirection() const;

	void SetCurrentTiltDirection(int tiltTo);

	bool IsInited() const;

	void Inited();

private:
	float _currentTilt{0};
	float _amountOfCoffee{0};
	float _tiltingTo;
	float _time;
	bool _inited{false};

};


class PlayerComponent : public IComponent
{
public:
	PlayerComponent(double, double);

	void RemoveCoffee(double amount);

	void DrinkCoffee(double amount);

	float GetCoffee() const;

	void HandleEvent(sf::Event event) override;

	void AddStamina(double amount);

	void RemoveStamina(double amount);

	float GetStamina() const;

	void SetJumping(bool status);

	bool IsJumping() const;;

	void SetFalling(bool status);

	bool IsFalling() const;;

	void Init() override;

	void Update(double) override;

	void
	CalculateTilt(double time, double currentVelocity, bool playerTiltedLeft,
			bool playerTiltedRight);

	bool PlayerPressedLeft{false};
	bool PlayerPressedRight{false};


	float GetCoffeeTilt() const;
	bool DroppedCoffee() const;

private:
	Coffee coffee{100};
	float _stamina;
	bool _droppedCoffee {false};

	bool _isJumping{false};
	bool _isFalling{false};


};


#endif //TDP005_PLAYER_H
