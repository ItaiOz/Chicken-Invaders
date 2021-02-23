#pragma once

#include "BaseObject.h"
#include <SFML/Graphics.hpp>

const float Timer = 0.2f;
const float rotationOne = 0.25f;
const float rotationTwo = 0.3f;
const float rotationThree = 0.4f;

class RotatingObjects : public BaseObject
{
public:
	using BaseObject::BaseObject;
	RotatingObjects(sf::Vector2f position, sf::Sprite sprite);

	bool toRotate();
	void setOrigin();
	void rotate();
	void setRotationTimer();

	~RotatingObjects() = default;
private:
	sf::Clock m_clock;
	float rotationTimer;
};