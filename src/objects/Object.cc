//
// Created by frabe808 on 23/11/16.
//


#include <iostream>
#include "Object.h"

/**
 * Constructor for Object.
 */
Object::Object()
{
	Init();
}

/**
 * Constructor for Object. Use to specify texture and game world position.
 * @param texture - Texture to use.
 * @param position - Vector2f GameWorld to use.
 */
Object::Object(const sf::Texture& texture, const sf::Vector2f& position)
{
	setTexture(texture);
	// Set origin to middle
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	setPosition(position);
}


/**
 * Initializes Object.
 */
void Object::Init()
{
	//set starting Game World position.
	setPosition(0, 0);
}


/**
 * Draws the object to the specifed RenderWindow.
 * @param window - RenderWindow to draw on.
 */
void Object::Draw(sf::RenderWindow& window) const
{
	if(!IsActive()) { return; }

	//cast the current object to an sprite to be able to draw.
	window.draw(*dynamic_cast<const sf::Sprite*>(this));
}

/**
 * Updates the Object.
 * @param time - Amount of elapsed time since last game tick.
 */
void Object::Update(double time) const
{
	if(IsDisabled()) { return;}

	if(!IsActive()) { return; }

	for (auto& c : Slots)
	{
		c->Update(time);
	}
}

/**
 * Handles the event
 * @param event - Event to handle
 */
void Object::HandleEvent(sf::Event event) const
{

	if(IsDisabled()) { return;}

	if(!IsActive()) { return; }

	for(auto& slot : Slots)
	{
		slot->HandleEvent(event);
	}

}

/**
 * Disable the object.
 */
void Object::SetDisable(bool status)
{
	_isDisabled = status;

}

/**
 * Activate the object.
 */
void Object::SetActive(bool status)
{
	_isActive = status;
}

bool Object::IsActive() const
{
	return _isActive;
}

bool Object::IsDisabled() const
{
	return _isDisabled;
}
