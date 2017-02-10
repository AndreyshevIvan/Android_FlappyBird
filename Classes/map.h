#ifndef __BACKGROUND_SCENE_H__
#define __BACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "constants.h"
#include <vector>

class GameMap
{
public:
	void Init(cocos2d::Layer* layer);

	void StopMotion();
	void StartMotion();
	void Update();

	cocos2d::PhysicsBody* GetGroundBody();
	std::vector<cocos2d::PhysicsBody*> GetTubesBodies();
	std::vector<cocos2d::PhysicsBody*> GetPointsBodies();

	void Reset();

private:
	cocos2d::Sprite* m_background;
	cocos2d::Sprite* m_city;
	cocos2d::Sprite* m_ground;
	std::vector<cocos2d::Sprite*> m_tubes;
	std::vector<cocos2d::PhysicsBody*> m_pointsBodies;

	void InitGround(cocos2d::Layer* layer);
	void InitTubes(cocos2d::Layer* layer, int tubesCount);
	void InitPointsBodies(cocos2d::Layer* layer);

	void UpdateGround();
	void UpdateTubes();
	void UpdatePointsBodies();

	float GetHeight();
	void ResetTubes(cocos2d::Sprite* topTube, cocos2d::Sprite* bottomTube);
};

#endif // __BACKGROUND_SCENE_H__