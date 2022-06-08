#ifndef __MAKE_MONSTER_FUNCTION_H__
#define __MAKE_MONSTER_FUNCTION_H__

#include "Monster.h"

BaseMonster* level1monster(int stage);
BaseMonster* level2monster(int stage);
BaseMonster* level3monster(int stage);
BaseMonster* level4monster(int stage);

BaseMonster* bossmonster(int stage);

#endif // !__MAKE_MONSTER_FUNCTION_H__