#include "RotatingObjects.h"

RotatingObjects::RotatingObjects(sf::Vector2f position, sf::Sprite sprite)
	:BaseObject(position, sprite)
{
	setOrigin();
	m_clock.restart().asSeconds();
}

bool RotatingObjects::toRotate()
{
	rotationTimer = m_clock.getElapsedTime().asSeconds();
	return(rotationTimer >= Timer);
}

void RotatingObjects::setOrigin()
{
	sf::Rect <float> size = getSprite().getGlobalBounds();
	getSprite().setOrigin({ size.width / 2, size.height / 2 });
}

void RotatingObjects::rotate()
{
	rotationTimer = m_clock.restart().asSeconds();
	getSprite().rotate(60.0f);
}

void RotatingObjects::setRotationTimer()
{
	int r = rand() % 4;

	switch (r)
	{

	case 0:
		rotationTimer = Timer;
	case 1:
		rotationTimer = rotationOne;
	case 2:
		rotationTimer = rotationTwo;
	case 3:
		rotationTimer = rotationThree;
	}
}
