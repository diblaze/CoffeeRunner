//
// Created by frabe808 on 16/12/16.
//

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "TextureManager.h"

/**
 * Load a texture to list.
 * @param name - Name to associate with.
 * @param filename - File to load.
 */
void TextureManager::LoadTexture(const std::string& name,
		const std::string& filename)
{
	sf::Texture tex;
	tex.loadFromFile(filename);

	_textures[name] = tex;
}

/**
 * Gets texture from list.
 * @param texture - Texture to get.
 * @return Pointer to texture.
 */
sf::Texture& TextureManager::GetTexture(const std::string& texture)
{

	return _textures.at(texture);
}

/**
 * Deconstructor for TextureManager.
 * Clears the texture list.
 */
TextureManager::~TextureManager()
{
	_textures.clear();
}
