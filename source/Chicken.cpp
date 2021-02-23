#include "Chicken.h"

Chicken::Chicken(sf::Vector2f position, sf::Sprite sprite)
	:Enemy(position, sprite)
{
	getSprite().setTextureRect(sf::IntRect(0, 0, 100, 86));
	getSprite().setScale(SCALE_SIZE * 0.012, SCALE_SIZE * 0.012);
}

void Chicken::setAnimation(int way, sf::Sprite& sprite)
{
	m_animation_counter += m_dynamic_clock.restart().asMilliseconds();

	if ((m_animation_counter >= elapsed))
	{
		m_animation_counter -= elapsed;
		m_source++;
	}

	if (m_source * 100 >= 497) m_source = 0;

	sprite.setTextureRect(sf::IntRect(m_source * 100, 0, 100, 86));
}
