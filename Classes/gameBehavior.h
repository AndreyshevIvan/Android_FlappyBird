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
	void Init(Bird* bird, GameMap* map, GameInterface* gameInterface);

	virtual void Start() = 0;
	virtual void Update(float elapsedTime) = 0;
	virtual void OnTouchEvent() {};
	virtual bool IsOnTouchChange() { return false; };
	
	virtual void CollideWithPointEvent() {};

protected: 
	Bird* m_bird;
	GameMap* m_map;
	GameInterface* m_interface;
};

class StartGameBehavior : public GameBehavior
{
public:
	void Start() override;
	void Update(float elapsedTime) override;
	bool IsOnTouchChange() override;

};

class GameplayBehavior : public GameBehavior
{
public:
	void Start() override;
	void Update(float elapsedTime) override {};
	void OnTouchEvent() override;

	void CollideWithPointEvent() override;

};

class GameoverBehavior : public GameBehavior
{
public:
	void Start() override;
	void Update(float elapsedTime) override {};
	bool IsOnTouchChange() override;

};

#endif // __GAME_BEHAVIOR_H__