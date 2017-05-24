//
// Created by frabe808 on 06/12/16.
//

#include "Game.h"
#include "scenes/MenuScene.h"

/**
 * Starts and runs the game.
 * @param width - Width of game window.
 * @param height - Height of game window.
 */
void Game::Run(unsigned int width, unsigned int height)
{
	// Create the window
	_window.create(sf::VideoMode{width, height}, "Coffee Rush 0.1 AlphaOmega3");
	_window.clear(sf::Color::White);

	// Set the framerate to 60
	_window.setFramerateLimit(60);

	// Start engine
	_engine.Run(Engine::make<MenuScene>(_window));

}
