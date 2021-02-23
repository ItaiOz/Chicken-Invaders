#include "Colission.h"

// primary collision-processing functions
typedef void(*HitFunctionPtr)(BaseObject&, BaseObject&);
typedef std::map<std::pair<std::string, std::string>, HitFunctionPtr> HitMap;

namespace {
	void bulletInChicken(BaseObject& bullet, BaseObject& chicken)
	{
		Bullet& bulletRef = static_cast<Bullet&>(bullet);
		Chicken& chickenRef = static_cast<Chicken&>(chicken);
		chickenRef.setRemove();
		//play hit sound
		bulletRef.setRemove(); //bulet is now not available will be erased
	}

	void eggInSpaceship(BaseObject& egg, BaseObject& player)
	{
		Egg& eggRef = static_cast<Egg&>(egg);
		Spaceship& playerRef = static_cast<Spaceship&>(player);
		playerRef.setRemove();
		playerRef.decreaseBullet();
		playerRef.decreaseLife();
		//audio
		eggRef.setRemove();
	}

	void asteroidInSpaceship(BaseObject& asteroid, BaseObject& player)
	{
		Asteroid& asteroidRef = static_cast<Asteroid&>(asteroid);
		Spaceship& playerRef = static_cast<Spaceship&>(player);
		playerRef.setRemove();
		playerRef.decreaseBullet();
		playerRef.decreaseLife();
		asteroidRef.setRemove();
	}

	void bulletInAsteroid(BaseObject& asteroid, BaseObject& bullet)
	{
		Asteroid& asteroidRef = static_cast<Asteroid&>(asteroid);
		Bullet& bulletRef = static_cast<Bullet&>(bullet);
		asteroidRef.setRemove();
		bulletRef.setRemove();
	}

	void bonusInSpaceship(BaseObject& bonus, BaseObject& spaceship)
	{
		PointsBonus& bonusRef = static_cast<PointsBonus&>(bonus);
		Spaceship& playerRef = static_cast<Spaceship&>(spaceship);
		bonusRef.setRemove();
		playerRef.increasePoints(BONUS_POINTS);
	}
	
	void shootingBonusInSpaceship(BaseObject& bonus, BaseObject& spaceship)
	{
		ShootingBonus& shotBonusRef = static_cast<ShootingBonus&>(bonus);
		Spaceship& playerRef = static_cast<Spaceship&>(spaceship);
		shotBonusRef.setRemove();
		playerRef.increasePoints(SHOOTING_POINTS);
		playerRef.increaseBullet();
		//change shooting sprite
	}

	void chickenInSpaceship(BaseObject& chicken, BaseObject& spaceship)
	{
		Chicken& chickenRef = static_cast<Chicken&>(chicken);
		Spaceship& playerRef = static_cast<Spaceship&>(spaceship);
		chickenRef.setRemove();
		playerRef.setRemove();
		playerRef.decreaseBullet();
		playerRef.decreaseLife();
		//change shooting sprite
	}

	void bossInSpaceship(BaseObject& boss, BaseObject& spaceship)
	{
		Boss& bossRef = static_cast<Boss&>(boss);
		Spaceship& playerRef = static_cast<Spaceship&>(spaceship);
		playerRef.setRemove();
		playerRef.decreaseBullet();
		playerRef.decreaseLife();
	}

	void bulletInBoss(BaseObject& bullet, BaseObject& boss)
	{
		Bullet& bulletRef = static_cast<Bullet&>(bullet);
		Boss& bossRef = static_cast<Boss&>(boss);
		bulletRef.setRemove();
		if(bossRef.getBossPower() == 0) bossRef.setRemove();
		bossRef.decreasePower();
		//boss - downgrade health
	}

	std::unique_ptr<HitMap> initializeCollisionMap() {
		auto phm = std::make_unique<HitMap>();

		(*phm)[std::make_pair(typeid(Bullet).name(), typeid(Chicken).name())] = &bulletInChicken;
		(*phm)[std::make_pair(typeid(Egg).name(), typeid(Spaceship).name())] = &eggInSpaceship;
		(*phm)[std::make_pair(typeid(Asteroid).name(), typeid(Spaceship).name())] = &asteroidInSpaceship;
		(*phm)[std::make_pair(typeid(Asteroid).name(), typeid(Bullet).name())] = &bulletInAsteroid;
		(*phm)[std::make_pair(typeid(PointsBonus).name(), typeid(Spaceship).name())] = &bonusInSpaceship;
		(*phm)[std::make_pair(typeid(ShootingBonus).name(), typeid(Spaceship).name())] = &shootingBonusInSpaceship;
		(*phm)[std::make_pair(typeid(Chicken).name(), typeid(Spaceship).name())] = &chickenInSpaceship;
		(*phm)[std::make_pair(typeid(Boss).name(), typeid(Spaceship).name())] = &bossInSpaceship;
		(*phm)[std::make_pair(typeid(Bullet).name(), typeid(Boss).name())] = &bulletInBoss;
		return phm;
	}

	HitFunctionPtr lookup(const std::string& class1, const std::string& class2) {
		static std::unique_ptr<HitMap>
			collisionMap(initializeCollisionMap());

		auto mapEntry = collisionMap->find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap->end())
			return nullptr;
		return (*mapEntry).second;
	}
} // end namespace

void Colission::processCollision(BaseObject& object1, BaseObject& object2)
{
    auto phf = lookup(typeid(object1).name(), typeid(object2).name());
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);

}
