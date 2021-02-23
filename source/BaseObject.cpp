#include "BaseObject.h"

BaseObject::BaseObject(sf::Vector2f position, sf::Sprite sprite)
	:m_position(position), m_sprite(sprite)
{
	m_sprite.setPosition(m_position.x, m_position.y);
		m_sprite.scale(SCALE_SIZE / m_sprite.getGlobalBounds().width, (SCALE_SIZE / m_sprite.getGlobalBounds().height));
}
 
void BaseObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
void BaseObject::move(float delta)
{
	getSprite().move(m_direction * delta);
	m_lastDelta = delta;
	setPosition(getSprite().getPosition());
}

void BaseObject::changeDirection()
{
	getSprite().move(-m_direction * m_lastDelta);
}



void BaseObject::moveSinusly(float delta)
{
	getSprite().move(m_direction * delta);
	setXPosition(delta);
	setPosition(getSprite().getPosition());
}

