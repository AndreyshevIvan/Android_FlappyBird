#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"
#include "gameBehavior.h"
#include "sound.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	Bird* m_bird;
	GameMap* m_map;
	GameInterface* m_interface;

	GameBehavior* m_currBehavior;
	GameBehavior* m_startBehavior;
	GameBehavior* m_gameplayBehavior;
	GameBehavior* m_gameoverBehavior;

	void AddListeners();

	bool IsBirdContactWithAny(cocos2d::PhysicsContact& contact);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	void update(float elapsedTime);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;
	
	void SetBehavior(GameBehavior* newBehavior);

};

#endif // __GAME_SCENE_H__