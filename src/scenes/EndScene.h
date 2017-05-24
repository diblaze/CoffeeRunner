//
// Created by frabe808 on 16/12/16.
//

#ifndef TDP005_ENDSCENE_H
#define TDP005_ENDSCENE_H


#include "../interfaces/IScene.h"

class EndScene : public IScene
{
public:
	EndScene(sf::RenderWindow& window, std::string message, float time,
			float coffee);

	void Init() override;

	void Cleanup() override;

	void LoadTextures() override;

	void Update() override;

	void HandleEvent(sf::Event event) override;

	void Draw() override;

	float CalcScore() const;

	void HorizontalCenterText(sf::Text& t, float heightOffset) const;

private:
	sf::Font font;
	sf::Text _mainText;
	sf::Text _endText;
	sf::Text _scoreText;
	sf::Text _instructionsText;

	std::string _message;
	float _time{0};
	float _coffee{0};


};


#endif //TDP005_ENDSCENE_H
