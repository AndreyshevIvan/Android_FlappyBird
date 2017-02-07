#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "background.h"
#include <fstream>

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	Bird* m_bird;
	Background* m_background;

	std::ofstream output;

	bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void GameUpdate(float dt);

};

#endif // __HELLOWORLD_SCENE_H__
