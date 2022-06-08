#include "MonsterMakingFunction.h"

BaseMonster* level1monster(int stage)
{
	BaseMonster* tmp;
	switch (stage)
	{
	case 1:
		tmp = TinyZombie::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 2:
		tmp = Goblin::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 3:
		tmp = Imp::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	default:
		return Necromancer::create();
		break;
	}
}

BaseMonster* level2monster(int stage)
{
	BaseMonster* tmp;
	switch (stage)
	{
	case 1:
		tmp = Skeleton::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 2:
		tmp = MaskedOrc::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 3:
		tmp = Necromancer::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	default:
		return Necromancer::create();
		break;
	}
}

BaseMonster* level3monster(int stage)
{
	BaseMonster* tmp;
	switch (stage)
	{
	case 1:
		tmp = Muddy::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 2:
		tmp = OrcWarrior::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 3:
		tmp = Wogol::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	default:
		return Necromancer::create();
		break;
	}
}

BaseMonster* level4monster(int stage)
{
	BaseMonster* tmp;
	switch (stage)
	{
	case 1:
		tmp = Zombie::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 2:
		tmp = OrcShaman::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 3:
		tmp = Chort::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	default:
		return Necromancer::create();
		break;
	}
}

BaseMonster* bossmonster(int stage)
{
	BaseMonster* tmp;
	switch (stage)
	{
	case 1:
		tmp = BigZombie::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 2:
		tmp = Ogre::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	case 3:
		tmp = BigDemon::create();
		tmp->setLocalZOrder(2);
		return tmp;
		break;
	default:
		return Necromancer::create();
		break;
	}
}