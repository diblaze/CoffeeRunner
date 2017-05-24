//
// Created by deniii on 12/8/16.
//

#ifndef TDP005_PLAYERCONTROLLER_H
#define TDP005_PLAYERCONTROLLER_H


#include "../interfaces/IComponent.h"
#include "Moveable.h"
#include "PlayerComponent.h"

enum Lane
{
	LeftL,
	MiddleL,
	RightL
};

class PlayerController : public IComponent
{
public:
	PlayerController()
	{ }

	PlayerController(int tileSize)
			:_tileSize{tileSize}
	{ }

	~PlayerController()
	{ }

	void Init() override;

	void Update(double time) override;

	void HandleEvent(sf::Event event) override;

	void IncreaseVelocity();

	void DecreaseVelocity();

	void HopLeft();

	void HopRight();

	void Jump();

	void Fall();

	double GetGearSpeed() const;

	Lane CurrentLane() const;

	void SetTileSize(int size);

private:
	Lane _currentLane;
	PlayerComponent* _playerComponent;
	Moveable* _moveableComponent;

	int _tileSize{128};

	sf::Clock _jumpTimer;

	sf::Clock _fallTimer;

	sf::Clock _hitTimer;

	void InitGears(double velocity);

	double velocityPerGear{0};
};


#endif //TDP005_PLAYERCONTROLLER_H
