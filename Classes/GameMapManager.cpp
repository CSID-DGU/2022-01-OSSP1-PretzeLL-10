#include "GameMapManager.h"

#define MAKEMAP(x, y, string) maparr[x][y] = new GameMap(string)
#define MAPNUMBER 1

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
	MAKEMAP(0, 0, "tmx/samplemap3.tmx");
	MAKEMAP(1, 0, "tmx/samplemap1.tmx");
	MAKEMAP(2, 0, "tmx/samplemap2.tmx");
	MAKEMAP(3, 0, "tmx/samplemap0.tmx");
	MAKEMAP(2, 1, "tmx/samplemap3.tmx");
	MAKEMAP(3, 1, "tmx/samplemap2.tmx");
	MAKEMAP(4, 1, "tmx/samplemap1.tmx");
	MAKEMAP(1, 2, "tmx/samplemap0.tmx");
	MAKEMAP(2, 2, "tmx/samplemap3.tmx");
	MAKEMAP(3, 2, "tmx/samplemap2.tmx");
	MAKEMAP(4, 2, "tmx/samplemap1.tmx");
	MAKEMAP(1, 3, "tmx/samplemap3.tmx");
	MAKEMAP(2, 3, "tmx/samplemap2.tmx");
	MAKEMAP(3, 3, "tmx/samplemap1.tmx");
	MAKEMAP(3, 4, "tmx/samplemap1.tmx");
}

void GameMapManager::doMakeGameMap1(GameMap***& maparr)
{
	MAKEMAP(1, 0, "tmx/samplemap3.tmx");
	MAKEMAP(1, 1, "tmx/samplemap1.tmx");
	MAKEMAP(2, 1, "tmx/samplemap2.tmx");
	MAKEMAP(3, 1, "tmx/samplemap0.tmx");
	MAKEMAP(4, 1, "tmx/samplemap3.tmx");
	MAKEMAP(1, 2, "tmx/samplemap2.tmx");
	MAKEMAP(2, 2, "tmx/samplemap1.tmx");
	MAKEMAP(2, 3, "tmx/samplemap0.tmx");
	MAKEMAP(3, 3, "tmx/samplemap3.tmx");
	MAKEMAP(4, 3, "tmx/samplemap2.tmx");
	MAKEMAP(0, 4, "tmx/samplemap1.tmx");
	MAKEMAP(1, 4, "tmx/samplemap1.tmx");
	MAKEMAP(2, 4, "tmx/samplemap1.tmx");
	MAKEMAP(3, 4, "tmx/samplemap1.tmx");
}

void GameMapManager::doMakeGameMap2(GameMap***& maparr)
{
	MAKEMAP(1, 0, "tmx/samplemap3.tmx");
	MAKEMAP(1, 1, "tmx/samplemap1.tmx");
	MAKEMAP(3, 1, "tmx/samplemap2.tmx");
	MAKEMAP(4, 1, "tmx/samplemap0.tmx");
	MAKEMAP(0, 2, "tmx/samplemap3.tmx");
	MAKEMAP(1, 2, "tmx/samplemap2.tmx");
	MAKEMAP(2, 2, "tmx/samplemap1.tmx");
	MAKEMAP(3, 2, "tmx/samplemap0.tmx");
	MAKEMAP(4, 2, "tmx/samplemap3.tmx");
	MAKEMAP(0, 3, "tmx/samplemap2.tmx");
	MAKEMAP(2, 3, "tmx/samplemap1.tmx");
	MAKEMAP(3, 3, "tmx/samplemap1.tmx");
	MAKEMAP(0, 4, "tmx/samplemap0.tmx");
	MAKEMAP(1, 4, "tmx/samplemap3.tmx");
	MAKEMAP(2, 4, "tmx/samplemap2.tmx");
	MAKEMAP(3, 4, "tmx/samplemap1.tmx");
	MAKEMAP(4, 4, "tmx/samplemap1.tmx");
}