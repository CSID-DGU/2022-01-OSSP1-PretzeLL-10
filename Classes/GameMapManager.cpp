#include "GameMapManager.h"

GameMapManager* GameMapManager::sharedGameMapManager = nullptr;

GameMapManager* GameMapManager::getInstance()
{
	if (sharedGameMapManager == nullptr)
	{
		sharedGameMapManager = new (std::nothrow) GameMapManager();
		sharedGameMapManager->init();
	}
	return sharedGameMapManager;
}

void GameMapManager::init()
{
}

void GameMapManager::makeGameMap()
{
	_gameMap = new GameMap**[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		_gameMap[i] = new GameMap*[mapHeight];
	}
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (j % 2 == 0)
				if(i%2 == 0)
					_gameMap[i][j] = new GameMap("tmx/samplemap0.tmx");
				else
					_gameMap[i][j] = new GameMap("tmx/samplemap1.tmx");
			else
				if (i % 2 == 0)
					_gameMap[i][j] = new GameMap("tmx/samplemap2.tmx");
				else
					_gameMap[i][j] = new GameMap("tmx/samplemap3.tmx");
		}
	}
}

void GameMapManager::deleteGameMap()
{
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
			delete _gameMap[i][j];
	}
	for (int i = 0; i < mapWidth; i++)
	{
		delete[] _gameMap[i];
	}
	delete[] _gameMap;
}

GameMapManager::GameMapManager()
	: _layer(cocos2d::Layer::create()), gameStage(0), mapWidth(0), mapHeight(0)
{
}

void GameMapManager::startNewGame()
{
	gameStage = 1;
	mapWidth = 5;
	mapHeight = 5;
	currentPosition = std::make_pair(mapWidth / 2 + 1, mapHeight / 2 + 1);
	makeGameMap();
	loadGameMap(currentPosition.first, currentPosition.second);
}

void GameMapManager::goNextStage()
{

}

void GameMapManager::clearLayer()
{
	_layer->removeAllChildren();
}

void GameMapManager::removeAllGameMap()
{

}

cocos2d::Layer* GameMapManager::getLayer() const {
	return _layer;
}

void GameMapManager::loadGameMap(int w, int h)
{
	TMXTiledMap *temp = doLoadGameMap(w, h);
	temp->setPosition(0, 140);
	_layer->addChild(temp);
}

TMXTiledMap* GameMapManager::doLoadGameMap(int w, int h)
{
	//if (!_gameMap[0])
		_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
	return _gameMap[w][h]->getTmxTiledMap();
}

void GameMapManager::loadUpMap()
{
	if (currentPosition.second >= mapHeight - 1)
		return;
	else
	{
		loadGameMap(currentPosition.first, currentPosition.second + 1);
		currentPosition.second++;
	}
}

void GameMapManager::loadDownMap()
{
	if (currentPosition.second <= 0)
		return;
	else
	{
		loadGameMap(currentPosition.first, currentPosition.second - 1);
		currentPosition.second--;
	}
}

void GameMapManager::loadRightMap()
{
	if (currentPosition.first >= mapWidth - 1)
		return;
	else
	{
		loadGameMap(currentPosition.first + 1, currentPosition.second);
		currentPosition.first++;
	}
}

void GameMapManager::loadLeftMap()
{
	if (currentPosition.first <= 0)
		return;
	else
	{
		loadGameMap(currentPosition.first - 1, currentPosition.second);
		currentPosition.first--;
	}
}