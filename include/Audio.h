#pragma once

#include "Global.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Audio
{
public:
	Audio();

//	void soundsHit();
	void playEggHatched() { m_sounds[0].play(); };
	void playBossHit() { m_sounds[9].play(); };
	void playBossDie() { m_sounds[1].play(); };
	void playChickenDie() { m_sounds[2].play(); };
	void playEggOnGround() { m_sounds[3].play(); };
	void playgameOver() { m_sounds[4].play(); };
	void stopMenuMusic() { m_sounds[5].stop(); };
	void playMenuSound() { m_sounds[5].play(); };
	void playPlayerHit() { m_sounds[6].play(); };
	void playShoot() { m_sounds[7].play(); };
	void playShootBonus() { m_sounds[8].play(); };
private:
	sf::SoundBuffer buffer[MAX_SOUNDS]; //change to const

	sf::Sound m_sounds[MAX_SOUNDS];
	sf::Music m_in_game;

};
