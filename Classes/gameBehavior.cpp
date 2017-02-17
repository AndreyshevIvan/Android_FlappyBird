#include "gameBehavior.h"

USING_NS_CC;

void GameBehavior::SetNewBehavior(BehaviorType const& newBehavior)
{
	ChangeBehavior(newBehavior);

	if (newBehavior == BehaviorType::START)      SetStartBehaviorOptions();
	if (newBehavior == BehaviorType::GAMEPLAY)   SetGameplayBehaviorOptions();
	if (newBehavior == BehaviorType::GAMEOVER)   SetGameoverBehaviorOptions();
}

void GameBehavior::PlayBehavior(BehaviorType const& newBehavior)
{
	if (newBehavior == BehaviorType::START)      StartBehavior();
	if (newBehavior == BehaviorType::GAMEPLAY)   GameplayBehavior();
	if (newBehavior == BehaviorType::GAMEOVER)   GameoverBehavior();
}