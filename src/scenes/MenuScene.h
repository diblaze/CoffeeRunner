//
// Created by frabe808 on 06/12/16.
//

#ifndef TDP005_MENUSTATE_H
#define TDP005_MENUSTATE_H


#include "../interfaces/IScene.h"


class MenuScene : public IScene
{

public:
	MenuScene(sf::RenderWindow&);

	void Init() override;

	void LoadTextures() override;

	void Cleanup() override;

	void Update() override;

	void HandleEvent(sf::Event event) override;

	void Draw() override;

private:
	sf::Font font;
	sf::Text _mainText;
	sf::Text _instructionText;
	sf::Sprite _bg;


};

#endif //TDP005_MENUSTATE_H
