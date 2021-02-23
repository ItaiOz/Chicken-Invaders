#pragma once

#include "Global.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>

class Files
{
public:
	enum Objects
	{
		stert_Background,
		Background,
		Spaceship,
		Chicken,
		bulletfirst,
		secondbullet,
		thirdbullet,
		save_the_world,
		help,
		egg,
		resume,
		sign,
		quit,
		hall_of_fame,
		back,
		font,
		asteroid,
		drumstick,
		burger,
		bonus,
		fries,
		Fork1,
		Fork2,
		ok,
		Banner,
		star,
		life,
		secondship1,
		secondship,
		ship1,
		boss,
		boss2,
		finish,
		gameover,
		level,
		helpBackground,
		explosion,
		oue,
		two,
		Max,
	};

	Files();
	static Files& instance();;

	Files(const Files&) = delete;
	Files& operator=(const Files&) = delete;

	sf::Sprite& getsprite(Objects object) { return m_data[object]; };
	sf::Font getfont(Objects object) const { if (object == Objects::font) return m_font; };

private:

	sf::Font m_font;
	std::vector< sf::Texture> m_texture;
	std::vector< sf::Sprite> m_data;
};