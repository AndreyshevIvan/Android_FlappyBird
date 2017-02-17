#ifndef __GAME_BEHAVIOR_H__
#define __GAME_BEHAVIOR_H__

#include "cocos2d.h"
#include "constants.h"

enum struct BehaviorType
{
	START,
	GAMEPLAY,
	GAMEOVER,
};

class GameBehavior
{
public:
	void PlayBehavior(BehaviorType const& newBehavior);
	void SetNewBehavior(BehaviorType const& newBehavior);

private:
	virtual void ChangeBehavior(BehaviorType const& newBehavior) = 0;

	virtual void SetStartBehaviorOptions() = 0;
	virtual void SetGameplayBehaviorOptions() = 0;
	virtual void SetGameoverBehaviorOptions() = 0;

	virtual void StartBehavior() = 0;
	virtual void GameplayBehavior() = 0;
	virtual void GameoverBehavior() = 0;

};

#endif // __GAME_BEHAVIOR_H__