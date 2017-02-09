#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "GameOverScene.h"

#include "bird.h"
#include "map.h"

enum struct GameBehavior
{
	START,
	GAMEPLAY,
	GAMEOVER,
};

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	cocos2d::PhysicsWorld* sceneWorld;
	GameBehavior m_behavior;
	Bird m_bird;
	GameMap m_background;
	std::vector<cocos2d::PhysicsBody*> m_tubesBodies;
	std::ofstream m_log;

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world);
	void SetBehavoir(GameBehavior newBehavior);

	bool IsScreenTouched(cocos2d::Touch* touch, cocos2d::Event* event);

	void GameUpdate(float dt);

	bool IsBirdFell(cocos2d::PhysicsContact& contact);
	bool IsCollideWithGround(cocos2d::PhysicsContact& contact);
	bool IsCollideWithTube(cocos2d::PhysicsContact& contact);

};

#endif // __HELLOWORLD_SCENE_H__
