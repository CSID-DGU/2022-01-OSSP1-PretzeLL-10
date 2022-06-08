#include "MonsterManager.h"
#include "GameManager.h"

void MonsterManager::createMonster(int stage, bool boss)
{
	if (boss)
	{
		createBossMonster(stage);
		return;
	}
	//int numberMT = 0;
	//int typeOfPattern = 0, MAXTYPE;
	//engine = std::mt19937_64(rand_device());
	//const std::uniform_int_distribution<int> numberRand(2, 6);
	//numberMT = numberRand(engine);
	//switch (numberMT)
	//{
	//case 2:
	//	MAXTYPE = 2;
	//	break;
	//case 3:
	//	MAXTYPE = 2;
	//	break;
	//case 4:
	//	MAXTYPE = 2;
	//	break;
	//case 5:
	//	MAXTYPE = 2;
	//	break;
	//case 6:
	//	MAXTYPE = 2;
	//	break;
	//default:
	//	exit(1);
	//	break;
	//}
	//const std::uniform_int_distribution<int> typeRand(0, MAXTYPE);
	//typeOfPattern = typeRand(engine);
	create4MT_0(stage);
}

void MonsterManager::create3MT_0(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3;
	
	monster1 = level1monster(stage);
	monster1->setAbsolutePosition(200, 600);
	monster1->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster1);
}

void MonsterManager::create4MT_0(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4;

	monster1 = level1monster(stage);
	monster1->setAbsolutePosition(200, 600);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level2monster(stage);
	monster2->setAbsolutePosition(600, 600);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level3monster(stage);
	monster3->setAbsolutePosition(200, 400);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level4monster(stage);
	monster4->setAbsolutePosition(600, 400);
	GameManager::getInstance()->addMonsters2(monster4);
}

void MonsterManager::createBossMonster(int stage)
{
	BaseMonster* boss = bossmonster(stage);
	boss->setAbsolutePosition(500, 500);
	boss->setScale(2.0f);

	GameManager::getInstance()->addMonsters2(boss);
}