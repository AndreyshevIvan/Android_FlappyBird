#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"
#include "sound.h"

class GameEntities
{
public:
	Bird* m_bird;
	GameMap* m_map;
	GameInterface* m_interface;

};

class GameBehaviorStrat
{
public:
	virtual void UpdateOptions() = 0;
	virtual void Behavior() = 0;

};

class StartGameBehavior : public GameBehaviorStrat, public GameEntities
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

	void Behavior() override
	{

	}
};

class GameplayBehavior : public GameBehaviorStrat, public GameEntities
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

class GameoverBehavior : public GameBehaviorStrat, public GameEntities
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

	void Behavior() override
	{

	}
};

class GameScene : public cocos2d::Layer, public GameEntities
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameBehaviorStrat* m_currBehavior;

	GameBehaviorStrat* m_startBehavior;
	GameBehaviorStrat* m_gameplayBehavior;
	GameBehaviorStrat* m_gameoverBehavior;

	void AddListeners();

	bool IsBirdCollideAny(cocos2d::PhysicsContact& contact);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
	void update(float elapsedTime);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;
	
	void SetBehavior(GameBehaviorStrat* newBehavior);

};

#endif // __GAME_SCENE_H__