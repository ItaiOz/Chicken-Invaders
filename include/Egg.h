#pragma once

#include "BaseObject.h"

class Egg : public BaseObject
{
public:
	using BaseObject::BaseObject;
	Egg(sf::Vector2f position, sf::Sprite sprite) :BaseObject(position, sprite) {
		getSprite().setTextureRect(sf::IntRect(0, 0, 24, 30));
		getSprite().setScale((float)(SCALE_SIZE * 0.017), (float)(SCALE_SIZE * 0.017));
	}
	virtual void setAnimation(int way, sf::Sprite& sprite){ sprite.setTextureRect(sf::IntRect(25, 0, 67, 30)); };

	void restartTimer() { eggTimer = mEggsClock.restart().asSeconds(); };
	void setHit() { hit_floor = true; };
	bool timesUp() { eggTimer = mEggsClock.getElapsedTime().asSeconds(); return(eggTimer >= 3.0f); };
	bool hitFloor()const{ return hit_floor; };

	~Egg() = default;
private:
	sf::Clock mEggsClock;
	float eggTimer = 0.0f;
	bool hit_floor = false;
};