#ifndef __BIRD_SCENE_H__
#define __BIRD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"
#include <cmath>

const int BIRD_COLLISION_BITMASK = 0x00001;
const int TEST_COLLISION_BITMASK = 0x00001;
const int BIRD_Z_INDEX = 10;
const float BIRD_MAX_HEIGHT = 1280;
const int BIRD_FRAMES = 4;
const float BIRD_POS_X_FACTOR = 0.2f;
const float BIRD_JUMP_VELOCITY = 1000;
const float BIRD_ANIMATE_FPS = 10;

const float UP_ROT_ANGALE = -50;
const float DOWN_ROT_ANGLE = 90;
const float DOWN_ROT_SPEED = 280;

enum struct BirdStatus
{
	IDLE,
	FLAPPING,
	DEAD,
};

class Bird
{
public:
	void Init(cocos2d::Layer* layer);

	void Update(float elapsedTime);
	void Idle(float elapsedTime);
	void Jump();

	cocos2d::Vec2 GetPos();
	cocos2d::PhysicsBody* GetBody();
	void Reset();
	void Death();

private:
	cocos2d::Sprite* m_body;
	cocos2d::Texture2D* m_aliveTexture;
	cocos2d::Texture2D* m_deadTexture;
	BirdStatus m_status;
	float m_topOfScreen;
	float m_idleAnimTime;
	float m_flappingAnimTime;

	void RotateBird(float elapsedTime);
	void FlappingAnimate(float elapsedTime);

	void ResetTexture();

	std::ofstream m_log;

};

#endif // __BIRD_SCENE_H__