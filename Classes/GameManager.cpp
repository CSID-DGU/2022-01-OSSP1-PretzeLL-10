#include "GameManager.h"
#include "GameStateLayer.h"

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
	_gameMap = new GameMap **[mapWidth];
	for (int i = 0; i < mapWidth; i++)
	{
		_gameMap[i] = new GameMap *[mapHeight];
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
	currentPosition = std::make_pair(mapWidth / 2 + 1, mapHeight / 2 + 1);
	makeGameMap();
	loadGameMap(currentPosition.first, currentPosition.second);

	//------------------------------------------------- for merge object code
//	auto _event_dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
//	auto __l_k = cocos2d::EventListenerKeyboard::create();
//	__l_k->onKeyPressed = CC_CALLBACK_2(GameManager::onKeyPressed, this);
//	__l_k->onKeyReleased = CC_CALLBACK_2(GameManager::onKeyReleased, this);
//    _event_dispatcher->addEventListenerWithSceneGraphPriority(__l_k, _layer);
//    auto _mouse_listener = cocos2d::EventListenerMouse::create();
//    _mouse_listener->onMouseMove = CC_CALLBACK_1(GameManager::onMouseMove, this);
//    _event_dispatcher->addEventListenerWithSceneGraphPriority(_mouse_listener, _layer);
    
    PhysicsObject::getWorld();
	_hero = Hero::create();
	_hero->setAbsolutePosition(500, 500);
	_hero->setZOrder(2);
    
    auto event = EventHandler::create();
    event->setup(_layer, _hero);
    _layer->addChild(event);

#if COCOS2D_DEBUG > 0
	auto __d_l = B2DebugDrawLayer::create(PhysicsObject::getWorld());
	_layer->addChild(__d_l, 2);
#endif
	_layer->scheduleUpdate();

	_layer->addChild(_hero);

	//------------------------------------------------- addChild GameStateLayer
	_state_layer = GameStateLayer::create();
	_state_layer->startNewGame(_hero);
	_layer->addChild(_state_layer);
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
	temp->setPosition(0, 140);
	_layer->addChild(temp);
}

TMXTiledMap* GameManager::doLoadGameMap(int w, int h)
{
	//if (!_gameMap[0])
	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
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
