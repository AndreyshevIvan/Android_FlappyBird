#ifndef __BACKGROUND_SCENE_H__
#define __BACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "constants.h"
#include <vector>

const int GROUND_COLLISION_BITMASK = 0x00001;
const int SKY_Z_INDEX = 0;
const int CITY_Z_INDEX = 1;
const int GROUND_Z_INDEX = 4;
const float GROUND_HEIGHT = 105;
const size_t GROUNDS_COUNT = 3;
const float GROUND_OFFSET = 446;

const int TUBE_Z_INDEX = 3;
const int TUBE_COLLISION_BITMASK = 0x00001;
const size_t TUBES_COUNT = 3;
const float TUBES_BETWEEN_OFFSET = 500;
const float TUBE_RESET_OFFSET = TUBES_BETWEEN_OFFSET * TUBES_COUNT;
const float TUBES_START_OFFSET = 256;
const float LOWER_SCREEN_TUBE_THRESHOLD = 0.40f;
const float UPPER_SCREEN_TUBE_THRESHOLD = 0.90f;
const float TUBE_GAP = 315;

class GameMap
{
public:
	void Init(cocos2d::Layer* layer);
	void Update(float elapsedTime);

	cocos2d::PhysicsBody* GetGroundBody();
	std::vector<cocos2d::PhysicsBody*> GetTubesBodies();

	void Reset();

private:
	cocos2d::Sprite* m_background;
	cocos2d::Sprite* m_city;
	cocos2d::Sprite* m_ground;
	std::vector<cocos2d::Sprite*> m_tubes;

	void InitGround(cocos2d::Layer* layer);
	void InitTubes(cocos2d::Layer* layer);

	void UpdateGround(float elapsedTime);
	void UpdateTubes(float elapsedTime);

	float GetHeight();
	void ResetTubes(cocos2d::Sprite* topTube, cocos2d::Sprite* bottomTube);

	std::ofstream m_log;
};

#endif // __BACKGROUND_SCENE_H__