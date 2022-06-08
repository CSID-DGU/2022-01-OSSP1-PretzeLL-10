#include "GameMapManager.h"

#define MAKEMAP(x, y, string) maparr[x][y] = new GameMap(string)
#define STARTMAP(x, y, string) maparr[x][y] = new GameMap(string, true, false)
#define MAPNUMBER 5

void GameMapManager::makeGameMap(GameMap ***&maparr)
{
	engine = std::mt19937_64(rand_device());
	rand = std::uniform_int_distribution<int>(0, MAPNUMBER - 1);

	int x = rand(engine);
	std::cout << "Map number : " << x << std::endl;
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
	case 3:
		doMakeGameMap3(maparr);
		break;
	case 4:
		doMakeGameMap4(maparr);
		break;
	default:
		break;
	}
}

void GameMapManager::doMakeGameMap0(GameMap ***&maparr)
{
	maparr[0][0] = new GameMap("tmx/Basic_type1_Right_c.tmx", true);
	MAKEMAP(1, 0, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(2, 0, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(3, 0, "tmx/Basic_type2_LT_c.tmx");	   //왼쪽 위쪽
	MAKEMAP(2, 1, "tmx/Basic_type2_TR_c.tmx");	   //오른쪽 위쪽
	MAKEMAP(3, 1, "tmx/Basic_type2_LB_c.tmx");	   //왼쪽 아래쪽
	MAKEMAP(4, 1, "tmx/Basic_type1_Top_c.tmx");	   //위쪽
	MAKEMAP(1, 2, "tmx/Basic_type2_TR_c.tmx");		//오른쪽 위쪽
	STARTMAP(2, 2, "tmx/Basic_type4_c.tmx");		//왼쪽 오른쪽 위쪽 아래쪽
	MAKEMAP(3, 2, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(4, 2, "tmx/Basic_type2_LB_c.tmx");	   //왼쪽 아래쪽
	MAKEMAP(1, 3, "tmx/Basic_type1_Bottom_c.tmx"); //아래쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type2_LT_c.tmx");	   //왼쪽 위쪽
	MAKEMAP(3, 4, "tmx/Basic_type1_Bottom_c.tmx"); //아래쪽
}

void GameMapManager::doMakeGameMap1(GameMap ***&maparr)
{
	MAKEMAP(1, 0, "tmx/Basic_type1_Top_c.tmx");	   //위쪽
	MAKEMAP(1, 1, "tmx/Basic_type3_EmptyL_c.tmx"); //오른쪽 위쪽 아래쪽
	MAKEMAP(2, 1, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(3, 1, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	maparr[4][1] = new GameMap("tmx/Basic_type1_Left_c.tmx", true);
	MAKEMAP(1, 2, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	STARTMAP(2, 2, "tmx/Basic_type2_LT_c.tmx");	   //왼쪽 위쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type3_EmptyB_c.tmx"); //왼쪽 오른쪽 위쪽
	MAKEMAP(4, 3, "tmx/Basic_type1_Left_c.tmx");   //왼쪽
	MAKEMAP(0, 4, "tmx/Basic_type1_Right_c.tmx");  //오른쪽
	MAKEMAP(1, 4, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(2, 4, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(3, 4, "tmx/Basic_type2_LB_c.tmx");	   //왼쪽 아래쪽
}

void GameMapManager::doMakeGameMap2(GameMap ***&maparr)
{
	MAKEMAP(1, 0, "tmx/Basic_type1_Top_c.tmx");	   //위쪽
	MAKEMAP(1, 1, "tmx/Basic_type2_TB_c.tmx");	   //위쪽 아래쪽
	maparr[3][1] = new GameMap("tmx/Basic_type1_Right_c.tmx", true);	//오른쪽
	MAKEMAP(4, 1, "tmx/Basic_type2_LT_c.tmx");	   //왼쪽 위쪽
	MAKEMAP(0, 2, "tmx/Basic_type1_Top_c.tmx");	   //위쪽
	MAKEMAP(1, 2, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	STARTMAP(2, 2, "tmx/Basic_type3_EmptyB_c.tmx"); //왼쪽 오른쪽 위쪽
	MAKEMAP(3, 2, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(4, 2, "tmx/Basic_type2_LB_c.tmx");	   //왼쪽 아래쪽
	MAKEMAP(0, 3, "tmx/Basic_type2_TB_c.tmx");	   //위쪽 아래쪽
	MAKEMAP(2, 3, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type2_LT_c.tmx");	   //왼쪽 위쪽
	MAKEMAP(0, 4, "tmx/Basic_type2_RB_c.tmx");	   //오른쪽 아래쪽
	MAKEMAP(1, 4, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(2, 4, "tmx/Basic_type2_LR_c.tmx");	   //왼쪽 오른쪽
	MAKEMAP(3, 4, "tmx/Basic_type3_EmptyT_c.tmx"); //왼쪽 오른쪽 아래쪽
	MAKEMAP(4, 4, "tmx/Basic_type1_Left_c.tmx");   //왼쪽
}

void GameMapManager::doMakeGameMap3(GameMap***& maparr)
{
	maparr[2][0] = new GameMap("tmx/Basic_type1_Right_c.tmx", true);	//오른쪽
	MAKEMAP(3, 0, "tmx/Basic_type2_LR_c.tmx");			//왼쪽 오른쪽
	MAKEMAP(4, 0, "tmx/Basic_type2_LT_c.tmx");			//왼쪽 위쪽
	MAKEMAP(4, 1, "tmx/Basic_type2_TB_c.tmx");			//위쪽 아래쪽
	MAKEMAP(0, 2, "tmx/Basic_type1_Right_c.tmx");		//오른쪽
	MAKEMAP(1, 2, "tmx/Basic_type3_EmptyB_c.tmx");		//왼쪽 오른쪽 위쪽 		
	STARTMAP(2, 2, "tmx/Basic_type2_LR_c.tmx");			//왼쪽 오른쪽
	MAKEMAP(3, 2, "tmx/Basic_type3_EmptyB_c.tmx");		//왼쪽 오른쪽 위쪽
	MAKEMAP(4, 2, "tmx/Basic_type2_LB_c.tmx");			//왼쪽 아래쪽
	MAKEMAP(1, 3, "tmx/Basic_type2_TB_c.tmx");			//위쪽 아래쪽
	MAKEMAP(3, 3, "tmx/Basic_type1_Bottom_c.tmx");		//아래쪽
	MAKEMAP(1, 4, "tmx/Basic_type2_RB_c.tmx");			//오른쪽 아래쪽 
	MAKEMAP(2, 4, "tmx/Basic_type1_Left_c.tmx");		//왼쪽
}

void GameMapManager::doMakeGameMap4(GameMap***& maparr)
{
	maparr[0][0] = new GameMap("tmx/Basic_type1_Right_c.tmx", true);	//오른쪽
	MAKEMAP(1, 0, "tmx/Basic_type2_LR_c.tmx");			//왼쪽 오른쪽
	MAKEMAP(2, 0, "tmx/Basic_type2_LT_c.tmx");			//왼쪽 위쪽
	MAKEMAP(2, 1, "tmx/Basic_type2_TB_c.tmx");			//위쪽 아래쪽
	STARTMAP(2, 2, "tmx/Basic_type3_EmptyL_c.tmx");		//오른쪽 위쪽 아래쪽
	MAKEMAP(3, 2, "tmx/Basic_type2_LR_c.tmx");			//왼쪽 오른쪽
	MAKEMAP(4, 2, "tmx/Basic_type1_Left_c.tmx");		//왼쪽
	MAKEMAP(1, 3, "tmx/Basic_type1_Right_c.tmx");		//오른쪽
	MAKEMAP(2, 3, "tmx/Basic_type3_EmptyR_c.tmx");		//왼쪽 위쪽 아래쪽
	MAKEMAP(2, 4, "tmx/Basic_type2_RB_c.tmx");			//오른쪽 아래쪽
	MAKEMAP(3, 4, "tmx/Basic_type1_Left_c.tmx");		//왼쪽
}
