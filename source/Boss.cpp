#include "Boss.h"

void Boss::approachSpaceship(sf::Vector2f position)
{
	float x, y;

	x = getPosition().x - position.x;
	y = getPosition().y - position.y;

	if (abs(x) > 150.0f) (x < 0) ? setDirection({ 5, 5 }) : setDirection({ -5, 5 });
	else (x < 0) ? setDirection({ 5, 0 }) : setDirection({-5, 0});


	//if (abs(y) < abs(x)) (x < 0)? setDirection({ -5, 0 }) : setDirection({ 5, 0 });

	//else (y < 0)?setDirection({ 0, -5 }): setDirection({ 0, 5 });
}
