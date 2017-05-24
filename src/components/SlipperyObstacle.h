//
// Created by frabe808 on 15/12/16.
//

#ifndef TDP005_SLIPPERYOBSTACLE_H
#define TDP005_SLIPPERYOBSTACLE_H


#include "../interfaces/IComponent.h"
#include "Collision.h"
#include "PlayerComponent.h"

class SlipperyObstacle : public IComponent
{
public:
	~SlipperyObstacle();

	void Init() override;

	void Update(double time) override;

	void HandleEvent(sf::Event event) override;

	void ApplyEffect(Object &);

private:
	Collision * _collisionComponent;
	bool _hasCollided{false};

};


#endif //TDP005_SLIPPERYOBSTACLE_H
