//
// Created by frabe808 on 06/12/16.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "World.h"
#include "objects/ObjectFactory.h"

/**
 * Constructor for World.
 */
World::World()
{ }

/**
 * Deconstructor for World.
 */
World::~World()
{

}

/**
 * Loads tilemap.
 * @param filename - Tilemap to use.
 * @param texMgr - TextureManager to use.
 */
void World::Load(std::string filename, TextureManager& texMgr)
{
	std::ifstream file(filename);
	std::string line;

	if (!file)
	{ throw std::runtime_error("No file with that name was found"); }

	int xPos{0};
	int yPos{0};

	bool createTile{false};

	int i;

	while (getline(file, line, ','))
	{
		std::stringstream ss(line);

		while (ss >> i)
		{
			createTile = true;

			if (ss.peek() == '\n')
			{
				yPos++;
				xPos = 0;
				continue;
			}

			uptr<Object> _t{nullptr};
			int scale = 1;

			switch (i)
			{

				case -1:
					createTile = false;
					break;
				case 0:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("floor"));
					_t->Name = "Floor";
					break;
				case 1:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("left_wall"));
					break;
				case 2:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("right_wall"));
					break;
				case 3:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("door_wall"));
					break;
				case 4:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("top_wall"));
					break;
				case 5:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("bottom_wall"));
					break;
				case 7:
					_t = ObjectFactory::Make(ObjectType::TurnRightTile,
							texMgr.GetTexture("floor"));
					break;
				case 8:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("corner_left_bottom"));
					break;
				case 9:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("corner_right_bottom"));
					break;
				case 10:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("corner_left_top"));
					break;
				case 11:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("corner_right_top"));
					break;
				case 12:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("comp_top"));
					break;
				case 13:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("comp_bottom"));
					break;
				case 14:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("java_empty"));
					_t->rotate(180);
					break;
				case 15:
					_t = ObjectFactory::Make(ObjectType::TurnLeftTile,
							texMgr.GetTexture("floor"));
					break;
				case 16:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("java_food"));
					_t->rotate(180);
					break;
				case 17:
					_t = ObjectFactory::Make(ObjectType::Tile,
							texMgr.GetTexture("java_table"));
					break;
				case 22:
					_t = ObjectFactory::Make(ObjectType::GoalTile,
							texMgr.GetTexture("goal"));
					break;
			}

			if (createTile)
			{
				_t->setScale(scale, scale);
				_t->setPosition(xPos * _tileSize, yPos * _tileSize);
				_tiles.push_back(std::move(_t));
			}

			xPos++;
		}
	}


}

/**
 * Get tile at X and Y positions.
 * @param x - x position
 * @param y - y position
 * @return Pointer to tile.
 */
Object* World::GetTile(double x, double y) const
{
	for (auto& ti : _tiles)
	{
		if (ti->getGlobalBounds().contains(x, y))
		{
			return ti.get();
		}
	}
	return nullptr;
}

const int World::TileSize() const
{
	return _tileSize;
}

std::vector<uptr<Object>>& World::Tiles()
{
	return _tiles;
}

