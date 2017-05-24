//
// Created by frabe808 on 08/12/16.
//

#ifndef TDP005_COLLISION_H
#define TDP005_COLLISION_H


#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>
#include "../interfaces/IComponent.h"

#define uptr std::unique_ptr

class Collision : public IComponent
{

public:
	Collision();
	Collision(float collisionScale);
	~Collision();

	void Init() override;

	void Update(double time) override;

	void HandleEvent(sf::Event);

	Object * HasCollided() const;
	Object * HasCollided(float, float) const;
	Object * HasCollided(sf::Vector2f) const;

	sf::Rect<float> CollisionBox() const;

private:
	float _collisionScale{1};
	sf::Rect<float> _collisionBox;
	static std::vector<Collision *> collisions;

};


#endif //TDP005_COLLISION_H
