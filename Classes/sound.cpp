#include "sound.h"

USING_NS_CC;

const float EFFECTS_VOLUME = 0.5f;

GameSound::GameSound()
{
	m_audio = CocosDenshion::SimpleAudioEngine::getInstance();

	m_audio->preloadEffect("sounds/point.wav");
	m_audio->preloadEffect("sounds/hit.wav");
	m_audio->preloadEffect("sounds/die.wav");
	m_audio->preloadEffect("souns/wing.wav");
	m_audio->preloadEffect("souns/swooshing.wav");
}

void GameSound::Wing()
{
	m_audio->playEffect("sounds/wing.wav", false);
}

void GameSound::Point()
{
	m_audio->playEffect("sounds/point.wav", false);
}

void GameSound::Hit()
{
	m_audio->playEffect("sounds/hit.wav", false);
}

void GameSound::Die()
{
	//m_audio->playEffect("sounds/die.wav", false);
}

void GameSound::Swooshing()
{
	m_audio->playEffect("sounds/swooshing.wav", false);
}