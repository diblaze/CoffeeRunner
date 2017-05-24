//
// Created by frabe808 on 24/11/16.
//

#ifndef TDP005_MOVEABLE_H
#define TDP005_MOVEABLE_H


#include <SFML/System/Clock.hpp>
#include "../interfaces/IComponent.h"

enum Speed
{
	Slow,
	Medium,
	Fast
};

class Moveable : public IComponent
{

public:
	Moveable(double maxVelocity);

	void Init() override;
	void Update(double) override;
	void HandleEvent(sf::Event event) override;

	void Teleport(float x, float y);
	void Teleport(sf::Vector2f pos);

	 sf::Vector2f Backward() const;
	 sf::Vector2f Forward() const;
	 sf::Vector2f Right() const;
	 sf::Vector2f Left() const;

	void ChangeLeft(Object*);
	void ChangeRight(Object*);

	void AddVelocity(double amount);
	void RemoveVelocity(double amount);
	void SetVelocity(double amount);

	void Move(sf::Vector2f directionVector);
	void Move(int offsetX, int offsetY);

	bool IsTurning() const;

	double GetVelocity() const;
	double GetMaxVelocity() const;

private:
	double _velocity {0};

	double const _maxVelocity;

	bool _isTurning{false};

	sf::Clock _turnCounter;

};


#endif //TDP005_MOVEABLE_H
