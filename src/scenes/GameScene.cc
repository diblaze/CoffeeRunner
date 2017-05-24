//
// Created by frabe808 on 06/12/16.
//

#include <iostream>
#include <complex>
#include "GameScene.h"
#include "../Engine.h"
#include "EndScene.h"
#include "../components/PlayerController.h"
#include "../components/Collision.h"
#include "../components/AIStudent.h"
#include "../utils/Mathf.h"

#define ot ObjectType
#define spawnX (2 * _world->TileSize())
#define spawnY (2 * _world->TileSize())

#define CAMERA_OFFSET (float)(2.5f * _world->TileSize())
#define CAMERA_ZOOM 2.5
#define CAMERA_ROTATION_SPEED 4.f
#define CAMERA_FOLLOW_SPEED_LANE 2.5f
#define CAMERA_FOLLOW_SPEED 15.f
#define DRAW_DISTANCE (15*_world->TileSize())

#define MAX_SPAWN_PER_INTERVAL 4
#define MIN_SPAWN_PER_INTERVAL 2
#define SPAWN_INTERVAL 10
#define SPAWN_OFFSET 8


/**
 * Constructor for GameScene
 * @param window - RenderWindow to use.
 */
GameScene::GameScene(sf::RenderWindow& window)
		:IScene(window), _world{new World()}
{
	LoadTextures();
	Init();
}

/**
 * Loads all the textures needed for the game.
 */
void GameScene::LoadTextures()
{
	_texManager.LoadTexture("floor", "src/assets/floor.png");
	_texManager.LoadTexture("left_wall", "src/assets/left_wall.png");
	_texManager.LoadTexture("right_wall", "src/assets/right_wall.png");
	_texManager.LoadTexture("door_wall", "src/assets/door_wall.png");
	_texManager.LoadTexture("top_wall", "src/assets/top_wall.png");
	_texManager.LoadTexture("bottom_wall", "src/assets/down_wall.png");
	_texManager.LoadTexture("corner_left_bottom",
			"src/assets/corner_left_down.png");
	_texManager.LoadTexture("corner_right_bottom",
			"src/assets/corner_right_down.png");
	_texManager.LoadTexture("corner_left_top",
			"src/assets/corner_left_top.png");
	_texManager.LoadTexture("corner_right_top",
			"src/assets/corner_right_top.png");
	_texManager.LoadTexture("comp_top", "src/assets/comp_top.png");
	_texManager.LoadTexture("comp_bottom", "src/assets/comp_down.png");
	_texManager.LoadTexture("java_empty", "src/assets/java_empty.png");
	_texManager.LoadTexture("java_food", "src/assets/java_food.png");
	_texManager.LoadTexture("java_table", "src/assets/java_table.png");
	_texManager.LoadTexture("goal.png", "src/assets/goal.png");
	_texManager.LoadTexture("player", "src/assets/player.png");
	_texManager.LoadTexture("player_jump", "src/assets/player_jump.png");
	_texManager.LoadTexture("player_walk1", "src/assets/player_walk1.png");
	_texManager.LoadTexture("student", "src/assets/student.png");
	_texManager.LoadTexture("fallen_student", "src/assets/fallen_student.png");
	_texManager.LoadTexture("slippery_floor", "src/assets/slippery_floor.png");
	_texManager.LoadTexture("goal", "src/assets/goal.png");
	_texManager.LoadTexture("tilt_bar", "src/assets/tiltBar.png");
	_texManager.LoadTexture("tilt_mark", "src/assets/tiltMarker.png");

}

/**
 * Initializes GameScene.
 * Creates all objects, initializes them, loads the map and creates the camera.
 */
void GameScene::Init()
{

	//Player configs
	_player = makeObject(ot::Player, _texManager.GetTexture("player"));
	_player->setPosition(spawnX, spawnY);
	_player->Fetch<PlayerController>()->SetTileSize(_world->TileSize());
	_lastPos = _player->getPosition();

	//Map configs
	_world->Load("src/map.csv", _texManager);
	BgColor = {123, 69, 0};

	//Camera configs
	_mainCamera.reset(sf::FloatRect(spawnX, spawnY, _window.getSize().x,
			_window.getSize().y));
	_hudCamera.reset(
			sf::FloatRect(0, 0, _window.getSize().x, _window.getSize().y));
	_mainCamera.setCenter(_player->getPosition());
	_mainCamera.setRotation(180);
	_mainCamera.zoom(CAMERA_ZOOM);

	//Configure temp HUD.
	ConfigureHUD();

}

/**
 * Configures the HUD.
 */
void GameScene::ConfigureHUD()
{
	//load font
	if (!font.loadFromFile("src/assets/Hack-Bold.ttf"))
	{
		return;
	}

	//time text
	_timerText.setFont(font);
	_timerText.setColor(sf::Color::White);
	_timerText.setPosition(_window.getSize().x - 190, _window.getSize().y - 35);
	_timerText.setString("tick");
	_timerText.setCharacterSize(15);

	//coffee text
	_coffeeText.setFont(font);
	_coffeeText.setColor(sf::Color::White);
	_coffeeText.setPosition(20, _window.getSize().y - 35);
	_coffeeText.setString("Coffee:     100% ");
	_coffeeText.setCharacterSize(15);

	//coffee tilt sprite
	_coffeeBarSprite.setTexture(_texManager.GetTexture("tilt_bar"));
	_coffeeBarSprite.setPosition(_window.getSize().x / 2,
			_window.getSize().y - 35);
	_coffeeBarSprite.setOrigin(98, 15);


	//coffee tilt arrow
	_coffeeTiltArrow.setTexture(_texManager.GetTexture("tilt_mark"));
	_coffeeTiltArrow.setPosition(_coffeeBarSprite.getPosition().x,
			_coffeeBarSprite.getPosition().y);
	_coffeeTiltArrow.setOrigin(_coffeeTiltArrow.getGlobalBounds().width/2, _coffeeTiltArrow.getGlobalBounds().height/2);

	//coffee bar
	_coffeeMeter.setSize(sf::Vector2f(100, 25));
	_coffeeMeter.setOutlineColor({89, 60, 31});
	_coffeeMeter.setFillColor({89, 60, 31});
	_coffeeMeter.setPosition(_coffeeText.getGlobalBounds().width/2 + 20, _window.getSize().y - 38);

	//stamina bar
	_staminaText.setFont(font);
	_staminaText.setColor(sf::Color::Yellow);
	_staminaText.setPosition(11, _window.getSize().y - 65);
	_staminaText.setString("Stamina: ");
	_staminaText.setCharacterSize(15);

	//stamina meter
	_staminaMeter.setSize(sf::Vector2f(100, 25));
	_staminaMeter.setOutlineColor(sf::Color::Yellow);
	_staminaMeter.setFillColor(sf::Color::Yellow);
	_staminaMeter.setPosition(85, _window.getSize().y - 70);

	//velocity meter
	_velocityText.setFont(font);
	_velocityText.setColor(sf::Color::White);
	_velocityText.setPosition(_window.getSize().x - 190,
			_window.getSize().y - 75);
	_velocityText.setString("");
	_velocityText.setCharacterSize(20);


	//hud background
	_hudBackground.setSize(sf::Vector2f(_window.getSize().x, 100));
	_hudBackground.setFillColor(sf::Color::Black);
	_hudBackground.setPosition(0, _window.getSize().y - 100);

}

/**
 * Switches to EndScene.
 * @param config - Value to send to EndScene. Controls the texts on EndScene.
 */
void GameScene::GameOver(int config)
{

	_isRunning = false;
	float time = _runClock.getElapsedTime().asSeconds();
	float coffee = _player->Fetch<PlayerComponent>()->GetCoffee();

	switch (config)
	{
		case 0:
			_player->SetDisable(true);
			//TODO: Calculate score and show on end scene.
			_next = Engine::make<EndScene>(_window, "damn you pretty good!",
					time, coffee);
			break;

		case 1:
			_player->SetDisable(true);
			_next = Engine::make<EndScene>(_window, "you can do better!", time,
					coffee);
			break;
		case 2:
			_player->SetDisable(true);
			_next = Engine::make<EndScene>(_window, "You dropped your coffee!",
					time,
					coffee);
	}

}

/**
 * Cleans up GameScene.
 */
void GameScene::Cleanup()
{
	_next.reset();
	_player = nullptr;
}

/**
 * Handles input events
 * @param event - Event to handle
 */
void GameScene::HandleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::W && !_isRunning &&
			    !_player->IsDisabled())
			{
				_runClock.restart();
				_isRunning = true;
			}
			if( event.key.code == sf::Keyboard::M)
			{
				_mainCamera.zoom(5);
			}
			if( event.key.code == sf::Keyboard::N)
			{
				_mainCamera.zoom(-5);
			}
			break;
	}


	for (auto& obj: _objects)
	{
		obj->HandleEvent(event);
	}
}

/**
 * Updates the GameScene.
 * Generates the obstacles needed, updates objects, updates camera and HUD.
 */
void GameScene::Update()
{
	double gameTime = _clock.restart().asMilliseconds();

	GenerateObstacles(MIN_SPAWN_PER_INTERVAL, MAX_SPAWN_PER_INTERVAL,
			SPAWN_INTERVAL);

	//World object updates
	for (auto& ob : _world->Tiles())
	{
		ob->SetActive(Mathf::distance(ob->getPosition(),
				_player->getPosition()) <= DRAW_DISTANCE);
		ob->Update(gameTime);
	}


	//Scene object updates
	for (auto& ob : _objects)
	{
		ob->SetActive(Mathf::distance(ob->getPosition(),
				_player->getPosition()) <= DRAW_DISTANCE);
		ob->Update(gameTime);
	}

	UpdatePlayerInteractions(gameTime);
	UpdateCamera(gameTime);
	UpdateHUD(gameTime);

}

/**
 * Updates GameScene according to player.
 * @param time - Amount of elapsed time since last game tick.
 */
void GameScene::UpdatePlayerInteractions(double time)
{
	if (_player && _player->IsActive())
	{


		if (auto co = _player->Fetch<Collision>()->HasCollided())
		{

			if (co->Name == "Turn Right")
			{
				_player->Fetch<Moveable>()->ChangeRight(co);
			} else if (co->Name == "Turn Left")
			{
				//last turn no more spawn
				_spawnObstacles = false;
				_player->Fetch<Moveable>()->ChangeLeft(co);
			}
		}

		if (auto co = _player->Fetch<Collision>()->HasCollided())
		{
			if (co->Name == "Goal")
			{
				GameOver(0);
			}
		}
	} else if (!_player->IsActive())
	{
		if (_player->Fetch<PlayerComponent>()->DroppedCoffee())
		{
			//player dropped coffee. Show "bad" text.
			GameOver(2);

		} else
		{
			//player did not drop coffee. Show "good" text.
			GameOver(1);
		}
	}


}

/**
 * Updates the camera.
 * @param time - Amount of elapsed time since last game tick.
 */
void GameScene::UpdateCamera(double time)
{
	Moveable* mc = _player->Fetch<Moveable>();

	//Camera rotation based on player rotation
	float dirFactor{0};
	if (mc->Backward().x == 1 || mc->Backward().x == -1)
	{ dirFactor = mc->Backward().x; };

	float dtRot = CAMERA_ROTATION_SPEED * (float) (time / 1000);
	float newRot = Mathf::Lerp(_mainCamera.getRotation(),
			((dirFactor * 90) + 180), dtRot);
	_mainCamera.setRotation((newRot));

	//Camera position based on player rotation
	sf::Vector2f setPos = {
			_player->getPosition() + (mc->Backward() * -(CAMERA_OFFSET))};

	float dtLane = CAMERA_FOLLOW_SPEED_LANE * (float) (time / 1000);
	float dtForward = CAMERA_FOLLOW_SPEED * (float) (time / 1000);
	sf::Vector2f smoothPos = _mainCamera.getCenter();

	if (mc->Forward().x == 1 || mc->Forward().x == -1)
	{
		smoothPos.y = Mathf::Lerp(smoothPos.y, setPos.y, dtLane);
		smoothPos.x = Mathf::Lerp(smoothPos.x, setPos.x, dtForward);
	} else if (mc->Forward().y == 1 || mc->Forward().y == -1)
	{
		smoothPos.x = Mathf::Lerp(smoothPos.x, setPos.x, dtLane);
		smoothPos.y = Mathf::Lerp(smoothPos.y, setPos.y, dtForward);
	}

	_mainCamera.setCenter(smoothPos);


}

/**
 * Updates the HUD.
 * @param time - Amount of elapsed time since last game tick.
 */
void GameScene::UpdateHUD(double time)
{

	//temp ui
	if (_player && _isRunning)
	{
		int time = _runClock.getElapsedTime().asSeconds();
		float coffee = _player->Fetch<PlayerComponent>()->GetCoffee();
		float stamin = _player->Fetch<PlayerComponent>()->GetStamina();
		float velo = _player->Fetch<Moveable>()->GetVelocity();
		float tilt = _player->Fetch<PlayerComponent>()->GetCoffeeTilt();

		_timerText.setString("Time: " + std::to_string(time));
		_velocityText.setString("Speed: " + std::to_string((int)(velo * 10)));
		_coffeeText.setString("Coffee:     "+ std::to_string((int)coffee) +"% ");
		_coffeeMeter.setScale(coffee / 100, 1);
		_coffeeTiltArrow.setPosition(
				_coffeeBarSprite.getPosition().x + (tilt),
				_coffeeBarSprite.getPosition().y - 3);
	}


}

/**
 * Generates the obstacles.
 * @param maxSpawn - Maximum obstacles to spawn in game session.
 * @param minSpawn - Minimum obstacles to spawn in game session.
 * @param step - How many steps away from player the obstacle shall spawn.
 */
void GameScene::GenerateObstacles(int maxSpawn, int minSpawn, int step)
{
	if (!_spawnObstacles)
	{ return; }

	auto mc = _player->Fetch<Moveable>();

	if (!mc->GetVelocity() > 0)
	{ return; }

	sf::Vector2f axisToLook;

	axisToLook = {_player->getPosition().x * mc->Forward().x,
	              _player->getPosition().y * mc->Forward().y};

	float playerAxisToCheck{axisToLook.x == 0 ? axisToLook.y : axisToLook.x};

	axisToLook = {_lastPos.x * mc->Forward().x, _lastPos.y * mc->Forward().y};
	float lastAxisToCheck{axisToLook.x == 0 ? axisToLook.y : axisToLook.x};

	if (std::abs((int) playerAxisToCheck - (int) lastAxisToCheck) >=
	    _world->TileSize() * step)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> spawnDist(minSpawn, maxSpawn);
		std::uniform_real_distribution<double> offsetDist(0, 3);
		std::uniform_real_distribution<double> laneDist(0, 2);

		int toSpawn{(int) spawnDist(mt)};

		int offset = SPAWN_OFFSET;
		sf::Vector2f spawnLane{0, 0};

		//if 0 == start spawning from right lane. if == 1 spawn from left
		int laneStartFactor{(int) laneDist(mt)};

		if (laneStartFactor == 0)
		{
			switch (_player->Fetch<PlayerController>()->CurrentLane())
			{

				case LeftL:
					spawnLane = _player->getPosition() +
					            ((float) -_world->TileSize() * 2 * mc->Right());
					break;

				case MiddleL:
					spawnLane = _player->getPosition() +
					            ((float) -_world->TileSize() * mc->Right());
					break;

				case RightL:
					spawnLane = _player->getPosition();
					break;
			}
		} else if (laneStartFactor == 1)
		{
			switch (_player->Fetch<PlayerController>()->CurrentLane())
			{
				case LeftL:
					spawnLane = _player->getPosition();
					break;

				case MiddleL:
					spawnLane = _player->getPosition() +
					            ((float) -_world->TileSize() * mc->Left());
					break;

				case RightL:
					spawnLane = _player->getPosition() +
					            ((float) -_world->TileSize() * 2 * mc->Left());
					break;
			}

		}

		for (int x{0}; x < toSpawn; x++)
		{

			sf::Vector2f delta{spawnLane - (_player->getPosition() +
			                                (mc->Forward() *
			                                 (float) _world->TileSize() *
			                                 (float) offset))};

			sf::Vector2f spawnPos{_player->getPosition() - delta};

			if (auto tile = _world->GetTile(spawnPos.x, spawnPos.y))
			{
				if (tile->Name == "Floor")
				{
					Object* ob = MakeRandomObstacle();
					ob->setPosition(spawnPos);
					if (auto ai = ob->Fetch<AIStudent>())
					{
						ai->SetDirection(mc->Backward());
					}

					offset += offsetDist(mt);
					sf::Vector2f laneOffset;
					ob->setRotation(_player->getRotation() + 180);

					//Move one tile to left or right depending on start tile.
					if (laneStartFactor == 0)
					{ laneOffset = (float) _world->TileSize() * mc->Right(); }
					else if (laneStartFactor == 1)
					{ laneOffset = (float) _world->TileSize() * mc->Left(); }

					spawnLane += laneOffset;

				}
			}

		}

		_lastPos = _player->getPosition();
	}


}

/**
 * Creates a random type of obstacle.
 * @return Pointer to obstacle.
 */
Object* GameScene::MakeRandomObstacle()
{
	int random = rand() % 3;

	switch (random)
	{
		case 0:
			return makeObject(ot::ImmobileObstacleTile,
					_texManager.GetTexture("fallen_student"));

		case 1:
			return makeObject(ot::SlipperyObstacleTile,
					_texManager.GetTexture("slippery_floor"));

		case 2:
			return makeObject(ot::StudentObstacleTile,
					_texManager.GetTexture("student"));

	}
	return nullptr;


}

/**
 * Draws everything in GameScene.
 */
void GameScene::Draw()
{

	_window.setView(_mainCamera);

	//World object draw
	for (auto& ob : _world->Tiles())
	{
		ob->Draw(_window);
	}

	//Scene object draw
	for (auto& ob : _objects)
	{

		if (ob->Name != "Player")
			ob->Draw(_window);

	}

	//Draw player on top
	_player->Draw(_window);


	// temp ui
	_window.setView(_hudCamera);
	_window.draw(_hudBackground);
	_window.draw(_timerText);
	_window.draw(_coffeeMeter);
	_window.draw(_coffeeText);
	//Extra krav
	//_window.draw(_staminaText);
	//_window.draw(_staminaMeter);
	_window.draw(_velocityText);
	_window.draw(_coffeeBarSprite);
	_window.draw(_coffeeTiltArrow);
}

