//
// Created by frabe808 on 06/12/16.
//
#include <iostream>
#include "MenuScene.h"
#include "../Engine.h"
#include "GameScene.h"

/**
 * Constructor for MenuScene.
 * @param window - RenderWindow to use.
 */
MenuScene::MenuScene(sf::RenderWindow& window)
		:IScene(window)
{
	LoadTextures();
	Init();
}

/**
 * Initializes MenuScene.
 * Sets all texts.
 */
void MenuScene::Init()
{
	//loads font
	if (!font.loadFromFile("src/assets/Hack-Bold.ttf"))
	{
		return;
	}

	_bg.setTexture(_texManager.GetTexture("bg"));

	//init main text
	_mainText.setFont(font);
	_mainText.setColor(sf::Color::White);
	_mainText.setString("Coffee Runner!");
	_mainText.setPosition(
			sf::Vector2f(_window.getSize().x / 3, _window.getSize().y / 2));

	//init instruction text
	_instructionText.setFont(font);
	_instructionText.setColor(sf::Color::White);
	_instructionText.setString(
			">Press enter to start!\n>Use A/D to switch lanes.\n>"
					"Use W/S to increase/decrease speed.\n>Use Left/Right to balance coffee!\n>"
					"Use Space to jump!");
	_instructionText.setPosition(
			sf::Vector2f(_window.getSize().x / 6, _window.getSize().y * 0.6));


}

void MenuScene::LoadTextures()
{
	_texManager.LoadTexture("bg","src/assets/bg.png");

}

/**
 * Cleans up MenuScene.
 */
void MenuScene::Cleanup()
{
	_window.setView(_window.getDefaultView());

}

/**
 * Handles input events.
 * @param event - Event to handle.
 */
void MenuScene::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Return)
			{
				_next = Engine::make<GameScene>(_window);

			}
			break;

	}

}

/**
 * Updates MenuScene.
 * Triggers all object updates.
 */
void MenuScene::Update()
{
	double gameTime = _clock.restart().asMilliseconds();
	for (auto& ob : _objects)
	{
		ob->Update(gameTime);
	}

}

/**
 * Draws everything in MenuScene.
 */
void MenuScene::Draw()
{

	_window.clear(sf::Color::Black);
	_window.draw(_bg);
	for (auto& ob : _objects)
	{
		ob->Draw(_window);
	}

	_window.draw(_mainText);
	_window.draw(_instructionText);

}



