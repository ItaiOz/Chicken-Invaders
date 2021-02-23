#pragma once

#include "BaseObject.h"

class Bullet : public BaseObject
{
public:
	using BaseObject::BaseObject;
	Bullet(sf::Vector2f position, sf::Sprite sprite) :BaseObject(position, sprite) {
		getSprite().setScale((float)(SCALE_SIZE * 0.017), (float)(SCALE_SIZE * 0.017));
	}
	virtual void setAnimation(int way, sf::Sprite& sprite) {};

	~Bullet() = default;
};