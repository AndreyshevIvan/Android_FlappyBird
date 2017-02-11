#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "constants.h"

class GameSound
{
public:
	GameSound();

	void Wing();
	void Point();
	void Hit();
	void Die();
	void Swooshing();

private:

	CocosDenshion::SimpleAudioEngine* m_audio;
};

#endif // __SOUND_H__