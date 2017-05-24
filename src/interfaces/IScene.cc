//
// Created by frabe808 on 05/12/16.
//

#include "IScene.h"
#include "../Engine.h"

/**
 * Constructor for Scene interface.
 * @param window - sf::RenderWindow to use.
 */
IScene::IScene(sf::RenderWindow& window)
		:_window{window}
{ }

/**
 * Creates an object and stores it in the scene's objectlist.
 * @param toCreate - ObjectType to create.
 * @param text - Text to associate with the object.
 * @return The object created.
 */
Object* IScene::makeObject(ObjectType toCreate, sf::Texture& text)
{
	_objects.push_back(ObjectFactory::Make(toCreate, text));
	return _objects.back().get();

}

/**
 * @return Gets the next scene.
 */
uptr<IScene> IScene::Next()
{
	return std::move(_next);
}

/**
 * DEBUGGING PURPOSE
 * Prints all objects.
 */
void IScene::PrintObjects() const
{
	std::map<std::string, int> objMap;

	for (auto& ob : _objects)
	{
		if (objMap.count(ob->Name) > 0)
		{
			objMap.find(ob->Name)->second++;
		} else
		{
			objMap.insert(std::pair<std::string, int>(ob->Name, 1));
		}
	}

	for (auto& ob : objMap)
	{
		std::cout << ob.first << " : " << ob.second << std::endl;
	}

}





