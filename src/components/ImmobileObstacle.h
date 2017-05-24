//
// Created by frabe808 on 13/12/16.
//

#ifndef TDP005_IMMOBILEOBSTACLE_H
#define TDP005_IMMOBILEOBSTACLE_H


#include "../interfaces/IComponent.h"
#include "Collision.h"
#include "../objects/Object.h"

class ImmobileObstacle : public IComponent
{
public:
	ImmobileObstacle(){};
	~ImmobileObstacle();

	void Init() override;

	void Update(double time) override;

	void HandleEvent(sf::Event event) override;

private:
	Collision * _collisionComponent;
	bool _hasCollided{false};
};


#endif //TDP005_IMMOBILEOBSTACLE_H
