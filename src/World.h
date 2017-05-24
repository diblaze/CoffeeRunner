//
// Created by frabe808 on 06/12/16.
// PROTOTYPEEE!!
//

#ifndef TDP005_WORLD_H
#define TDP005_WORLD_H

#include "objects/Object.h"
#include "TextureManager.h"
#include <vector>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#define uptr std::unique_ptr

class World
{
public:
	World();
	~World();

	const int TileSize() const;

	void Load(std::string filename, TextureManager & texMgr);

	std::vector<uptr<Object>> & Tiles();

	Object * GetTile(double x, double y) const;

private:
	std::vector<uptr<Object>> _tiles;
	int _tileSize{128};

};


#endif //TDP005_WORLD_H
;