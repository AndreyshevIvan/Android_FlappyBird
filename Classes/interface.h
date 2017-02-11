#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "cocos2d.h"
#include "constants.h"
#include "sound.h"
#include <sstream>

class GameInterface
{
public:
	void Init(cocos2d::Layer* layer);

	void AddPoint();
	unsigned GetPointsCount();

	void Update(cocos2d::Vec2 const& birdPosition);

	void SetStartUI();
	void SetGameplayUI();
	void SetGameoverUI();

	void Reset();

private:
	unsigned m_pointsCount;
	float m_guideTimer;
	GameSound m_audio;

	cocos2d::Label* m_points;
	cocos2d::Label* m_score;
	cocos2d::Sprite* m_scoreTab;
	cocos2d::Sprite* m_gameOver;
	cocos2d::Sprite* m_gameName;
	cocos2d::Sprite* m_guide;

	void UpdateIdleInterface(cocos2d::Vec2 const& birdPosition);
	std::string GetPointsStr();

	void ResetUI();

};

#endif // __INTERFACE_H__