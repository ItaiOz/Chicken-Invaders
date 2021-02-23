#include "Files.h"
#include <stdexcept>



Files& Files::instance()
{
	static Files instance;
	return instance;
}


Files::Files() : m_data(Max), m_texture(Max)
{

	if ((
		!m_texture[helpBackground].loadFromFile("help.png") ||
		!m_texture[level].loadFromFile("level.png") ||
		!m_texture[oue].loadFromFile("oue.png") ||
		!m_texture[two].loadFromFile("two.png") ||
		!m_texture[explosion].loadFromFile("Explosion.png") ||
		!m_texture[secondship1].loadFromFile("secondship1.png") ||
		!m_texture[secondship].loadFromFile("secondship.png") ||
		!m_texture[ship1].loadFromFile("ship1.png") ||
		!m_texture[gameover].loadFromFile("gameover.png") ||
		!m_texture[finish].loadFromFile("finishpng.png") ||
		!m_texture[life].loadFromFile("life.png") ||
		!m_texture[boss2].loadFromFile("boss2.png") ||
		!m_texture[ok].loadFromFile("ok.png") ||
		!m_texture[star].loadFromFile("ster.png") ||
		!m_texture[Banner].loadFromFile("Banner.png") ||
		!m_texture[Fork1].loadFromFile("Fork1.png") ||
		!m_texture[Fork2].loadFromFile("Fork2.png") ||
		!m_texture[asteroid].loadFromFile("asteroid.png") ||
		!m_texture[boss].loadFromFile("boss.png") ||
		!m_texture[secondbullet].loadFromFile("firesmall.png") ||
		!m_texture[thirdbullet].loadFromFile("thirdbullet.png") ||
		!m_texture[fries].loadFromFile("fries.png") ||
		!m_texture[bonus].loadFromFile("bonus.png") ||
		!m_texture[burger].loadFromFile("burger.png") ||
		!m_texture[drumstick].loadFromFile("drumstick.png") ||
		!m_texture[egg].loadFromFile("egg.png") ||
		!m_texture[Background].loadFromFile("620478.jpg")) ||
		(!m_texture[Spaceship].loadFromFile("ship.png")) ||
		(!m_texture[stert_Background].loadFromFile("start.png")) ||
		(!m_texture[Chicken].loadFromFile("chickenSpriteSheet.png")) ||
		(!m_texture[bulletfirst].loadFromFile("bulletfirst.png")) ||
		(!m_texture[save_the_world].loadFromFile("3.png")) ||
		(!m_texture[sign].loadFromFile("2.png")) ||
		(!m_texture[quit].loadFromFile("4.png")) ||
		(!m_texture[help].loadFromFile("5.png")) ||
		(!m_texture[hall_of_fame].loadFromFile("6.png")) ||
		(!m_texture[resume].loadFromFile("7.png")) ||
		(!m_texture[back].loadFromFile("8.png")))
	{
		throw std::runtime_error("Can't load file");
	}

	if (!m_font.loadFromFile("Oswald-Bold.ttf"))
	{
		throw std::runtime_error("Can't load file");
	}

	m_data[oue].setTexture(m_texture[oue]);
	m_data[helpBackground].setTexture(m_texture[helpBackground]);
	m_data[two].setTexture(m_texture[two]);
	m_data[secondship1].setTexture(m_texture[secondship1]);
	m_data[level].setTexture(m_texture[level]);
	m_data[ship1].setTexture(m_texture[ship1]);
	m_data[boss2].setTexture(m_texture[boss2]);
	m_data[Background].setTexture(m_texture[Background]);
	m_data[Spaceship].setTexture(m_texture[Spaceship]);
	m_data[Chicken].setTexture(m_texture[Chicken]);
	m_data[bulletfirst].setTexture(m_texture[bulletfirst]);
	m_data[egg].setTexture(m_texture[egg]);
	m_data[asteroid].setTexture(m_texture[asteroid]);
	m_data[drumstick].setTexture(m_texture[drumstick]);
	m_data[burger].setTexture(m_texture[burger]);
	m_data[bonus].setTexture(m_texture[bonus]);
	m_data[fries].setTexture(m_texture[fries]);
	m_data[secondbullet].setTexture(m_texture[secondbullet]);
	m_data[thirdbullet].setTexture(m_texture[thirdbullet]);
	m_data[boss].setTexture(m_texture[boss]);
	m_data[gameover].setTexture(m_texture[gameover]);
	m_data[finish].setTexture(m_texture[finish]);
	m_data[explosion].setTexture(m_texture[explosion]);
	m_data[secondship].setTexture(m_texture[secondship]);
	//---------------------menu textures---------------------------
	m_data[save_the_world].setTexture(m_texture[save_the_world]);
	m_data[quit].setTexture(m_texture[quit]);
	m_data[help].setTexture(m_texture[help]);
	m_data[hall_of_fame].setTexture(m_texture[hall_of_fame]);
	m_data[back].setTexture(m_texture[back]);
	m_data[resume].setTexture(m_texture[resume]);
	m_data[sign].setTexture(m_texture[sign]);
	m_data[stert_Background].setTexture(m_texture[stert_Background]);
	m_data[life].setTexture(m_texture[life]);
	m_data[star].setTexture(m_texture[star]);
	m_data[Banner].setTexture(m_texture[Banner]);
	m_data[ok].setTexture(m_texture[ok]);
	m_data[Fork2].setTexture(m_texture[Fork2]);
	m_data[Fork1].setTexture(m_texture[Fork1]);

}