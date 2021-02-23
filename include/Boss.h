#pragma once

#include "Enemy.h"

class Boss : public Enemy
{
public:
	using Enemy::Enemy;
	Boss(sf::Vector2f position, sf::Sprite sprite) :Enemy(position, sprite) { getSprite().setScale(SCALE_SIZE * 0.022, SCALE_SIZE * 0.022); }

	void approachSpaceship(sf::Vector2f position);
	void decreasePower() { m_hits--; }
	int getBossPower()const { return m_hits; }
	virtual void setAnimation(int way, sf::Sprite& sprite) {};

	~Boss() = default;
private:
	int m_hits = 50;
};