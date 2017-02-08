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

class Bird
{
public:
	void Init(cocos2d::Layer* layer);

	void Update(float elapsedTime);
	void Idle(float elapsedTime);
	void Jump();

	cocos2d::PhysicsBody* GetBody();
	void Reset();

private:
	cocos2d::Sprite* m_body;
	BirdStatus m_status;
	float m_topOfScreen;
	float m_idleAnimTime;
	float m_flappingAnimTime;

	void RotateBird(float elapsedTime);
	void FlappingAnimate(float elapsedTime);

};

#endif // __BIRD_SCENE_H__