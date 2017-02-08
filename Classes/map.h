#ifndef __BACKGROUND_SCENE_H__
#define __BACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "constants.h"
#include <vector>

class GameMap
{
public:
	void Init(cocos2d::Layer* layer);
	void Update(float elapsedTime);

	cocos2d::Rect GetGroundBox();

private:
	cocos2d::Sprite* m_background;
	cocos2d::Sprite* m_city;
	cocos2d::Sprite* m_ground;
	std::vector<cocos2d::Sprite*> m_tubes;

	void InitGround(cocos2d::Layer* layer);
	void InitTubes(cocos2d::Layer* layer);

	void UpdateGround(float elapsedTime);
	void UpdateTubes(float elapsedTime);

	std::ofstream m_log;
};

#endif // __BACKGROUND_SCENE_H__