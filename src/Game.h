//
// Created by frabe808 on 06/12/16.
//

#ifndef TDP005_GAME_H
#define TDP005_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Engine.h"

class Game
{
public:
	void Run(unsigned int width = 800, unsigned int height = 600);

private:
	sf::RenderWindow _window;
	Engine _engine{_window};
};


#endif //TDP005_GAME_H
