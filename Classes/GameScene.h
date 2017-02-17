#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"
#include "sound.h"
#include "gameBehavior.h"

class GameScene : public cocos2d::Layer, protected GameBehavior
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	BehaviorType m_behavior;
	Bird* m_bird;
	GameMap* m_map;
	GameInterface* m_interface;

	void AddListeners();

	bool IsBirdCollideAny(cocos2d::PhysicsContact& contact);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	void update(float elapsedTime); 
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;

	void ChangeBehavior(BehaviorType const& newBehavior) override;

	void SetStartBehaviorOptions() override;
	void SetGameplayBehaviorOptions() override;
	void SetGameoverBehaviorOptions() override;

	void StartBehavior() override;
	void GameplayBehavior() override;
	void GameoverBehavior() override;

};

#endif // __HELLOWORLD_SCENE_H__
