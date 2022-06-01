#include "GameManager.h"

GameManager* GameManager::sharedGameMapManager = nullptr;

GameManager* GameManager::getInstance()
{
	if (sharedGameMapManager == nullptr)
	{
		sharedGameMapManager = new (std::nothrow) GameManager();
		sharedGameMapManager->init();
	}
	return sharedGameMapManager;
}

void GameManager::init()
{
}

void GameManager::makeGameMap()
{
	_gameMap = new GameMap * *[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		_gameMap[i] = new GameMap * [mapHeight];
	}
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (j % 2 == 0)
				if (i % 2 == 0)
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

void GameManager::deleteGameMap()
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

GameManager::GameManager()
	: _layer(cocos2d::Layer::create()), gameStage(0), mapWidth(0), mapHeight(0)
{
	_layer->retain();
}

void GameManager::startNewGame()
{
	gameStage = 1;
	mapWidth = 5;
	mapHeight = 5;
	currentPosition = std::make_pair(mapWidth / 2 + 1, mapHeight / 2 + 1);
	makeGameMap();
	loadGameMap(currentPosition.first, currentPosition.second);
    
#if COCOS2D_DEBUG > 0
	auto __d_l = B2DebugDrawLayer::create(PhysicsObject::getWorld());
	_layer->addChild(__d_l, 2);
#elif
    PhysicsObject::getWorld();
#endif
	_layer->scheduleUpdate();

    _hero = Hero::create();
    _hero->setAbsolutePosition(500, 500);
    _hero->setLocalZOrder(2);
	_layer->addChild(_hero);
    
    auto _big_demon = BigDemon::create();
    _big_demon->setAbsolutePosition(300, 700);
    _big_demon->setScale(2.0f);
    _big_demon->setLocalZOrder(2);
    _layer->addChild(_big_demon);

	//------------------------------------------------- addChild GameStateLayer
	_state_layer = GameStateLayer::create();
	_state_layer->startNewGame(_hero);
	_layer->addChild(_state_layer);
    
    auto event = EventHandler::create();
    event->setup(_layer);
    _layer->addChild(event);
}

void GameManager::createMonster()
{

}

void GameManager::goNextStage()
{

}

void GameManager::clearLayer()
{
	_layer->removeAllChildren();
}

void GameManager::removeAllGameMap()
{

}

cocos2d::Layer* GameManager::getLayer() const {
	return _layer;
}

//==================================================================================
//						Load GameMap and addchild() to Layer
//==================================================================================

void GameManager::loadGameMap(int w, int h)
{
	TMXTiledMap* temp = doLoadGameMap(w, h);
	temp->setPosition(0, 130);
	_layer->addChild(temp);
    
    auto wall = PhysicsObject::createWall(temp);
    if (wall) {
        _gameMap[w][h]->_wall = wall;
        wall->SetTransform(wall->GetPosition() + b2Vec2(0, 130/PTM_RATIO), 0.0f);
    }
}

TMXTiledMap* GameManager::doLoadGameMap(int w, int h)
{
	//if (!_gameMap[0])
	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
    
    auto wall = _gameMap[currentPosition.first][currentPosition.second]->_wall;
    if (wall) PhysicsObject::getWorld()->DestroyBody(wall);
    
	return _gameMap[w][h]->getTmxTiledMap();
}

void GameManager::loadUpMap()
{
	if (currentPosition.second >= mapHeight - 1)
		return;
	else
	{
		loadGameMap(currentPosition.first, currentPosition.second + 1);
		currentPosition.second++;
	}
}

void GameManager::loadDownMap()
{
	if (currentPosition.second <= 0)
		return;
	else
	{
		loadGameMap(currentPosition.first, currentPosition.second - 1);
		currentPosition.second--;
	}
}

void GameManager::loadRightMap()
{
	if (currentPosition.first >= mapWidth - 1)
		return;
	else
	{
		loadGameMap(currentPosition.first + 1, currentPosition.second);
		currentPosition.first++;
		_hero->setAbsolutePosition(500, 500);
	}
}

void GameManager::loadLeftMap()
{
	if (currentPosition.first <= 0)
		return;
	else
	{
		loadGameMap(currentPosition.first - 1, currentPosition.second);
		currentPosition.first--;
	}
}

void GameManager::update(float dt)
{
	PhysicsObject::getWorld()->Step(dt, 8, 3);
}


//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return _hero;
}
