#include "Bonus.h"

Bonus::Bonus(sf::Vector2f position, sf::Sprite sprite)
	:MovingObject(position, sprite)
{
	setOrigin(); 
	rotationTimer = m_clock.getElapsedTime().asSeconds();
}

void Bonus::setOrigin()
{
		sf::Rect <float> size = getSprite().getGlobalBounds();
		getSprite().setOrigin({ size.width / 2, size.height / 2 });
}
