#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"

class GameOverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void exitPause(cocos2d::Ref* pSender);
	CREATE_FUNC(GameOverScene);

private:
	cocos2d::Director *m_director;
	cocos2d::Size m_visibleSize;
};

#endif // __PAUSE_SCENE_H__
