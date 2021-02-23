#pragma once

#include "Enemy.h"

const float elapsed = 200.0f;

class Chicken : public Enemy
{
public:
	using Enemy::Enemy;
	Chicken(sf::Vector2f position, sf::Sprite sprite);
	void setStay() { m_stay = true; }
	bool isInPlace() const { return m_stay; };
	void setOriginalPoisition(sf::Vector2f position) { m_original_position = position; };
	void initializeTimer() { m_timer = rand() % 6 + 2;};
	int getTimer()const { return m_timer; };
	virtual void setAnimation(int way, sf::Sprite& sprite);
	sf::Vector2f getOriginalPoisition() const { return m_original_position; };

	~Chicken() = default;
private:
	int m_timer = 10; //for not reaching the chickens with no eggs
	bool m_stay = false;
	sf::Vector2f m_original_position;
	//--------------------------vars for animation-------------------
	sf::Clock m_dynamic_clock;
	int m_source = 1;
	int m_animation_counter = 0;
	int m_animation_frame_duration = 100;
};

