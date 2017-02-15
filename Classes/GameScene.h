#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"
#include "sound.h"

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
	CREATE_FUNC(GameScene);

private:
	GameBehavior m_behavior;
	Bird* m_bird;
	GameMap* m_map;
	GameInterface m_interface;

	bool IsBirdCollideAny(cocos2d::PhysicsContact& contact);

	void SetBehavoir(GameBehavior newBehavior);

	bool HandleTouch(cocos2d::Touch* touch, cocos2d::Event* event);
	void Update(float elapsedTime); 
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;

};

#endif // __HELLOWORLD_SCENE_H__
