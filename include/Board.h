#pragma once

#include "Global.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>  
#include <list>  

class Board
{
public:
	Board();

	void increaseLevel() { m_level++; };

	bool bossMode()const { return(m_line.empty()); };
	bool endGame()const { return(m_levels.empty()) ;};

	int getLevel()const { return m_level; };
	
	Board& instance();
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

	void getnewline();
	int getData();

	~Board() {};
private:
	int m_level = 1;
	std::list <std::string> m_levels;
	std::list <int> m_line;
	std::ifstream m_file;
};

