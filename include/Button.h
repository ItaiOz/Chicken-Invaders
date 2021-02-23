#pragma once

#include"Files.h"
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(Files::Objects but);
	void draw(sf::RenderTarget& target) const { target.draw(m_sprite); }
	~Button() = default;
	bool onButton(sf::Vector2i mousePos);
	Files::Objects gatObjects();
	void setClicking(sf::Vector2i mousePos);
	void setNoclicking(sf::Vector2i mousePos);

private:
	sf::Vector2f toVector(Files::Objects but);
	sf::Sprite m_sprite;
	Files::Objects typs;
};


