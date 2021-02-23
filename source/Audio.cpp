#include "Audio.h"

Audio::Audio()
{
	if(
	!buffer[0].loadFromFile("EggLay.wav")||
	!buffer[1].loadFromFile("BossDie.wav")||
	!buffer[2].loadFromFile("chickendie.wav")||
	!buffer[3].loadFromFile("eggOnGround.wav")||
	!buffer[4].loadFromFile("gameover.wav")||
	!buffer[5].loadFromFile("menuSound.wav")||
	//!buffer[6].loadFromFile("playerhit.wav")||
	!buffer[7].loadFromFile("shoot.ogx")||
	!buffer[8].loadFromFile("Shootbonus.ogx")||
	!buffer[9].loadFromFile("BossHit.wav")
	)
	{
		throw std::runtime_error("Can't load file");
	}

	m_sounds[0].setBuffer(buffer[0]);
	m_sounds[1].setBuffer(buffer[1]);
	m_sounds[2].setBuffer(buffer[2]);
	m_sounds[3].setBuffer(buffer[3]);
	m_sounds[4].setBuffer(buffer[4]);
	m_sounds[5].setBuffer(buffer[5]);
	m_sounds[6].setBuffer(buffer[6]);
	m_sounds[7].setBuffer(buffer[7]);
	m_sounds[8].setBuffer(buffer[8]);
	m_sounds[9].setBuffer(buffer[9]);
}