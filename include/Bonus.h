#pragma once

#include "RotatingObjects.h"
#include <SFML/Graphics.hpp>

class Bonus: public RotatingObjects
{
public:
	using RotatingObjects::RotatingObjects;
	virtual void setAnimation(int way, sf::Sprite& sprite) {};

	~Bonus() = default;
};

