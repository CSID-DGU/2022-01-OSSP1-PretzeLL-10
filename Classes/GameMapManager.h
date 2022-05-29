#ifndef __GAME_MAP_MANAGER_H__
#define __GAME_MAP_MANAGER_H__

#include <cocos2d.h>
#include "GameMap.h"

#define MAKEMAP(x, y, FILENAME) 

class GameMapManager
{
private:
	std::random_device rand_device;
	std::mt19937_64 engine;
	std::uniform_int_distribution<int> rand;
public:
	void makeGameMap(GameMap***& maparr);
private:
	void doMakeGameMap0(GameMap***& maparr);
	void doMakeGameMap1(GameMap***& maparr);
	void doMakeGameMap2(GameMap***& maparr);
	void doMakeGameMap3(GameMap***& maparr);
	void doMakeGameMap4(GameMap***& maparr);
	void doMakeGameMap5(GameMap***& maparr);
};

#endif
