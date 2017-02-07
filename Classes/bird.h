#ifndef __BIRD_SCENE_H__
#define __BIRD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

class Bird : public cocos2d::Sprite
{
public:
	Bird() {};

	int state;
	
	static Bird* CreateWithFileName(char* fileName);
	void Update(float dt);
	void Reset();
	void SetStartSpeed();
	void SetParams(float tos);
	cocos2d::Rect TubeCollisionBox();

private:
	float m_speedY;
	float m_topOfScreen;

};

#endif // __BIRD_SCENE_H__