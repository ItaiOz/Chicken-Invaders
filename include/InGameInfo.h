#pragma once

#include <SFML/Graphics.hpp>
#include "Files.h"

class InGameInfo
{
public:
	enum Objects
	{
		BannerScoring,
		Scoring,
		level,
		life1,
		Banner,	
		life,
		Banner2,
		max
	};

	InGameInfo(bool two_players = true);
	void setplayer(bool players);
	void setPosition();
	void setScoring(int i = 0) { m_Scoring = i; };
	void setlife(int i = 5) { m_life = i; };
	void setlifesecond(int i = 0) { m_lifeSecond = i; };
	void setlevel(int i ) { m_level = i; };

	void runMenu() {};
	void draw(sf::RenderTarget& target);
	~InGameInfo() = default;
	void setScoringtosprite();
	bool getNumOfPlayers();

private:
	sf::Font m_font;
	std::vector <sf::Sprite> m_sprite;
	std::vector <sf::Text> m_Scorin_print;
	int m_Scoring;
	int m_life;
	int m_level;
	int m_lifeSecond;
	bool m_two_players = false;
};


