#pragma once

#include "RotatingObjects.h"

class Asteroid : public RotatingObjects
{
public:
	using RotatingObjects::RotatingObjects;

	void initializeDelay() { m_delay = (float)(rand() % 8 + 4); };
	void initializeSpeed() { int r = rand() % 2; (r == 0) ? m_speed = 1.0f : m_speed = 2.0f; };
	float getSpeed() const{ return m_speed; };

	float getDelay() const { return m_delay; };

	virtual void setAnimation(int way, sf::Sprite& sprite) {};

	~Asteroid() = default;

private:
	float m_speed;
	float m_delay = 0;

};