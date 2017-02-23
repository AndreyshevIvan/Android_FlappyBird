#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "gameBehavior.h"
#include "gameEntities.h"
#include "sound.h"

class GameScene : public cocos2d::Layer, public GameEntities
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameBehavior* m_currBehavior;

	GameBehavior* m_startBehavior;
	GameBehavior* m_gameplayBehavior;
	GameBehavior* m_gameoverBehavior;

	void AddListeners();

	bool IsBirdCollideAny(cocos2d::PhysicsContact& contact);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	void update(float elapsedTime);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;
	
	void SetBehavior(GameBehavior* newBehavior);

};

#endif // __GAME_SCENE_H__