//
// Created by frabe808 on 06/12/16.
//

#ifndef TDP005_GAMESCENE_H


#include "../interfaces/IScene.h"
#include "../World.h"

class GameScene : public IScene
{

public:
	GameScene(sf::RenderWindow& window);

	void Init() override;

	void LoadTextures() override;

	void Cleanup() override;

	void HandleEvent(sf::Event event) override;

	void Update() override;

	void Draw() override;

private:
	Object* _player{nullptr};
	uptr<World> _world;

	sf::View _hudCamera;

	bool _spawnObstacles{true};

	sf::Clock _runClock;
	bool _isRunning{false};

	sf::Vector2f _lastPos;

	Object* MakeRandomObstacle();

	void ConfigureHUD();

	void GenerateObstacles(int, int, int);

	void UpdateCamera(double);

	void UpdateHUD(double);

	void UpdatePlayerInteractions(double);

	void GameOver(int config);

	//temp ui
	sf::Font font;
	sf::Text _timerText;
	sf::Text _coffeeText;
	sf::RectangleShape _coffeeMeter;
	sf::Text _staminaText;
	sf::RectangleShape _staminaMeter;
	sf::Text _velocityText;
	sf::Sprite _coffeeTiltArrow;
	sf::Sprite _coffeeBarSprite;
	sf::RectangleShape _hudBackground;
};


#endif //TDP005_GAMESCENE_H
