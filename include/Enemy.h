#pragma once

#include "BaseObject.h"

class Enemy : public BaseObject
{
public:
	using BaseObject::BaseObject;
	Enemy(sf::Vector2f position, sf::Sprite sprite) :BaseObject(position, sprite) {}

	void setHatched() { m_hatched = true; };
	void resetHatched() { m_hatched = false; };
	bool isHatched()const { return m_hatched; };

	~Enemy() = default;
private:
	bool m_hatched = false;
};


