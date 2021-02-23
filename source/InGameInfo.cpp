#include "InGameInfo.h"

InGameInfo::InGameInfo(bool two_players) :m_sprite(max), m_life(5), m_Scorin_print(max)
, m_Scoring(0), m_level(1), m_two_players(two_players)
, m_lifeSecond(5)
{
    m_font = Files::instance().getfont(Files::Objects::font);
    m_sprite[Scoring] = Files::instance().getsprite(Files::Objects::star);
    m_sprite[level] = Files::instance().getsprite(Files::Objects::level);
    m_sprite[life1] = Files::instance().getsprite(Files::Objects::ship1);
    m_sprite[Banner] = Files::instance().getsprite(Files::Objects::Banner);
    m_sprite[Banner2] = Files::instance().getsprite(Files::Objects::Banner);
    m_sprite[life] = Files::instance().getsprite(Files::Objects::secondship1);
    setPosition();
}

void InGameInfo::setplayer(bool players)
{ 
    m_two_players = players;
  if (m_two_players == false)
    {
        m_sprite.resize(5);
        m_Scorin_print.resize(5);
    }
 }


void InGameInfo::setPosition()
{
    m_sprite[Banner].setPosition(sf::Vector2f(-130,750));
    m_sprite[Banner2].setScale(-1, 1);
    m_sprite[Banner2].setPosition(sf::Vector2f(1130, 750));


    m_sprite[Scoring].setScale(sf::Vector2f(0.6, 0.6));
    m_sprite[Scoring].setPosition(sf::Vector2f(500, 770));
    m_sprite[life1].setScale(sf::Vector2f(0.85, 0.85));
    m_sprite[life1].setPosition(sf::Vector2f(25, 763));

     m_sprite[level].setScale(sf::Vector2f(0.055, 0.055));
     m_sprite[level].setPosition(sf::Vector2f(440, 765));

     m_sprite[life].setScale(sf::Vector2f(0.85, 0.85));
     m_sprite[life].setPosition(sf::Vector2f(920, 763));


    m_Scorin_print[level].setFont(m_font);
    m_Scorin_print[level].setOutlineColor(sf::Color::Black);
    m_Scorin_print[level].setOutlineThickness(1.0f);
    m_Scorin_print[level].setCharacterSize(20);

    m_Scorin_print[life1].setFont(m_font);
    m_Scorin_print[life1].setOutlineColor(sf::Color::Black);
    m_Scorin_print[life1].setOutlineThickness(1.0f);
    m_Scorin_print[life1].setCharacterSize(20);

    m_Scorin_print[Scoring].setFont(m_font);
    m_Scorin_print[Scoring].setOutlineColor(sf::Color::Black);
    m_Scorin_print[Scoring].setOutlineThickness(1.0f);
    m_Scorin_print[Scoring].setCharacterSize(20);


    m_Scorin_print[life1].setPosition(sf::Vector2f(sf::Vector2f(65, 773)));


    m_Scorin_print[level].setPosition(sf::Vector2f(sf::Vector2f(480, 773)));
    m_Scorin_print[Scoring].setPosition(sf::Vector2f(sf::Vector2f(530, 773)));

    m_Scorin_print[life].setFont(m_font);
    m_Scorin_print[life].setOutlineColor(sf::Color::Black);
    m_Scorin_print[life].setOutlineThickness(1.0f);
    m_Scorin_print[life].setCharacterSize(20);
    m_Scorin_print[life].setPosition(sf::Vector2f(960, 773));
    

    setScoringtosprite();
}
void InGameInfo::draw(sf::RenderTarget& target)
{
    setScoringtosprite();
    for (auto& i : m_sprite)
        target.draw(i);
    for (auto& i : m_Scorin_print)
        target.draw(i);
}

void InGameInfo::setScoringtosprite()
{
    m_Scorin_print[life1].setString(std::to_string(m_life));
    m_Scorin_print[Scoring].setString(std::to_string(m_Scoring));
    m_Scorin_print[level].setString(std::to_string(m_level));
    if (m_two_players)
    //----------------
    m_Scorin_print[life].setString(std::to_string(m_lifeSecond));
}
bool InGameInfo::getNumOfPlayers(){
    return m_two_players;
}
