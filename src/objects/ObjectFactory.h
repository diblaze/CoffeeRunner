//
// Created by frabe808 on 24/11/16.
//

#ifndef TDP005_OBJECTFACTORY_H
#define TDP005_OBJECTFACTORY_H


#include "Object.h"
#include "../components/Moveable.h"
#include "../components/PlayerComponent.h"
#include "../TextureManager.h"

#define uptr std::unique_ptr

enum ObjectType
{
	Player,
	Tile,
	ImmobileObstacleTile,
	SlipperyObstacleTile,
	StudentObstacleTile,
	TurnLeftTile,
	TurnRightTile,
	GoalTile

};

class ObjectFactory
{

public:
	ObjectFactory() = delete;

	static uptr<Object> Make(ObjectType, sf::Texture & texture);

private:
	static uptr<Object> MakePlayer(sf::Texture & texture);

	static uptr<Object> MakeTile(sf::Texture & texture);

	static uptr<Object> MakeImmobileObstacle(sf::Texture & texture);

	static uptr<Object> MakeSlipperyObstacle(sf::Texture & texture);

	static uptr<Object> MakeStudentObstacle(sf::Texture & texture);

	static uptr<Object> MakeTurnLeft(sf::Texture & texture);

	static uptr<Object> MakeTurnRight(sf::Texture & texture);

	static uptr<Object> MakeGoal(sf::Texture & texture);

};


#endif //TDP005_OBJECTFACTORY_H
