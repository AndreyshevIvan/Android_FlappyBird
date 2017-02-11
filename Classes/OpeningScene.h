#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "GameScene.h"

class OpeningScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OpeningScene);

private:
	void GoToGameScene(float elapsedTime);

};

#endif // __PAUSE_SCENE_H__
