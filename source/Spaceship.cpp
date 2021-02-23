#include "Spaceship.h"

Spaceship::Spaceship(sf::Vector2f position, sf::Sprite sprite)
	:BaseObject(position, sprite)
{
	getSprite().setTextureRect(sf::IntRect(0, 0, 40, 86));
	getSprite().setScale(SCALE_SIZE * 0.022, SCALE_SIZE * 0.022);

}

void Spaceship::setAnimation(int way, sf::Sprite& sprite)
{
	sprite.setTextureRect(sf::IntRect(way * 40, 0, 40, 86));
}

