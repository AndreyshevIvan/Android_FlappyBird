#ifndef __GAME_BEHAVIOR_H__
#define __GAME_BEHAVIOR_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"

class GameBehavior
{
public:
	virtual void UpdateOptions(Bird* bird, GameMap* map, GameInterface* gameInterface) = 0;
	virtual void Behavior(Bird* bird, GameMap* map, GameInterface* gameInterface) = 0;

};

class StartGameBehavior : public GameBehavior
{
public:
	void UpdateOptions(Bird* bird, GameMap* map, GameInterface* gameInterface) override
	{
		bird->Reset();
		map->Reset();
		gameInterface->Reset();
	}

	void Behavior(Bird* bird, GameMap* map, GameInterface* gameInterface) override {}
};

class GameplayBehavior : public GameBehavior
{
public:
	void UpdateOptions(Bird* bird, GameMap* map, GameInterface* gameInterface) override
	{
		gameInterface->SetGameplayUI();
		map->StartMotion();
		bird->StartFlapping();
	}

	void Behavior(Bird* bird, GameMap* map, GameInterface* gameInterface) override
	{
		bird->Jump();
	}
};

class GameoverBehavior : public GameBehavior
{
public:
	void UpdateOptions(Bird* bird, GameMap* map, GameInterface* gameInterface) override
	{
		gameInterface->SetGameoverUI();
		bird->Death();
		map->StopMotion();
	}

	void Behavior(Bird* bird, GameMap* map, GameInterface* gameInterface) override {}

};

#endif // __GAME_BEHAVIOR_H__