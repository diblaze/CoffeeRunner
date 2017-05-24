//
// Created by frabe808 on 05/12/16.
//

#ifndef TDP005_SCENE_H
#define TDP005_SCENE_H

#include "../objects/Object.h"
#include "../objects/ObjectFactory.h"
#include "../TextureManager.h"

#define uptr std::unique_ptr

class Engine;

class IScene
{

public:
	IScene() = delete;

	IScene(sf::RenderWindow&);

	virtual ~IScene() = default;

	virtual void Init() = 0;

	virtual void LoadTextures() = 0;

	virtual void Cleanup() = 0;

	virtual void HandleEvent(sf::Event event) = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	void PrintObjects() const;

	uptr<IScene> Next();

	sf::Color BgColor{sf::Color::Black};


protected:
	// Create and add an object to the scene
	Object* makeObject(ObjectType, sf::Texture & texture);

	// Vector of objects in scene
	std::vector<uptr<Object>> _objects;

	// Clock to track time
	sf::Clock _clock;

	// Main camera/view
	sf::View _mainCamera;

	// Render window
	sf::RenderWindow& _window;

	// Next scene
	uptr<IScene> _next{nullptr};

	//Texture manager
	TextureManager _texManager;


};


#endif //TDP005_SCENE_H
