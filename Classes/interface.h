#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "cocos2d.h"
#include "constants.h"

const int INTERFACE_Z_INDEX = 100;
const float GAME_NAME_OFFSET = 360;
const float GAMEOVER_OFFSET = 360;
const cocos2d::Vec2 SCORE_OFFSET = cocos2d::Vec2(238, 32);
const int FONT_OUTLINE_THICKNESS = 5;
const int SCORE_FONT_SIZE = 60;
const int POINTS_FONT_SIZE = 70;
const cocos2d::Color4B FONT_OUTLINE_COLOR = cocos2d::Color4B(92, 53, 70, 255);
const float POINTS_POS_FACTOR = 0.9f;

class GameInterface
{
public:
	void Init(cocos2d::Layer* layer);

	void AddPoint();
	unsigned GetPointsCount();

	void Update(float elapsedTime, cocos2d::Vec2 const& birdPosition);
	void UpdateIdleInterface(float elapsedTime, cocos2d::Vec2 const& birdPosition);

	void SetStartUI();
	void SetGameplayUI();
	void SetGameoverUI();

	void ResetUI();
	void Reset();

private:
	unsigned m_pointsCount;
	float m_guideTimer;

	cocos2d::Label* m_points;
	cocos2d::Label* m_score;
	cocos2d::Sprite* m_scoreTab;
	cocos2d::Sprite* m_gameOver;
	cocos2d::Sprite* m_gameName;
	cocos2d::Sprite* m_guide;

};

#endif // __INTERFACE_H__