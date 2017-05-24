//
// Created by frabe808 on 24/11/16.
//

#include <stdlib.h>
#include "ObjectFactory.h"
#include "../components/PlayerController.h"
#include "../components/Collision.h"
#include "../components/ImmobileObstacle.h"
#include "../components/SlipperyObstacle.h"
#include "../components/AIStudent.h"

//Object name definitions
#define TURN_LEFT_ID "Turn Left"
#define TURN_RIGHT_ID "Turn Right"
#define GOAL_ID "Goal"

/**
 * Creates an object.
 * @param type - ObjectType to create.
 * @param texture - Texture to use.
 * @return Unique pointer to object.
 */
uptr<Object> ObjectFactory::Make(ObjectType type, sf::Texture & texture)
{
	switch (type)
	{
		case Player:
			return MakePlayer(texture);

		case Tile:
			return MakeTile(texture);

		case TurnLeftTile:
			return MakeTurnLeft(texture);

		case TurnRightTile:
			return MakeTurnRight(texture);

		case GoalTile:
			return MakeGoal(texture);

		case ImmobileObstacleTile:
			return MakeImmobileObstacle(texture);

		case SlipperyObstacleTile:
			return MakeSlipperyObstacle(texture);

		case StudentObstacleTile:
			return MakeStudentObstacle(texture);
	}

	return NULL;
}

/**
 * Creates a player.
 * @param texture - Texture to use.
 * @return Unique pointer to player.
 */
uptr<Object> ObjectFactory::MakePlayer(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = "Player";

	pattern->Attach<Collision>(0.5);
	pattern->Attach<Moveable>(1);
	pattern->Attach<PlayerComponent>(100.0, 100.0);
	pattern->Attach<PlayerController>();

	return std::move(pattern);

}


/**
 * Creates a tile.
 * @param texture - Texture to use.
 * @return Unique pointer to tile.
 */
uptr<Object> ObjectFactory::MakeTile(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = "Tile";
	return std::move(pattern);
}

/**
 * Creates a turn left tile.
 * @param texture - Texture to use.
 * @return Unique pointer to tile.
 */
uptr<Object> ObjectFactory::MakeTurnLeft(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = TURN_LEFT_ID;
	pattern->Attach<Collision>();
	pattern->setColor(sf::Color::Red);

	return std::move(pattern);

}

/**
 * Creates a turn right rile.
 * @param texture - Texture to use.
 * @return Unique pointer to tile.
 */
uptr<Object> ObjectFactory::MakeTurnRight(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = TURN_RIGHT_ID;
	pattern->Attach<Collision>();
	pattern->setColor(sf::Color::Red);

	return std::move(pattern);

}

/**
 * Creates a goal.
 * @param texture - Texture to use.
 * @return Unique pointer to goal.
 */
uptr<Object> ObjectFactory::MakeGoal(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = GOAL_ID;
	pattern->Attach<Collision>();

	return std::move(pattern);

}

/**
 * Creates an ImmobileObstacle.
 * @param texture - Texture to use.
 * @return Unique pointer to obstacle.
 */
uptr<Object> ObjectFactory::MakeImmobileObstacle(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = "ImmobileObstacle";

	pattern->Attach<Collision>(0.5);
	pattern->Attach<ImmobileObstacle>();

	return std::move(pattern);
}

/**
 * Creates an SlipperyObstacle.
 * @param texture - Texture to use.
 * @return Unique pointer to obstacle.
 */
uptr<Object> ObjectFactory::MakeSlipperyObstacle(sf::Texture & texture)
{
	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = "SlipperyObstacle";

	pattern->Attach<Collision>(0.5);
	pattern->Attach<SlipperyObstacle>();

	return std::move(pattern);}

/**
 * Creates an StudentObstacle.
 * @param texture - Texture to use.
 * @return Unique pointer to obstacle.
 */
uptr<Object> ObjectFactory::MakeStudentObstacle(sf::Texture & texture)
{

	uptr<Object> pattern{new Object(texture, {0, 0})};
	pattern->Name = "StudentObstacle";


	pattern->Attach<Moveable>((double)((rand() % 7+1)/10.f));
	pattern->Attach<Collision>(0.5);
	pattern->Attach<AIStudent>();
	pattern->Attach<ImmobileObstacle>();

	return std::move(pattern);
}
