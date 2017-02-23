#ifndef __GAME_BEHAVIOR_H__
#define __GAME_BEHAVIOR_H__

#include "cocos2d.h"
#include "constants.h"

#include "gameEntities.h"

class GameBehavior
{
public:
	virtual void UpdateOptions() = 0;
	virtual void Behavior() = 0;

};

class StartGameBehavior : public GameBehavior, public GameEntities
{
public:
	StartGameBehavior(Bird* bird, GameMap* map, GameInterface* gameInterface)
	{
		m_bird = bird;
		m_map = map;
		m_interface = gameInterface;
	}

	void UpdateOptions() override
	{
		m_bird->Reset();
		m_map->Reset();
		m_interface->Reset();
	}

	void Behavior() override {}
};

class GameplayBehavior : public GameBehavior, public GameEntities
{
public:
	GameplayBehavior(Bird* bird, GameMap* map, GameInterface* gameInterface)
	{
		m_bird = bird;
		m_map = map;
		m_interface = gameInterface;
	}

	void UpdateOptions() override
	{
		m_interface->SetGameplayUI();
		m_map->StartMotion();
		m_bird->StartFlapping();
	}

	void Behavior() override
	{
		m_bird->Jump();
	}
};

class GameoverBehavior : public GameBehavior, public GameEntities
{
public:
	GameoverBehavior(Bird* bird, GameMap* map, GameInterface* gameInterface)
	{
		m_bird = bird;
		m_map = map;
		m_interface = gameInterface;
	}

	void UpdateOptions() override
	{
		m_interface->SetGameoverUI();
		m_bird->Death();
		m_map->StopMotion();
	}

	void Behavior() override {}
};

#endif // __GAME_BEHAVIOR_H__