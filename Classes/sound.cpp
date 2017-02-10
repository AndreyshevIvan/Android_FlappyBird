#include "sound.h"

USING_NS_CC;


void GameSound::Init()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	audio->preloadEffect("sounds/point.wav");
	//m_audio->preloadEffect("sounds/hit.ogg");
	//m_audio->preloadEffect("sounds/sfx_die.ogg");
	//m_audio->preloadEffect("sounds/sfx_swooshing.ogg");

	//m_audio->setEffectsVolume(2);

	//m_audio->preloadBackgroundMusic();
	m_log.open("output.txt");
}

void GameSound::Point()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	m_log << "playEffect";
	audio->playEffect("sounds/point.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameSound::Hit()
{

}

void GameSound::Die()
{

}

void GameSound::Swooshing()
{

}