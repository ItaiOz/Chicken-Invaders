#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Global.h"

class SpaceShip;
class Chicken;
class Egg;
class Asteroid;
class Boss;

class BaseObject
{
public:
	BaseObject() = default;
	BaseObject(sf::Vector2f position, sf::Sprite sprite);


	void move(float delta);
	void moveSinusly(float delta); //function to move chickens sinusly
	void changeDirection();
	bool toRemove() const { return m_remove; };  //func to return object status
	bool toBlow()const { return m_blow; };
	void setRemove() { m_remove = true; };		//func to set if the object is "dead"
	void resurrect() { m_remove = false; };
	void setDirection(sf::Vector2f direction) { m_direction = direction; };
	void setBlow() { m_blow = true; }
	void blow(sf::Sprite sprite);
	virtual void setAnimation(int way, sf::Sprite& sprite) = 0 {};
	//void setBlowAnimation(sf::Sprite sprite);

	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition()const { return m_position; };
	sf::Sprite& getSprite() { return m_sprite; };
	sf::FloatRect getGlobalBounds()const { return m_sprite.getGlobalBounds(); };

	void setPosition(sf::Vector2f position) { m_position = position; }
	void setXPosition(float d) { m_position.x += d; }
	//void changeSprite(sf::Texture* blow, sf::Vector2f position);
	~BaseObject() {};

private:
	sf::Vector2f m_position;
	sf::Sprite m_sprite;

	bool m_remove = false;
	bool m_blow = false;
	sf::Vector2f m_direction;
	sf::Vector2f m_starting_position;
	float m_lastDelta = 0;
	//------------------------vars for animation-------------------
	sf::Clock m_dynamic_clock;
	int m_source = 0;
	int m_animation_counter = 0;
	float frame = 700.0f;
};
