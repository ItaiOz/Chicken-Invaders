#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <list>
#include <map>
#include <experimental/vector>

#include "Board.h"
#include "BaseObject.h"
#include "InGameInfo.h"
#include "Egg.h"
#include "Spaceship.h"
#include "Audio.h"
#include "Asteroid.h"
#include "Boss.h"
#include "Files.h"
#include "Global.h"
#include "Chicken.h"
#include "Bullet.h"
#include "PointsBonus.h"
#include "Bonus.h"
#include "ShootingBonus.h"
#include "Colission.h"

class GameController
{
public:
	GameController()=default;
	GameController(bool numOfPlayer) ;

	void runGame(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, float deltaTime);
	void drawBackground(sf::RenderWindow& window, float deltaTime);
	void getToPosition(sf::RenderWindow& window, float deltaTime);
	void moveSpaceship(sf::RenderWindow& window,float deltaTime);
	void shoot(sf::RenderWindow& window);
	void moveChickens(float deltaTime);
	void moveObjects(float deltaTime);
	void moveAsteroids(float deltaTime);
	void dropAsteroids(float deltaTime);
	void createAsteroids();
	void moveHorizonal(float deltaTime);
	void bringChickens(float deltaTime);
	void initializeChickens();
	void checkColissions(sf::RenderWindow& window);
	void createBullet(sf::RenderWindow& window, const int typeplayer);
	void createBonus(sf::RenderWindow& window, sf::Vector2f position);
	void activateBossMode(float deltaTime);
	void checkBossPositions();
	void hatchBossEggs();
	void setNewLevel(sf::RenderWindow& window);
	void gameWon(sf::RenderWindow& window);
	void gameOver(sf::RenderWindow& window);
	void updateBoard(sf::RenderWindow& window);
	sf::Vector2f calculateAsteroidPoisition();
	int getPoints()const { return m_player->getPoints(); };
	int getPointsTwoplayers()const { return m_player2->getPoints() + (m_player->getPoints()); };
	
	int getlife()const { return m_player->getLife() ; };
	int getlife2()const { return m_player2->getLife() ; };
	~GameController() {};
private:
	Board m_board;
	Colission m_colission;
	Audio m_audio;

	int m_current_background = 0;
	int m_other_background = 1;

	std::unique_ptr<InGameInfo> m_in_game_info;
	std::vector<std::vector<std::shared_ptr<Chicken>>> m_chickens;
	std::unique_ptr<Spaceship> m_player;
	std::unique_ptr<Spaceship> m_player2;
	std::unique_ptr<Boss> m_boss;
	std::list<Bullet> m_bullets;
	std::list<Egg> m_eggs;
	std::list<std::unique_ptr< Bonus>> m_bonuses;
	std::vector<std::unique_ptr<Asteroid>> m_asteroids;
	
	sf::Sprite m_sprite_back[2];
	sf::Sprite m_stages[2];
	sf::Texture m_blow;
	sf::Clock m_clock;	
	sf::Clock subStages_clock;
	sf::Clock fire_clock;
	sf::Clock eggs_clock;
	sf::Clock asteroids_clock;
	sf::Clock m_hide_ship_clock;
	sf::Clock boss_clock;
	sf::Clock boss_egg_clock;
	sf::Time boss_egg_timer;

	float subStagesTimer = 0;
	float eggs_timer = 0;
	float asteroids_timer = 0;
	float hide_ship_timer = 0;
	float boss_timer = 0;
	int m_shot_type = 0;

	int chickens_in_place = 0;
	int asteroids_in_place = 0;
	int bonusCounter = 0;
	int bonusNum = 0;
	int bossMoves = 0;
	int m_level=1;
	bool betweenSubStages = false;
	bool AsteroidsMode = false;
	bool bossMode = false;
	bool chickensMode = true;
	bool inStartingPosition = false;
	bool dontShowPlayer1 = false;
	bool dontShowPlayer2 = false;
	bool first_chickens = true;
	bool game_won = false;
	bool game_over = false;
	bool lastLevel = false;
	bool rotateBossClockwise = true;
	bool secondPlayer = false;
	float chicken_movement = 0;
	float fire_rate;
	float eggsDelay = 0.5;
	float backgroundSpeed = 20.0f;
	const float fire_delay = 0.3f;
	float pic_pos;
};

