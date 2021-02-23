
#include "Button.h"


Button::Button(Files::Objects but)
{

    m_sprite = Files::instance().getsprite(but);
    m_sprite.setPosition(sf::Vector2f(toVector(but)));
    m_sprite.setColor(sf::Color::White);
    typs = but;
}
void Button::setClicking(sf::Vector2i mousePos)
{
    if (gatObjects() == Files::Objects::Fork1) {
        m_sprite = Files::instance().getsprite(Files::Objects::Fork2);
        m_sprite.setPosition(sf::Vector2f(mousePos));
    }


}
void Button::setNoclicking(sf::Vector2i mousePos)
{
    if (gatObjects() == Files::Objects::Fork1 || gatObjects() == Files::Objects::Fork2) {
        m_sprite = Files::instance().getsprite(Files::Objects::Fork1);
        m_sprite.setPosition(sf::Vector2f(mousePos));
    }
}


sf::Vector2f Button::toVector(Files::Objects but)
{
    switch (but)
    {
    case Files::Objects::sign:
        return { 200 , 50 };
    case Files::Objects::quit:
        return { 100 , 650 };
    case Files::Objects::back:
        return { 700, 650 };
    case Files::Objects::help:
        return { 400, 550 };  
    case Files::Objects::two:
        return { 400, 450 };
    case Files::Objects::hall_of_fame:
        return { 400, 450 };
    case Files::Objects::oue:
        return { 400, 350 };
    case Files::Objects::save_the_world:
        return { 400, 350 };
    case Files::Objects::Fork1:
        return { 0,0 };
    case Files::Objects::Fork2:
        return { 0,0 };
    case Files::Objects::ok:
        return { 400,500 };
    default:
        throw std::runtime_error("Unknown direction");
    }
}

bool Button::onButton(sf::Vector2i mousePos)
{
    //for (m_index = 0; m_index < OPTIONS - 1; m_index++)
    if (((float)mousePos.x > m_sprite.getGlobalBounds().left &&
        (float)mousePos.x < m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width)
        && ((float)mousePos.y > m_sprite.getGlobalBounds().top &&
            (float)mousePos.y < m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height))
    {
        if (gatObjects() != Files::Objects::sign)
            m_sprite.setColor(sf::Color::Blue);
        return true;
    }
    m_sprite.setColor(sf::Color::White);
    return false;
}
Files::Objects Button::gatObjects()
{
    return typs;
}

