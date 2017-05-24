//
// Created by deniii on 11/29/16.
//

#include <iostream>
#include <stdlib.h>
#include "Engine.h"

// Define current as next scene (top of scene buffer)
#define current _scenes.top()


/**
 * Constructor for Engine
 * @param window - RenderWindow to use.
 */
Engine::Engine(sf::RenderWindow& window)
		:_window{window}
{

}

/**
 * Deconstructor for Engine.
 */
Engine::~Engine()
{ }

/**
 * Initializes and runs the engine.
 * @param scene - Scene to start on.
 */
void Engine::Run(uptr<IScene> scene)
{

	// Add first scene
	_scenes.push(std::move(scene));

	// Initiate running variable
	_running = true;

	// Create main loop
	while (Running())
	{
		NextScene();
		Update();
		Draw();
	}

}

/**
 * Updates the engine.
 * Goes through all events and handles them.
 */
void Engine::Update() const
{
	sf::Event event;
	// while there are pending events...
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window.close();
			std::exit(0);
		}

		// check the type of the event...
		current->HandleEvent(event);

	}
	current->Update();

}

/**
 * Draws engine.
 */
void Engine::Draw() const
{
	current->Draw();
	_window.display();
	_window.clear(current->BgColor);
}

/**
 * Change to next scene defined by the current scene
 */
void Engine::NextScene()
{
	if (_scenes.empty())
	{ return; }

	if (auto n = current->Next())
	{
		current->Cleanup();
		_window.setView(_window.getDefaultView());
		current.reset();
		_scenes.pop();
		_scenes.push(std::move(n));
	}

}

bool Engine::Running() const
{
	return _running;
}

void Engine::Exit()
{
	_running = false;
}
