#pragma once

#include <string>
#include <map>
#include <iostream>
#include <typeinfo>
#include "BaseObject.h"
#include "Chicken.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Files.h"
#include "ShootingBonus.h"
#include "Boss.h"
#include "PointsBonus.h"
#include "Egg.h"
#include "Bonus.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

class Colission
{
public:
	Colission() = default;

	void processCollision(BaseObject& object1, BaseObject& object2);
    ~Colission() = default;
private:
};

struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(BaseObject& a, BaseObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};