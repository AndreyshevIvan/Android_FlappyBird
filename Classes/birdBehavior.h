#ifndef __BIRD_BEHAVIOR_H__
#define __BIRD_BEHAVIOR_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "sound.h"

class BirdBehavior
{
public:
	void Init(Bird* bird)
	{
		m_bird = bird;
	}

	virtual void Update(float elapsedTime) = 0;

protected:
	Bird* m_bird;
};

class BirdIdle : BirdBehavior
{
	void Update(float elapsedTime) override { };
};

class BirdFlapping : BirdBehavior
{
	void Update(float elapsedTime) override { };
};

class BirdDead : BirdBehavior
{
	void Update(float elapsedTime) override { };
};

#endif // __BIRD_BEHAVIOR_H__