#pragma once

#include "BaseObject.h"
#include "Global.h"


class Spaceship : public BaseObject
{
public:
	Spaceship(sf::Vector2f position, sf::Sprite sprite);
	~Spaceship() = default;

	virtual void setAnimation(int way, sf::Sprite& sprite);

	using BaseObject::BaseObject;
	int getBulletLevel()const { return m_bullet_count; };
	void increaseBullet() { if (m_bullet_count < 2) m_bullet_count++; };
	void decreaseBullet() { if (m_bullet_count > 0) m_bullet_count--; };
	void decreaseLife() { m_life--; };

	void increasePoints(int num) { m_points += num; };
	int getPoints()const { return m_points; };
	int getLife()const { return m_life; };

private:
	int m_life = 5;
	int m_bullet_count = 0;
	int m_points = 0;
};




