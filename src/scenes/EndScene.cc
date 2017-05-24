//
// Created by deniii on 12/16/16.
//

#include "EndScene.h"
#include "../Engine.h"
#include "MenuScene.h"

/**
 * Constructor for EndScene
 * @param window - RenderWindow to use.
 * @param message - Message to draw.
 * @param time - Time elapsed of game session.
 * @param coffee - Amount of coffee left.
 */
EndScene::EndScene(sf::RenderWindow& window, std::string message, float time,
		float coffee)
		:IScene(window), _message{message}, _time{time}, _coffee{coffee}
{
	Init();
}

/**
 * Initializes EndScene.
 * Draws all objects needed on screen.
 */
void EndScene::Init()
{

	//load font to use.
	if (!font.loadFromFile("src/assets/Hack-Bold.ttf"))
	{
		return;
	}

	//init main text
	_mainText.setFont(font);
	_mainText.setColor(sf::Color::Red);
	_mainText.setScale(1.5, 1.5);
	_mainText.setString("Game Over!");
	HorizontalCenterText(_mainText, _window.getSize().y / 4);

	//init end text
	_endText.setFont(font);
	_endText.setColor(sf::Color::Red);
	_endText.setString(_message);
	HorizontalCenterText(_endText, _window.getSize().y / 3 + 10);

	//init score text
	_scoreText.setFont(font);
	_scoreText.setColor(sf::Color::Red);
	if(_coffee > 0)
	{
		_scoreText.setString("Time: " + std::to_string(_time) + " / Coffee: " +
		                     std::to_string((int)_coffee) + " \n Final Time:  " +
		                     std::to_string(CalcScore()) + " seconds.");
	}
	else
	{
		_scoreText.setString("Time: " + std::to_string(_time));
	}
	HorizontalCenterText(_scoreText, _window.getSize().y / 2);

	//init instructions text
	_instructionsText.setFont(font);
	_instructionsText.setColor(sf::Color::Red);
	_instructionsText.setString("press space to restart!");
	HorizontalCenterText(_instructionsText, _window.getSize().y * (2.f / 3.f));

}

/**
 * Centers text horizontally.
 * @param t - Text to center
 * @param heightOffset - Offset of height.
 */
void EndScene::HorizontalCenterText(sf::Text& t, float heightOffset) const
{
	sf::FloatRect textRect = t.getLocalBounds();
	t.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
	t.setPosition(sf::Vector2f(_window.getSize().x / 2, heightOffset));

}

/**
 * Cleans up EndScene.
 */
void EndScene::Cleanup()
{
	_window.setView(_window.getDefaultView());

}

/**
 * Updates EndScreen.
 */
void EndScene::Update()
{

	double gameTime = _clock.restart().asMilliseconds();
	for (auto& ob : _objects)
	{
		ob->Update(gameTime);
	}
}

/**
 * Handles events.
 * @param event - Event to handle.
 */
void EndScene::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space)
			{
				_next = Engine::make<MenuScene>(_window);

			}
			break;

	}

}

/**
 * Draws everything on EndScene.
 */
void EndScene::Draw()
{

	_window.clear(sf::Color::Black);

	for (auto& ob : _objects)
	{
		ob->Draw(_window);
	}

	_window.draw(_mainText);
	_window.draw(_endText);
	_window.draw(_scoreText);
	_window.draw(_instructionsText);

}

void EndScene::LoadTextures()
{

}

/**
 * Calculates the summary score of coffee and time
 * @return result
 */
float EndScene::CalcScore() const
{
	float result = _time + ((((100-_coffee)*10))/100);
	if(result <= 0)
	{
		result = 0;
	}
	return result;
}
