#ifndef __BACKGROUND_SCENE_H__
#define __BACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "constants.h"
#include <vector>

class Background
{
public:
	void Init(cocos2d::Layer* layer);
	void Update(float elapsedTime);

private:
	std::vector<cocos2d::Sprite*> m_grounds;

	void InitGrounds(cocos2d::Layer* layer);

	void UpdateGround(float elapsedTime);
};

#endif // __BACKGROUND_SCENE_H__