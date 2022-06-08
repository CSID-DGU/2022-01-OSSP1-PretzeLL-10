#include "MonsterManager.h"
#include "GameManager.h"

std::function<void(MonsterManager&, int)> create3MT_PT[] = { 
	&MonsterManager::create3MT_0,
	&MonsterManager::create3MT_1
};

std::function<void(MonsterManager&, int)> create4MT_PT[] = {
	&MonsterManager::create4MT_0,
	&MonsterManager::create4MT_1
};

std::function<void(MonsterManager&, int)> create5MT_PT[] = {
	&MonsterManager::create5MT_0,
	&MonsterManager::create5MT_1
};

std::function<void(MonsterManager&, int)> create6MT_PT[] = {
	&MonsterManager::create6MT_0,
	&MonsterManager::create6MT_1
};

void MonsterManager::createMonster(int stage, bool boss)
{
	if (boss)
	{
		createBossMonster(stage);
		return;
	}
	int numberMT = 0;
	int typeOfPattern = 0, MAXTYPE;
	engine = std::mt19937_64(rand_device());
    std::uniform_int_distribution<int> numberRand(3, 6);
	numberMT = numberRand(engine);
	switch (numberMT)
	{
	case 3:
		MAXTYPE = 2;
		break;
	case 4:
		MAXTYPE = 2;
		break;
	case 5:
		MAXTYPE = 2;
		break;
	case 6:
		MAXTYPE = 2;
		break;
	default:
		exit(1);
		break;
	}
    std::uniform_int_distribution<int> typeRand(0, MAXTYPE - 1);
	typeOfPattern = typeRand(engine);
	switch (numberMT)
	{
	case 3:
		create3MT_PT[typeOfPattern](*this, stage);
		break;
	case 4:
		create4MT_PT[typeOfPattern](*this, stage);
		break;
	case 5:
		create5MT_PT[typeOfPattern](*this, stage);
		break;
	case 6:
		create6MT_PT[typeOfPattern](*this, stage);
		break;
	default:
		exit(1);
		break;
	}
}

void MonsterManager::create3MT_0(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3;
	
	monster1 = level2monster(stage);
	monster1->setAbsolutePosition(626, 791);
	monster1->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level4monster(stage);
	monster2->setAbsolutePosition(241, 461);
	monster2->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level3monster(stage);
	monster3->setAbsolutePosition(338, 708);
	monster3->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster3);
}

void MonsterManager::create3MT_1(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3;

	monster1 = level1monster(stage);
	monster1->setAbsolutePosition(310, 423);
	monster1->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level4monster(stage);
	monster2->setAbsolutePosition(500, 745);
	monster2->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level1monster(stage);
	monster3->setAbsolutePosition(407, 708);
	monster3->setLocalZOrder(2);
	GameManager::getInstance()->addMonsters2(monster3);
}

void MonsterManager::create4MT_0(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4;

	monster1 = level3monster(stage);
	monster1->setAbsolutePosition(206, 429);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level4monster(stage);
	monster2->setAbsolutePosition(286, 518);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level1monster(stage);
	monster3->setAbsolutePosition(522, 754);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level1monster(stage);
	monster4->setAbsolutePosition(377, 624);
	GameManager::getInstance()->addMonsters2(monster4);
}

void MonsterManager::create4MT_1(int stage)
{
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4;

	monster1 = level3monster(stage);
	monster1->setAbsolutePosition(242, 510);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level2monster(stage);
	monster2->setAbsolutePosition(403, 664);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level3monster(stage);
	monster3->setAbsolutePosition(350, 733);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level1monster(stage);
	monster4->setAbsolutePosition(205, 403);
	GameManager::getInstance()->addMonsters2(monster4);
}

void MonsterManager::create5MT_0(int stage) {
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4; BaseMonster* monster5;

	monster1 = level3monster(stage);
	monster1->setAbsolutePosition(730, 639);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level2monster(stage);
	monster2->setAbsolutePosition(370, 706);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level3monster(stage);
	monster3->setAbsolutePosition(602, 542);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level1monster(stage);
	monster4->setAbsolutePosition(301, 404);
	GameManager::getInstance()->addMonsters2(monster4);

	monster5 = level1monster(stage);
	monster5->setAbsolutePosition(599, 798);
	GameManager::getInstance()->addMonsters2(monster5);
}

void MonsterManager::create5MT_1(int stage) {
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4; BaseMonster* monster5;

	monster1 = level2monster(stage);
	monster1->setAbsolutePosition(309, 659);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level2monster(stage);
	monster2->setAbsolutePosition(769, 462);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level2monster(stage);
	monster3->setAbsolutePosition(232, 688);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level4monster(stage);
	monster4->setAbsolutePosition(546, 471);
	GameManager::getInstance()->addMonsters2(monster4);

	monster5 = level3monster(stage);
	monster5->setAbsolutePosition(391, 733);
	GameManager::getInstance()->addMonsters2(monster5);
}

void MonsterManager::create6MT_0(int stage) {
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4; BaseMonster* monster5; BaseMonster* monster6;

	monster1 = level4monster(stage);
	monster1->setAbsolutePosition(230, 441);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level1monster(stage);
	monster2->setAbsolutePosition(375, 612);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level2monster(stage);
	monster3->setAbsolutePosition(431, 779);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level2monster(stage);
	monster4->setAbsolutePosition(752, 621);
	GameManager::getInstance()->addMonsters2(monster4);

	monster5 = level4monster(stage);
	monster5->setAbsolutePosition(675, 717);
	GameManager::getInstance()->addMonsters2(monster5);

	monster6 = level2monster(stage);
	monster6->setAbsolutePosition(566, 767);
	GameManager::getInstance()->addMonsters2(monster6);
}

void MonsterManager::create6MT_1(int stage) {
	BaseMonster* monster1; BaseMonster* monster2; BaseMonster* monster3; BaseMonster* monster4; BaseMonster* monster5; BaseMonster* monster6;

	monster1 = level4monster(stage);
	monster1->setAbsolutePosition(791, 679);
	GameManager::getInstance()->addMonsters2(monster1);

	monster2 = level1monster(stage);
	monster2->setAbsolutePosition(604, 728);
	GameManager::getInstance()->addMonsters2(monster2);

	monster3 = level4monster(stage);
	monster3->setAbsolutePosition(317, 406);
	GameManager::getInstance()->addMonsters2(monster3);

	monster4 = level2monster(stage);
	monster4->setAbsolutePosition(595, 574);
	GameManager::getInstance()->addMonsters2(monster4);

	monster5 = level1monster(stage);
	monster5->setAbsolutePosition(353, 737);
	GameManager::getInstance()->addMonsters2(monster5);

	monster6 = level2monster(stage);
	monster6->setAbsolutePosition(635, 500);
	GameManager::getInstance()->addMonsters2(monster6);
}

void MonsterManager::createBossMonster(int stage)
{
	BaseMonster* boss = bossmonster(stage);
	boss->setAbsolutePosition(500, 500);
	boss->setScale(2.0f);

	GameManager::getInstance()->addMonsters2(boss);
}
