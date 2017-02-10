#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "constants.h"

class GameSound
{
public:
	void Init();

	void Point();
	void Hit();
	void Die();
	void Swooshing();

private:

	std::ofstream m_log;
};

#endif // __SOUND_H__