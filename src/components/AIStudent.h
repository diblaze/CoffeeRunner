//
// Created by frabe808 on 15/12/16.
//

#ifndef TDP005_AISTUDENT_H
#define TDP005_AISTUDENT_H


#include "../interfaces/IComponent.h"
#include "Moveable.h"
#include "Collision.h"

class AIStudent : public IComponent
{
public:
	void Init() override;

	void Update(double time) override;

	void HandleEvent(sf::Event event) override;

	void SetDirection(sf::Vector2f direction);

private:
	sf::Vector2f _direction{0,0};

	Moveable * _moveableComponent{nullptr};
	Collision * _collisionComponent{nullptr};

};


#endif //TDP005_AISTUDENT_H

