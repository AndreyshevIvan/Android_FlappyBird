#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::PhysicsWorld* sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

	Bird m_bird;
	GameMap m_background;
	std::ofstream m_log;

	bool IsBirdCollideAny(cocos2d::PhysicsContact& contact);
	bool IsScreenTouched(cocos2d::Touch* touch, cocos2d::Event* event);

	void GameUpdate(float dt);

	bool IsCollideWithGround(cocos2d::PhysicsContact& contact);

};

#endif // __HELLOWORLD_SCENE_H__
