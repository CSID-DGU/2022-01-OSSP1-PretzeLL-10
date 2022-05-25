#include "GameMapManager.h"

#define MAKEMAP(x, y, string) maparr[x][y] = new GameMap(string)
#define MAPNUMBER 3

void GameMapManager::makeGameMap(GameMap***& maparr)
{
	engine = std::mt19937_64(rand_device());
	rand = std::uniform_int_distribution<int>(0, MAPNUMBER - 1);

	int x = rand(engine);
	switch (x)
	{
	case 0:
		doMakeGameMap0(maparr);
		break;
	case 1:
		doMakeGameMap1(maparr);
		break;
	case 2:
		doMakeGameMap2(maparr);
		break;
	default:
		break;
	}
}

void GameMapManager::doMakeGameMap0(GameMap***& maparr)
{
	MAKEMAP(0, 0, "tmx/Basic_type1_Right.tmx");		//오른쪽
	MAKEMAP(1, 0, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(2, 0, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(3, 0, "tmx/Basic_type2_LT.tmx");		//왼쪽 위쪽
	MAKEMAP(2, 1, "tmx/Basic_type2_TR.tmx");		//오른쪽 위쪽
	MAKEMAP(3, 1, "tmx/Basic_type2_LB.tmx");		//왼쪽 아래쪽
	MAKEMAP(4, 1, "tmx/Basic_type1_Top.tmx");		//위쪽
	MAKEMAP(1, 2, "tmx/Basic_type2_TR.tmx");		//오른쪽 위쪽
	MAKEMAP(2, 2, "tmx/Basic_type4.tmx");			//왼쪽 오른쪽 위쪽 아래쪽
	MAKEMAP(3, 2, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(4, 2, "tmx/Basic_type2_LB.tmx");		//왼쪽 아래쪽
	MAKEMAP(1, 3, "tmx/Basic_type1_Bottom.tmx");	//아래쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type2_LT.tmx");		//왼쪽 위쪽
	MAKEMAP(3, 4, "tmx/Basic_type1_Bottom.tmx");	//아래쪽
}

void GameMapManager::doMakeGameMap1(GameMap***& maparr)
{
	MAKEMAP(1, 0, "tmx/Basic_type1_Top.tmx");		//위쪽
	MAKEMAP(1, 1, "tmx/Basic_type3_EmptyL.tmx");	//오른쪽 위쪽 아래쪽
	MAKEMAP(2, 1, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(3, 1, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(4, 1, "tmx/Basic_type1_Left.tmx");		//왼쪽
	MAKEMAP(1, 2, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(2, 2, "tmx/Basic_type2_LT.tmx");		//왼쪽 위쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type3_EmptyB.tmx");	//왼쪽 오른쪽 위쪽
	MAKEMAP(4, 3, "tmx/Basic_type1_Left.tmx");		//왼쪽
	MAKEMAP(0, 4, "tmx/Basic_type2_Right.tmx");		//오른쪽
	MAKEMAP(1, 4, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(2, 4, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(3, 4, "tmx/Basic_type1_LB.tmx");		//왼쪽 아래쪽
}

void GameMapManager::doMakeGameMap2(GameMap***& maparr)
{
	MAKEMAP(1, 0, "tmx/Basic_type1_Top.tmx");		//위쪽
	MAKEMAP(1, 1, "tmx/Basic_type2_TB.tmx");		//위쪽 아래쪽
	MAKEMAP(3, 1, "tmx/Basic_type1_Right.tmx");		//오른쪽
	MAKEMAP(4, 1, "tmx/Basic_type2_LT.tmx");		//왼쪽 위쪽
	MAKEMAP(0, 2, "tmx/Basic_type1_Top.tmx");		//위쪽
	MAKEMAP(1, 2, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(2, 2, "tmx/Basic_type3_EmptyB.tmx");	//왼쪽 오른쪽 위쪽
	MAKEMAP(3, 2, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(4, 2, "tmx/Basic_type2_LB.tmx");		//왼쪽 아래쪽
	MAKEMAP(0, 3, "tmx/Basic_type2_LB.tmx");		//위쪽 아래쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type2_LT.tmx");		//왼쪽 위쪽
	MAKEMAP(0, 4, "tmx/Basic_type2_RB.tmx");		//오른쪽 아래쪽
	MAKEMAP(1, 4, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(2, 4, "tmx/Basic_type2_LR.tmx");		//왼쪽 오른쪽
	MAKEMAP(3, 4, "tmx/Basic_type3_EmptyT.tmx");	//왼쪽 오른쪽 아래쪽
	MAKEMAP(4, 4, "tmx/Basic_type1_Top.tmx");		//왼쪽
}