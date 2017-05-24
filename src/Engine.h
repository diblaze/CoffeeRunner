//
// Created by deniii on 11/29/16.
//

#ifndef TDP005_ENGINE_H
#define TDP005_ENGINE_H

//#include "World.h"
#include <memory>
#include <stack>
#include <random>
#include <SFML/Graphics/RenderWindow.hpp>
#include "interfaces/IScene.h"

#define uptr std::unique_ptr
#define stack std::stack


class Engine
{

public:
	Engine(sf::RenderWindow&);

	~Engine();

	void Run(uptr<IScene> scene);
	void NextScene();
	void Update() const;
	void Draw() const;

	bool Running() const;

	void Exit();

	template<typename T, typename ... TArgs>
	static uptr<T> make(TArgs&& ... Args);

private:
	// Stack of scenes
	stack<uptr<IScene>> _scenes;

	// Render window
	sf::RenderWindow& _window;

	bool _running;

};

/**
 * Make a scene based on T parameter.
 *
 * @tparam T Name of the Scene class to create.
 * @return Returns a new Scene based on typename.
 */
template<typename T, typename ... TArgs>
uptr<T> Engine::make(TArgs&& ... Args)
{
	return std::move(uptr<T>(new T(std::forward<TArgs>(Args)...)));
}



#endif //TDP005_ENGINE_H
