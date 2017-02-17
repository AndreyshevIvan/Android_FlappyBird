#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "cocos2d.h"
#include "constants.h"
#include "sound.h"
#include <sstream>

class GameInterface : public cocos2d::Node
{
public:
	bool init() override;

	void AddPoint();
	unsigned GetPointsCount();

	void Update(cocos2d::Vec2 const& birdPosition);

	void SetStartUI();
	void SetGameplayUI();
	void SetGameoverUI();

	bool IsGameoverTableAppeared();

	void Reset();

private:
	unsigned m_pointsCount;
	float m_guideTimer;
	GameSound m_audio;

	cocos2d::Label* m_points;
	cocos2d::Label* m_score;
	cocos2d::Label* m_bestScore;
	cocos2d::Sprite* m_scoreTab;
	cocos2d::Sprite* m_medal;
	cocos2d::Sprite* m_newHighScoreTab;
	cocos2d::Sprite* m_gameOver;
	cocos2d::Sprite* m_gameName;
	cocos2d::Sprite* m_guide;

	void onEnter() override;
	void onExit() override;

	void UpdateIdleInterface(cocos2d::Vec2 const& birdPosition);
	std::string GetHighScoreStr();
	void SetMedal();
	void SetNewHightScore();
	bool IsScoreNew();

	void ResetUI();

};

std::string PointsToStr(unsigned points);

#endif // __INTERFACE_H__