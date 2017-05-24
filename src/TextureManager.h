//
// Created by frabe808 on 16/12/16.
//

#ifndef TDP005_TEXTUREMANAGER_H
#define TDP005_TEXTUREMANAGER_H

#include <string>
#include <map>

class TextureManager
{
public:
	TextureManager()
	{ }
	~TextureManager();
	void LoadTexture(const std::string& name, const std::string &filename);
	sf::Texture& GetTexture(const std::string& texture);


private:
	std::map<std::string, sf::Texture> _textures;

};


#endif //TDP005_TEXTUREMANAGER_H
