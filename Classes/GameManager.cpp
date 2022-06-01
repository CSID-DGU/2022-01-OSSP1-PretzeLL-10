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
	mapWidth = 5;
	mapHeight = 5;
	_gameMap = new GameMap * *[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		_gameMap[i] = new GameMap * [mapHeight];
	}
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			_gameMap[i][j] = NULL;
		}
	}
}

void GameManager::makeGameMap()
{
	mapManager.makeGameMap(_gameMap);
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
	monsterVec.clear();
	makeGameMap();
	
    
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
    
<<<<<<< HEAD
=======
//    auto _big_demon = BigDemon::create();
//    _big_demon->setAbsolutePosition(300, 700);
//    _big_demon->setScale(2.0f);
//    _big_demon->setLocalZOrder(2);
//    _layer->addChild(_big_demon);

>>>>>>> TACStest
	//------------------------------------------------- addChild GameStateLayer
	_state_layer = GameStateLayer::create();
	_state_layer->startNewGame(_hero);
	_layer->addChild(_state_layer);
    
    auto event = EventHandler::create();
    event->setup(_layer);
    _layer->addChild(event);
	//--------------------------------------------------
	loadGameMap(currentPosition.first, currentPosition.second);
}

void GameManager::createMonsters()
{
	auto _big_demon = BigDemon::create();
	monsterVec.push_back(_big_demon);
	_big_demon->setAbsolutePosition(300, 700);
	_big_demon->setScale(2.0f);
	_big_demon->setLocalZOrder(2);
	_layer->addChild(_big_demon);
}

void GameManager::deleteMonster(BaseMonster* dM)
{
	auto iter = std::vector<BaseMonster*>::iterator();
	for (iter = monsterVec.begin(); iter!=monsterVec.end();iter++)
	{
		if ((*iter) == dM)
		{
			monsterVec.erase(iter);
			return;
		}
	}
}

void GameManager::updateMapClear()
{
	if (monsterVec.empty())
		_gameMap[currentPosition.first][currentPosition.second]->setClear();
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
	if (!_gameMap[w][h]->getIsClear())
		createMonsters();

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
		if (_gameMap[currentPosition.first][currentPosition.second + 1] == nullptr)
			return;
		//-------------test start--------------
		if (!_gameMap[currentPosition.first][currentPosition.second]->getIsClear())
			return;
		//-------------test end---------------
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
		if (_gameMap[currentPosition.first][currentPosition.second - 1] == nullptr)
			return;
		//-------------test start--------------
		if (!_gameMap[currentPosition.first][currentPosition.second]->getIsClear())
			return;
		//-------------test end---------------
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
		if (_gameMap[currentPosition.first + 1][currentPosition.second] == nullptr)
			return;
		//-------------test start--------------
		if (!_gameMap[currentPosition.first][currentPosition.second]->getIsClear())
			return;
		//-------------test end---------------
		loadGameMap(currentPosition.first + 1, currentPosition.second);
		currentPosition.first++;
	}
}

void GameManager::loadLeftMap()
{
	if (currentPosition.first <= 0)
		return;
	else
	{
		if (_gameMap[currentPosition.first - 1][currentPosition.second] == nullptr)
			return;
		//-------------test start--------------
		if (!_gameMap[currentPosition.first][currentPosition.second]->getIsClear())
			return;
		//-------------test end---------------
		loadGameMap(currentPosition.first - 1, currentPosition.second);
		currentPosition.first--;
	}
}

void GameManager::update(float dt)
{
	PhysicsObject::getWorld()->Step(dt, 8, 3);
	updateMapClear();
    switch (_hero->getDirection()) {
        case MAP_UP     : loadUpMap();    break;
        case MAP_DOWN   : loadDownMap();  break;
        case MAP_LEFT   : loadLeftMap();  break;
        case MAP_RIGHT  : loadRightMap(); break;
        default: break;
    }
}


//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return _hero;
}
