#ifndef __GAME_ENTITIES_H__
#define __GAME_ENTITIES_H__

#include "cocos2d.h"
#include "constants.h"

#include "bird.h"
#include "map.h"
#include "interface.h"

class GameEntities
{
public:
	Bird* m_bird;
	GameMap* m_map;
	GameInterface* m_interface;

};

#endif // __GAME_ENTITIES_H__