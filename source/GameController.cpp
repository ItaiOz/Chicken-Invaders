#include "GameController.h"

#include <SFML/Graphics.hpp>

enum Direction { up, down, left, right };

GameController::GameController(bool numOfPlayer)
{
	m_sprite_back[m_current_background] = Files::instance().getsprite(Files::Objects::Background);
	m_sprite_back[m_other_background] = Files::instance().getsprite(Files::Objects::Background);
	m_sprite_back[0].setPosition(0, 0);
	m_sprite_back[1].setPosition(0, 0 - m_sprite_back->getGlobalBounds().height);

	m_stages[0] = Files::instance().getsprite(Files::Objects::gameover);
	m_stages[1] = Files::instance().getsprite(Files::Objects::finish);

	m_stages[0].setPosition(-110, 0);
	m_stages[1].setPosition(0, 0);

	m_blow.loadFromFile("Explosion.png");

	m_in_game_info = std::make_unique <InGameInfo>();
	m_in_game_info->setplayer(numOfPlayer);
	pic_pos = 0 - m_sprite_back->getGlobalBounds().height;
	secondPlayer = numOfPlayer;

	m_player = std::make_unique<Spaceship>(sf::Vector2f((WINDOW_WIDTH / 3) - 25.0f, WINDOW_HEIGHT + 100.0f), Files::instance().getsprite(Files::Objects::Spaceship));
	if (secondPlayer)
		m_player2 = std::make_unique<Spaceship>(sf::Vector2f((WINDOW_WIDTH * 0.66) - 25.0f, WINDOW_HEIGHT + 100.0f), Files::instance().getsprite(Files::Objects::secondship));
	else { m_player2 = nullptr; }
}

void GameController::runGame(sf::RenderWindow& window)
{
	float deltaTime;
	float m_stars_speed = 20.0;

	sf::Clock chickens_clock;
	sf::Event event;

	window.setMouseCursorVisible(true);
	fire_clock.restart().asMilliseconds();

	while (window.isOpen() && (!game_won && !game_over))
	{
		deltaTime = m_clock.restart().asSeconds();
		draw(window, deltaTime);
		while (window.pollEvent(event))
		{
			switch (event.type)
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
		}
		(!inStartingPosition) ? getToPosition(window, deltaTime) : moveSpaceship(window, deltaTime);
		if (chickensMode) moveChickens(deltaTime);
		if (AsteroidsMode) moveAsteroids(deltaTime);
		if (!dontShowPlayer1) shoot(window);
		if (!dontShowPlayer2) shoot(window);
		moveObjects(deltaTime);
		checkColissions(window);
		updateBoard(window);

		if (bossMode) activateBossMode(deltaTime);

	}
}


void GameController::draw(sf::RenderWindow& window, float deltatime)
{
	window.clear();
	drawBackground(window, deltatime);

	for (auto& b : m_bullets)
		b.draw(window);

	for (auto& e : m_eggs)
		e.draw(window);

	for (auto& Iterator_i : m_chickens)
		for (auto& Iterator : Iterator_i)
			Iterator->draw(window);

	hide_ship_timer = m_hide_ship_clock.getElapsedTime().asSeconds();
	if (!dontShowPlayer1) m_player->draw(window);
	if (!dontShowPlayer2 && secondPlayer)m_player2->draw(window);

	else if (dontShowPlayer1 && hide_ship_timer > 2.0f) dontShowPlayer1 = false;
	else if (dontShowPlayer2 && hide_ship_timer > 2.0f) dontShowPlayer2 = false;

	if (bossMoves == 1)m_boss->draw(window);

	for (auto& b : m_bonuses)
		b->draw(window);


	for (auto& a : m_asteroids)
		a->draw(window);



	m_in_game_info->draw(window);

	window.display();
}

//function to draw the background
void GameController::drawBackground(sf::RenderWindow& window, float deltaTime)
{
	if (betweenSubStages) { //substage in finished

		subStagesTimer = subStages_clock.restart().asSeconds();
		betweenSubStages = false;
	}

	subStagesTimer = subStages_clock.getElapsedTime().asSeconds();
	(subStagesTimer <= 4.0) ? backgroundSpeed = 60.0f : backgroundSpeed = 20.0;

	m_sprite_back[m_current_background].move(0, backgroundSpeed * deltaTime);
	window.draw(m_sprite_back[m_current_background]);
	if (m_sprite_back[m_current_background].getPosition().y > 0) {
		m_sprite_back[m_other_background].move(0, backgroundSpeed * deltaTime);
		window.draw(m_sprite_back[m_other_background]);
	}
	if (m_sprite_back[m_current_background].getPosition().y > WINDOW_HEIGHT) {
		std::swap(m_current_background, m_other_background);
		m_sprite_back[m_other_background].setPosition(0, pic_pos);
	}
}

void GameController::getToPosition(sf::RenderWindow& window, float deltaTime)
{
	if (secondPlayer)
	{
		m_player2->setDirection({ 0, -5 });
		m_player2->move(deltaTime * 5.0f);
	}
	m_player->setDirection({ 0, -5 });
	m_player->move(deltaTime * 5.0f);
	if (m_player->getPosition().y <= (WINDOW_HEIGHT - 100.0f)) { inStartingPosition = true; };
}

//function to move spaceship (and bullets) according to the arrows
void GameController::moveSpaceship(sf::RenderWindow& window, float deltaTime)
{
	m_player->setAnimation(up, m_player->getSprite());

	if (secondPlayer)
		m_player2->setAnimation(up, m_player2->getSprite());


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_player->setDirection({ 0 , -5 });
		if (m_player->getPosition().y > 0) { m_player->setAnimation(up, m_player->getSprite()); m_player->move(deltaTime * 35.0f); }
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_player->setDirection({ 0, 5 });
		if (m_player->getPosition().y + m_player->getGlobalBounds().height < WINDOW_HEIGHT) { m_player->setAnimation(down, m_player->getSprite()); m_player->move(deltaTime * 35.0f); }
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_player->setDirection({ 5, 0 });
		if (m_player->getPosition().x + m_player->getGlobalBounds().width < WINDOW_WIDTH) { m_player->setAnimation(right, m_player->getSprite()); m_player->move(deltaTime * 35.0f); }
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_player->setDirection({ -5, 0 });
		if (m_player->getPosition().x > 0) { m_player->setAnimation(left, m_player->getSprite()); m_player->move(deltaTime * 35.0f); }
	}
	if (secondPlayer) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_player2->setDirection({ 0 , -5 });
			if (m_player2->getPosition().y > 0) { m_player2->setAnimation(up, m_player2->getSprite()); m_player2->move(deltaTime * 35.0f); }
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_player2->setDirection({ 0, 5 });
			if (m_player2->getPosition().y + m_player2->getGlobalBounds().height < WINDOW_HEIGHT) { m_player2->setAnimation(down, m_player2->getSprite()); m_player2->move(deltaTime * 35.0f); }
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_player2->setDirection({ 5, 0 });
			if (m_player2->getPosition().x + m_player2->getGlobalBounds().width < WINDOW_WIDTH) { m_player2->setAnimation(right, m_player2->getSprite()); m_player2->move(deltaTime * 35.0f); }
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_player2->setDirection({ -5, 0 });
			if (m_player2->getPosition().x > 0) { m_player2->setAnimation(left, m_player2->getSprite()); m_player2->move(deltaTime * 35.0f); }
		}
	}
	if (!m_bullets.empty()) for (auto& b : m_bullets) {
		b.setDirection({ 0, -5 });
		b.move(deltaTime * 55.0f);
	}
}

void GameController::shoot(sf::RenderWindow& window)
{
	if (!dontShowPlayer1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			fire_rate = fire_clock.getElapsedTime().asSeconds();
			if (fire_rate >= fire_delay) {
				createBullet(window, PLAYER1);
				fire_clock.restart().asMilliseconds();
			}
		}
	}
	if (secondPlayer) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			fire_rate = fire_clock.getElapsedTime().asSeconds();
			if (fire_rate >= fire_delay) {
				createBullet(window, PLAYER2);
				fire_clock.restart().asMilliseconds();
			}
		}
	}
}

//fuction to move chickens
void GameController::moveChickens(float deltaTime)
{
	if (chickens_in_place == 0) initializeChickens();
	else if (chickens_in_place == 1) bringChickens(deltaTime);
	else if (chickens_in_place == 2) moveHorizonal(deltaTime);
	//function to move the chickens sinsusly
	else {
		chicken_movement += deltaTime;

		for (auto& ChickensIterator : m_chickens)
			for (auto& Iterator : ChickensIterator) {
				/*(Iterator->toBlow()) ? Iterator->setBlowAnimation(Iterator->getSprite()) : */
				Iterator->setAnimation(0, Iterator->getSprite());
				Iterator->moveSinusly(4.0f * cosf(chicken_movement) * deltaTime);
			}

		eggs_timer = eggs_clock.getElapsedTime().asSeconds();
		if (eggs_timer >= (float)8) eggs_clock.restart().asSeconds();

		for (auto& ChickensIterator : m_chickens)
			for (auto& Iterator : ChickensIterator)
				if (eggs_timer >= 0.0f && eggs_timer < 1.0f)
				{
					Iterator->resetHatched();
				}
				else if (!Iterator->isHatched() && eggs_timer >= (float)Iterator->getTimer()) {
					m_audio.playEggHatched();
					m_eggs.push_back(Egg(sf::Vector2f(Iterator->getPosition().x + 25.0f,
						Iterator->getPosition().y + 50), Files::instance().getsprite(Files::Objects::egg)));
					Iterator->setHatched();
				}
	}

}
void GameController::moveObjects(float deltaTime)
{
	if (!m_eggs.empty())
		for (auto& e : m_eggs) {
			if (!e.hitFloor()) {
				e.setDirection({ 0, 5 });
				e.move(deltaTime * 25.0f);
				if (e.getPosition().y >= WINDOW_HEIGHT - 100.0f) {
					m_audio.playEggOnGround();
					e.setAnimation(0, e.getSprite());
					e.setHit();
					e.restartTimer();
				}
			}
		}

	if (!m_bonuses.empty())
		for (auto& b : m_bonuses) {
			b->setDirection({ 0, 5 });
			b->move(deltaTime * 20.0f);
			if (b->toRotate()) b->rotate();
		}
}
void GameController::moveAsteroids(float deltaTime)
{
	(asteroids_in_place == 0) ? createAsteroids() : dropAsteroids(deltaTime);
}

//dropping the asteroids in diagonal angle
void GameController::dropAsteroids(float deltaTime)
{
	asteroids_timer = asteroids_clock.getElapsedTime().asSeconds();

	if (!m_asteroids.empty())
		for (auto& a : m_asteroids) {
			if (asteroids_timer > a->getDelay()) {
				a->setDirection({ 3, 4 });
				a->move(deltaTime * 10.0f * a->getSpeed());
				if (a->toRotate()) a->rotate();

			}
		}
}

//inserting asteroids into a list
void GameController::createAsteroids()
{
	int size = m_board.getData();

	sf::Vector2f position;

	for (int i = 0; i < size; i++) {
		position = calculateAsteroidPoisition();
		m_asteroids.emplace_back(std::make_unique<Asteroid>(position, Files::instance().getsprite(Files::Objects::asteroid)));
		m_asteroids[i]->initializeDelay();
		m_asteroids[i]->initializeSpeed();
		m_asteroids[i]->setRotationTimer();
	}
	asteroids_clock.restart().asSeconds();

	asteroids_in_place = 1;
}
//function to move the chickens down
void GameController::bringChickens(float deltaTime)
{
	float gap = 65.0f;

	//next loop is for putting chickens in their line
	int i = 0;
	for (auto& ChickensIterator : m_chickens)
	{
		for (auto& Iterator : ChickensIterator)
			if (Iterator->getPosition().y >= 30 + (i * gap)) Iterator->setStay();
		i++;
	}
	//if last chicken is in place - means we dont need to get this function anymore
	auto iterator = m_chickens.rbegin();
	auto j = *iterator->rbegin();
	if (j->isInPlace()) { chickens_in_place = 2; first_chickens = false; }


	for (auto& ChickensIterator : m_chickens)
		for (auto& Iterator : ChickensIterator)
			if (!Iterator->isInPlace())
			{
				Iterator->setDirection({ 0 , 5 });
				Iterator->setAnimation(0, Iterator->getSprite());
				(first_chickens == true) ? Iterator->move((deltaTime * 10.0f)) : Iterator->move((deltaTime * 25.0f));
			}
}

//function to move chickens sideways when getting to their positions
void GameController::moveHorizonal(float deltaTime)
{
	int random;
	for (auto& ChickensIterator : m_chickens)
		for (auto& Iterator : ChickensIterator) {
			random = rand() % 2;
			random == 1 ? Iterator->setDirection({ 5, 0 }) : Iterator->setDirection({ -5, 0 });
		}
	eggs_clock.restart().asSeconds(); //start counting from the moment chickens move horizonally
	chickens_in_place = 3;
}

//function to create chickens
void GameController::initializeChickens()
{
	int line = m_board.getData();
	int col = m_board.getData();

	float space = (float)(WINDOW_WIDTH / col) - 22.0f;

	int count = 0;

	m_chickens.resize(line);
	for (auto& Iterator : m_chickens)
		for (int j = 0; j < col; j++)
		{
			Iterator.emplace_back(std::make_shared<Chicken>(sf::Vector2f(space * (j + 1), -150.0f),
				Files::instance().getsprite(Files::Objects::Chicken)));
			count++;
			if (count % 3 == 0) Iterator[j]->initializeTimer(); // the zero is for choosing the chickens delay 
			Iterator[j]->setOriginalPoisition(Iterator[j]->getPosition());
		}
	chickens_in_place = 1;
	bonusNum = rand() % (line * col);
}

void GameController::checkColissions(sf::RenderWindow& window)
{
	for (auto& b : m_bullets)
		for (auto& ChickensIterator : m_chickens)
			for (auto& Iterator : ChickensIterator)
				if (b.getGlobalBounds().intersects(Iterator->getGlobalBounds())) {
					m_audio.playChickenDie();
					createBonus(window, { Iterator->getPosition().x + Iterator->getGlobalBounds().width / 2, Iterator->getPosition().y + Iterator->getGlobalBounds().height });
					m_colission.processCollision(b, *Iterator);
				}

	for (auto& ChickensIterator : m_chickens)
		for (auto& c : ChickensIterator)
			if (c->getGlobalBounds().intersects(m_player->getGlobalBounds())) {
				m_colission.processCollision(*c, *m_player); //m_audio.playPlayerHit();
			}

			else if (secondPlayer && c->getGlobalBounds().intersects(m_player2->getGlobalBounds())) {
				m_colission.processCollision(*c, *m_player2);//m_audio.playPlayerHit();
			}
	for (auto& b : m_bullets)
		for (auto& a : m_asteroids)
			if (b.getGlobalBounds().intersects(a->getGlobalBounds()))
				m_colission.processCollision(*a, b);

	if (!dontShowPlayer1 || !dontShowPlayer2)
	{
		for (auto& e : m_eggs)
			if (!e.hitFloor() && e.getGlobalBounds().intersects(m_player->getGlobalBounds())) {
				m_colission.processCollision(e, *m_player); //m_audio.playPlayerHit();
			}
			else if (secondPlayer && !e.hitFloor() && e.getGlobalBounds().intersects(m_player2->getGlobalBounds()))
				m_colission.processCollision(e, *m_player2);//m_audio.playPlayerHit();

		for (auto& b : m_bonuses)
			if (b->getGlobalBounds().intersects(m_player->getGlobalBounds())) {
				m_colission.processCollision(*b, *m_player); m_audio.playShootBonus();
			}
			else if (secondPlayer && b->getGlobalBounds().intersects(m_player2->getGlobalBounds())) {
				m_colission.processCollision(*b, *m_player2); m_audio.playShootBonus();
			}
		for (auto& a : m_asteroids)
			if (a->getGlobalBounds().intersects(m_player->getGlobalBounds()))
				m_colission.processCollision(*a, *m_player);
			else if (secondPlayer && a->getGlobalBounds().intersects(m_player2->getGlobalBounds()))
				m_colission.processCollision(*a, *m_player2);

		if (bossMode) {
			if (m_boss->getGlobalBounds().intersects(m_player->getGlobalBounds())) m_colission.processCollision(*m_boss, *m_player);
			for (auto& b : m_bullets)
				if (b.getGlobalBounds().intersects(m_boss->getGlobalBounds())) {
					m_colission.processCollision(b, *m_boss); m_audio.playBossHit();
				}
			if (secondPlayer && m_boss->getGlobalBounds().intersects(m_player2->getGlobalBounds())) m_colission.processCollision(*m_boss, *m_player2);
			for (auto& b : m_bullets) {
				if (b.getGlobalBounds().intersects(m_boss->getGlobalBounds())) m_colission.processCollision(b, *m_boss); m_audio.playBossHit();
			}
		}
		if(secondPlayer)
		m_in_game_info->setScoring(getPointsTwoplayers());
		else {m_in_game_info->setScoring(getPoints());}
			
		if (!dontShowPlayer1)
		m_in_game_info->setlife(getlife());
		if(secondPlayer)
		m_in_game_info->setlifesecond(getlife2());
		
	}
}
//creating bullets when player hits spcae
void GameController::createBullet(sf::RenderWindow& window, const int typeplayer)
{
	m_audio.playShoot();
	if (typeplayer == 0)
	{
		switch (m_player->getBulletLevel())
		{
		case 0:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player->getPosition().x + 19.0f, m_player->getPosition().y), Files::instance().getsprite(Files::Objects::bulletfirst)));//
			break;
		case 1:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player->getPosition().x + 19.0f, m_player->getPosition().y), Files::instance().getsprite(Files::Objects::secondbullet)));//
			break;
		case 2:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player->getPosition().x + 19.0f, m_player->getPosition().y), Files::instance().getsprite(Files::Objects::thirdbullet)));//
			break;
		}
	}
	if (secondPlayer && typeplayer == 1)
	{
		switch (m_player2->getBulletLevel())
		{
		case 0:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player2->getPosition().x + 19.0f, m_player2->getPosition().y), Files::instance().getsprite(Files::Objects::bulletfirst)));//
			break;
		case 1:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player2->getPosition().x + 19.0f, m_player2->getPosition().y), Files::instance().getsprite(Files::Objects::secondbullet)));//
			break;
		case 2:
			m_bullets.push_back(Bullet(sf::Vector2f(m_player2->getPosition().x + 19.0f, m_player2->getPosition().y), Files::instance().getsprite(Files::Objects::thirdbullet)));//
			break;
		}
	}
}
//creating bonus occur when chickens get shot
void GameController::createBonus(sf::RenderWindow& window, sf::Vector2f position)
{
	bonusCounter++;
	if (bonusCounter == bonusNum) m_bonuses.emplace_back(std::make_unique<ShootingBonus>(position, Files::instance().getsprite(Files::Objects::bonus)));
	else
	{
		int r = rand() % 3;
		switch (r) {
		case 0: m_bonuses.emplace_back(std::make_unique<PointsBonus>(position, Files::instance().getsprite(Files::Objects::burger)));
			break;
		case 1: m_bonuses.emplace_back(std::make_unique<PointsBonus>(position, Files::instance().getsprite(Files::Objects::drumstick)));
			break;
		case 2: m_bonuses.emplace_back(std::make_unique<PointsBonus>(position, Files::instance().getsprite(Files::Objects::fries)));
			break;
		}
	}
}

void GameController::activateBossMode(float deltaTime)
{
	if (bossMoves == 0) {
		if (m_board.getLevel() == 1)
			m_boss = std::make_unique<Boss>(sf::Vector2f((WINDOW_WIDTH / 2) - 150.0f, -350.0f), Files::instance().getsprite(Files::Objects::boss));// one is for boss delay

		else if (m_board.getLevel() == 2)
			m_boss = std::make_unique<Boss>(sf::Vector2f((WINDOW_WIDTH / 2) - 150.0f, -350.0f), Files::instance().getsprite(Files::Objects::boss2));

		boss_clock.restart().asSeconds();
		m_boss->setDirection({ 0, 5 });
		bossMoves = 1;
	}

	else
	{
		boss_timer = boss_clock.getElapsedTime().asSeconds();

		if (boss_timer >= 5.0) { boss_clock.restart().asSeconds(); m_boss->approachSpaceship(m_player->getPosition()); }
		checkBossPositions();
		m_boss->move(deltaTime * 15.0);
		hatchBossEggs();
	}
}

void GameController::checkBossPositions()
{
	if (m_boss->getPosition().x <= 0) { boss_clock.restart().asSeconds(); m_boss->setDirection({ 5, 0 }); }
	else if (m_boss->getGlobalBounds().width + m_boss->getPosition().x >= WINDOW_WIDTH) { boss_clock.restart().asSeconds(); m_boss->setDirection({ -5, 0 }); }
	else if (m_boss->getGlobalBounds().height + m_boss->getPosition().y >= WINDOW_HEIGHT - 100.0f) { boss_clock.restart().asSeconds(); m_boss->setDirection({ 0, -5 }); }
}

void GameController::hatchBossEggs()
{
	boss_egg_timer = boss_egg_clock.getElapsedTime();

	if (boss_egg_timer.asSeconds() > eggsDelay) {
		m_eggs.push_back(Egg(sf::Vector2f(m_boss->getPosition().x + m_boss->getGlobalBounds().width / 2,
			m_boss->getPosition().y + m_boss->getGlobalBounds().height), Files::instance().getsprite(Files::Objects::egg)));
		(m_eggs.size() >= 7) ? eggsDelay = 1.5f : eggsDelay = 0.5f;
		boss_egg_clock.restart().asMilliseconds();
	}
}

//reseting vars for the new level
void GameController::setNewLevel(sf::RenderWindow& window)
{
	if (!m_board.endGame()) {
		chickens_in_place = 0;
		asteroids_in_place = 0;
		bossMoves = 0;
		chickensMode = true;
		bool first_chickens = true;
		m_boss.reset();
		m_board.increaseLevel();
		bossMode = false;
		chickensMode = true;
		m_board.getnewline();
		m_level++;
		m_in_game_info->setlevel(m_level);
	}
	else gameWon(window);
}
//function to handle game end
void GameController::gameWon(sf::RenderWindow& window)
{
	sf::Clock clock;
	clock.restart().asSeconds();
	sf::Time time;

	while (1)
	{
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 3.0) break;
		window.clear();
		window.draw(m_stages[1]);
		window.display();
	}
	game_won = true;
}
//if game is over reaching here
void GameController::gameOver(sf::RenderWindow& window)
{
	m_audio.playgameOver();
	sf::Clock clock;
	clock.restart().asSeconds();
	sf::Time time;

	while (1)
	{
		time = clock.getElapsedTime();
		if (time.asSeconds() >= 3.0) break;
		window.clear();
		window.draw(m_stages[0]);
		window.display();
	}
	game_over = true;

}

//remove objects if needed
void GameController::updateBoard(sf::RenderWindow& window)
{
	//deleting from chickens vector
	for (auto& i : m_chickens)std::experimental::erase_if(i, [](const std::shared_ptr <Chicken>& chicken) {return chicken->toRemove(); });

	//deleting from asteroids vector
	std::experimental::erase_if(m_asteroids, [](const std::unique_ptr <Asteroid>& asteroid) {return (asteroid->toRemove() || asteroid->getGlobalBounds().top > WINDOW_HEIGHT); });

	//moving objects removal check
	m_bullets.remove_if([&](const Bullet& b) {return b.getPosition().y + b.getGlobalBounds().height < 0 || b.toRemove(); });
	m_eggs.remove_if([&](Egg& e) {return e.toRemove() || (e.hitFloor() && e.timesUp()); });
	m_bonuses.remove_if([](const std::unique_ptr <Bonus>& b) {return b->getPosition().y > WINDOW_HEIGHT || b->toRemove(); });

	//player remove
	if (m_player->toRemove()) { dontShowPlayer1 = true; m_player->resurrect() ;hide_ship_timer = m_hide_ship_clock.restart().asSeconds(); }

	if (secondPlayer)
		if (m_player2->toRemove()) { dontShowPlayer2 = true; m_player2->resurrect(); hide_ship_timer = m_hide_ship_clock.restart().asSeconds(); }

	if (bossMode) if (m_boss->toRemove()) {
		m_audio.playBossDie();
		setNewLevel(window);
		return;
	}

	if (AsteroidsMode)
		if (m_asteroids.empty()) {
			betweenSubStages = true;
			AsteroidsMode = false;
			if (!m_board.bossMode())chickensMode = true;
			asteroids_in_place = 0;
			return;
		}

	if (chickensMode) {
		static const auto empty = [](const auto& c) { return c.empty(); };
		if (std::all_of(std::begin(m_chickens), std::end(m_chickens), empty)) {
			betweenSubStages = true;
			chickensMode = false;
			if (!m_board.bossMode()) AsteroidsMode = true;
			chickens_in_place = 0;
			bonusCounter = 0;
		}
	}
	
	if (secondPlayer && m_player2->getLife() <= 0) {
		dontShowPlayer2 = false;
		secondPlayer = false;
	}
	if (secondPlayer && m_player->getLife() <= 0) dontShowPlayer1 = true;
	if (!secondPlayer && m_player->getLife() <= 0) gameOver(window);//handle game over
	if (secondPlayer && m_player->getLife() <= 0 && m_player2->getLife() < 0) gameOver(window);//handle game over


	if ((!AsteroidsMode && !chickensMode) && m_board.bossMode())  bossMode = true;

}

//function to calculate position
sf::Vector2f GameController::calculateAsteroidPoisition()
{
	float x = 4, y = 5; //random numbers so we wont get garbage values
	int a = rand() % 2;

	(a == 0) ? x = -50.0f : y = -50.0f;

	if (x == -50.f) y = (float)(rand() % (int)(WINDOW_HEIGHT / 2));

	else if (y == -50.0f) x = (float)(rand() % (int)(WINDOW_WIDTH * 0.6f));

	return { x, y };
}


