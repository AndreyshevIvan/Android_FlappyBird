#ifndef __BIRD_SCENE_H__
#define __BIRD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include <cmath>

enum struct BirdStatus
{
	IDLE,
	FLAPPING,
};

class Bird : public cocos2d::Sprite
{
public:
	Bird();

	int state;

	static Bird* CreateWithFileName(char* fileName);

	void Update(float elapsedTime);
	void UpdateGravity(float elapsedTime);
	void Idle(float elapsedTime);
	void RotateBird(float elapsedTime, cocos2d::Vec2 const& movement);
	void Jump();

	void Reset();
	void SetStartSpeed();
	void SetParams(float tos);
	cocos2d::Rect TubeCollisionBox();

private:
	BirdStatus m_status;
	float m_speed;
	float m_topOfScreen;
	float m_idleAnimTime;

};

#endif // __BIRD_SCENE_H__