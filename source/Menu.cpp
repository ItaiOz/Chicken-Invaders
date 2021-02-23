#include "Menu.h"


Menu::Menu()
	:m_window(sf::VideoMode(1000, 800), "Chicken Invaders", sf::Style::Close),
	m_font(Files::instance().getfont(Files::Objects::font)),
	m_fork(Files::Objects::Fork1), m_name("")
{
	for (auto& s : m_stars_array)
		s.position = { (float)(rand() % (int)WINDOW_WIDTH), (float)(rand() % (int)WINDOW_HEIGHT) };
	MenuState();
	buttonState();
	m_help = Files::instance().getsprite(Files::Objects::helpBackground);
	m_help.setScale(.62, .62);
}


void Menu::run()
{
	m_window.setMouseCursorVisible(false);
	sf::Event event;
	fixed = m_window.getView();
	
	while (m_window.isOpen())
	{
		startSuond.playMenuSound();
		m_deltaTime = m_clock.restart().asSeconds();
		printScreen();
		
		while (m_window.pollEvent(event))
		{
		
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}

			case sf::Event::MouseMoved: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				for (auto& i : m_Buttons) {
					i.onButton(mousePos);
				}
				m_fork.setNoclicking(mousePos);
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				m_fork.setClicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				break;
			}
			case sf::Event::MouseButtonReleased: {

				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				for (auto& i : m_Buttons)
				{
					if (i.onButton(mousePos))
					{
						switch (i.gatObjects())
						{
						case Files::Objects::quit:
							m_window.close();
						case Files::Objects::save_the_world:
						{
							drawScreenum_of_Player();
						
							break;
						}
						case Files::Objects::hall_of_fame:
						{
							printhall();
							break;
						}
						case Files::Objects::help:
						{
							PrintHelp();
							break;
						}
						}
					}
				
				}

			}
			default:
			
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
			}
			
		}
	}
}

void Menu::draw()
{
	drawstars();
	m_window.draw(m_menuSprite);
	for (auto& j : m_Buttons)
		j.draw(m_window);
	m_fork.draw(m_window);
}

void Menu::drawstars()
{
	for (auto& s : m_stars_array) {
		s.position.y += 20.0 * m_deltaTime;
		if (s.position.y > WINDOW_HEIGHT) s.position = { (float)(rand() % (int)WINDOW_WIDTH), 0 };
		m_window.draw(&s, 1, sf::Points);
	}
}

void Menu::printScreen()
{
	m_window.clear();
	draw();
	m_window.setView(fixed);
	m_window.display();
}

void Menu::setHall(int i, std::string name)
{
	m_names.insert(scores::value_type(i, name));
}


void Menu::startGame(bool m_player ) 
{
	startSuond.stopMenuMusic();
	std::unique_ptr<GameController> m_controller = std::make_unique <GameController>(m_player);
	m_controller->runGame(m_window);
	setHall(m_controller->getPoints(), m_name);
}

void Menu::MenuState()
{
	m_menuSprite = Files::instance().getsprite(Files::stert_Background);
	sf::Vector2f targetSize(1000.0f, 800.0f);
	m_menuSprite.setScale(targetSize.x / m_menuSprite.getLocalBounds().width,
		targetSize.y / m_menuSprite.getLocalBounds().height);

}


void Menu::buttonState()
{
	m_Buttons.push_back(Files::quit);
	m_Buttons.push_back(Files::help);
	m_Buttons.push_back(Files::save_the_world);
	m_Buttons.push_back(Files::hall_of_fame);
	m_Buttons.push_back(Files::sign);

	m_Buttons_players.push_back(Files::back);
	m_Buttons_players.push_back(Files::oue);
	m_Buttons_players.push_back(Files::two);

}

void Menu::printhall()
{

	
	m_deltaTime = m_clock.restart().asSeconds();

	//std::string m_hail()  ;
	std::vector < sf::Text >  names_print;
	sf::Text name_line;
	name_line.setOutlineColor(sf::Color::Black);
	name_line.setOutlineThickness(1.0f);
	name_line.setCharacterSize(45);
	name_line.setFont(m_font);
	int i = 1;
	for (auto iter = m_names.rbegin(); iter != m_names.rend(); ++iter)
	{
		name_line.setString(std::to_string(i) + ". " + (iter->second));
		sf::Vector2f targetSize(m_menuSprite.getGlobalBounds().width  / 8,
			i*(m_menuSprite.getGlobalBounds().height - (float)name_line.getGlobalBounds().height) / 10);
		name_line.setPosition(targetSize);
		names_print.push_back(name_line);
		name_line.setString(std::to_string(i) + ". " + (iter->second));
		sf::Vector2f target(m_menuSprite.getGlobalBounds().width / 2,
			i * (m_menuSprite.getGlobalBounds().height - (float)name_line.getGlobalBounds().height) / 10);
		name_line.setString(std::to_string(iter->first));
		name_line.setPosition(target);
		names_print.push_back(name_line);
		
		if (i++ == 9)
			break;
	}

	
	Button m_But(Files::back);
	m_window.setMouseCursorVisible(false);
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();
		drawScreenhall(names_print, m_But);
		sf::Event event;
		while (m_window.pollEvent(event))
		{
	
			
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::MouseMoved:{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				m_But.onButton(mousePos);
				m_fork.setNoclicking(mousePos);
				break;
			}
			case sf::Event::MouseButtonPressed:{
				m_fork.setClicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				break;
			}
			case sf::Event::MouseButtonReleased:{
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				if (m_But.onButton(mousePos))
					return;
			}
			default:
			{
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
			}

			}

		}
	}
}

void Menu::drawScreenhall(std::vector < sf::Text >& name_prints, Button& m_But)
{
	m_window.clear();
	drawstars();
	m_window.draw(m_menuSprite);
	for (auto&i: name_prints)
	m_window.draw(i);
	m_But.draw(m_window);
	m_fork.draw(m_window);
	m_window.setView(fixed);
	m_window.display();
}


bool Menu::setName(int  player_2)
{
	std::vector <sf::Text >names;
	Button m_ok(Files::ok);
	Button m_back(Files::back);
	sf::Text name;
	name.setFont(m_font);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(3.0f);
	name.setCharacterSize(50);
	names.push_back(name);
	if (player_2 == 1)
	{
		names[0].setString("Enter player's name:");
	}else
		names[0].setString("Enter two players names:");
	names.push_back(name);
	int j = 1;
	for (auto& i : names)
	{
		sf::Vector2f targetSize(((m_menuSprite.getGlobalBounds().width - (float)i.getGlobalBounds().width)) / 2,
			(float)(j++ * 150));
		i.setPosition(targetSize);
	}
	m_window.setMouseCursorVisible(false);
	while (m_window.isOpen())
	{

		m_deltaTime = m_clock.restart().asSeconds();
		drawName(names, m_ok, m_back);
		sf::Event event;
		while (m_window.pollEvent(event))
		{
		
			switch (event.type)
			{

			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::MouseMoved:
			{

				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				m_ok.onButton(mousePos);
				m_back.onButton(mousePos);
				m_fork.setNoclicking(mousePos);
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				m_fork.setClicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				if (m_ok.onButton(mousePos))
					return true;
				if (m_back.onButton(mousePos))
					return false;
			}
			case sf::Event::TextEntered:
			{
				if (event.text.unicode < 128)
				{
					if (event.text.unicode == 8)
					{
						if (m_name.size() == 0)
							m_name = "";
						else
							m_name.erase(m_name.end() - 1);
					}
					 else if (event.text.unicode != 0 && m_name.size() < 12)
						m_name += static_cast<char>(event.text.unicode);
					if (event.text.unicode == 13)
						return true;

					names[1].setString(m_name);
					sf::Vector2f targetSize((
						(m_menuSprite.getGlobalBounds().width - (float)names[1].getGlobalBounds().width)) / 2,
						(float)300);
					names[1].setPosition(targetSize);
				}
			}
			default:
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
			}

		}
	}
	return false ;
}
void Menu::drawName(std::vector <sf::Text>& name, Button& m_ok , Button& m_back)
{

	m_window.clear();
	drawstars();
	m_window.draw(m_menuSprite);
	for (auto& i : name)
		m_window.draw(i);
	m_ok.draw(m_window);
	m_back.draw(m_window);
	m_fork.draw(m_window);
	m_window.setView(fixed);
	m_window.display();

}


void Menu::drawScreenPlayer()
{
	m_window.clear();
	drawstars();
		m_window.draw(m_menuSprite);
		for (auto& j : m_Buttons_players)
			j.draw(m_window);
		m_fork.draw(m_window);
		m_window.setView(fixed);
		m_window.display();
}

void Menu::drawScreenum_of_Player()
{
	m_window.setMouseCursorVisible(false);
	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();
		drawScreenPlayer();
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			m_deltaTime = m_clock.restart().asSeconds();
			// kmhhue 
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::MouseMoved: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				for (auto& i : m_Buttons_players)
					i.onButton(mousePos);
				m_fork.setNoclicking(mousePos);
				break;
			}
			case sf::Event::MouseButtonPressed: {
				m_fork.setClicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				break;
			}
			case sf::Event::MouseButtonReleased: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				for (auto& i : m_Buttons_players)
				{
					if (i.onButton(mousePos))
					{
						switch (i.gatObjects())
						{
						case Files::Objects::quit:
							m_window.close();
						case Files::Objects::back:
						{
							return ;
						}
						case Files::Objects::oue:
						{
							if (setName(1))
								startGame(0);
							break;
						}
						case Files::Objects::two:
						{
							if (setName(2))
								startGame(true);
							break;
						}
						}
					}
				}
			}
			default:
			{
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
			}

			}

		}
	}
}

void Menu::drowHelp(Button& m_back)
{
	m_window.clear();
	drawstars();
	m_fork.draw(m_window);
	m_window.draw(m_help);
	m_back.draw(m_window);
	m_window.setView(fixed);
	m_window.display();
}
void Menu::PrintHelp()
{
	Button m_back(Files::back);

	while (m_window.isOpen())
	{
		m_deltaTime = m_clock.restart().asSeconds();
		drowHelp(m_back);
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				m_window.close();
				break;
			}
			case sf::Event::MouseMoved: {
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				m_back.onButton(mousePos);
				m_fork.setNoclicking(mousePos);
				break;
			}
			case sf::Event::MouseButtonPressed: {
				m_fork.setClicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				break;
			}
			case sf::Event::MouseButtonReleased: {
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
				sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
				if (m_back.onButton(mousePos))
					return;
			}
			default:
			{
				m_fork.setNoclicking(static_cast<sf::Vector2i>(sf::Mouse::getPosition(m_window)));
			}

			}
		}
	}
}
