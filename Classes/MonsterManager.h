#ifndef __MONSTER_MANAGER_H__
#define __MONSTER_MANAGER_H__

#include <cocos2d.h>
#include "MonsterMakingFunction.h"

//BaseMonster* level2Monster(int stage)
//{
//	switch (stage)
//	{
//	case 1:
//	case 2:
//	case 3:
//	case 4:
//	default:
//		break;
//	}
//}

class MonsterManager
{
private:
	std::random_device rand_device;
	std::mt19937_64 engine;
public:
	// random pick of monster creation
	void createMonster(int stage, bool boss);

	// boss monster spawn
	void createBossMonster(int stage);
	// monster spwan location pattern
	void create3MT_0(int stage);
	void create3MT_1(int stage);
	void create4MT_0(int stage);
	void create4MT_1(int stage);

	// create Boss Monster
};


#endif /* __MONSTER_MANAGER_H__ */