#pragma once

#include <SFML/Graphics.hpp>
#include "GameController.h"
#include <set>
#include "Button.h"
#include "InGameInfo.h"
#include "Global.h"
#include <Audio.h>


typedef std::multimap< int, std::string> scores;

class Menu
{
public:
	Menu();

	void run();
	void draw();
	void setHall(int i, std::string name);
	~Menu() {};

private:
	bool setName(int player);
	void drawName(std::vector <sf::Text>& name, Button& m_ok, Button& m_back);
	void drawScreenhall(std::vector < sf::Text >& name_prints, Button& m_But);
	void drawScreenum_of_Player();
	void drawstars();
	void printScreen();
	void drawScreenPlayer();
	void MenuState();
	void startGame(bool m_player);
	
	void buttonState();
	void printhall(); 
	void drowHelp(Button& m_back);
	void PrintHelp();

	float m_deltaTime;
	sf::Clock m_clock;
	sf::Font m_font;
	std::array<sf::Vertex, 600> m_stars_array;
	sf::RenderWindow m_window;
	std::vector<Button> m_Buttons;
	std::vector<Button> m_Buttons_players;
	Button m_fork;
	GameController* m_controller;
	sf::View fixed; 
	Audio startSuond;

	std::string m_name;

	scores m_names;

	sf::Sprite m_menuSprite;
	sf::Sprite m_help;
};
