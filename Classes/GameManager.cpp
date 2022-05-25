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

	//------------------------------------------------- for merge object code
	auto _event_dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	auto __l_k = cocos2d::EventListenerKeyboard::create();
	__l_k->onKeyPressed = CC_CALLBACK_2(GameManager::onKeyPressed, this);
	__l_k->onKeyReleased = CC_CALLBACK_2(GameManager::onKeyReleased, this);
    _event_dispatcher->addEventListenerWithSceneGraphPriority(__l_k, _layer);
    auto _mouse_listener = cocos2d::EventListenerMouse::create();
    _mouse_listener->onMouseMove = CC_CALLBACK_1(GameManager::onMouseMove, this);
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_mouse_listener, _layer);

    PhysicsObject::getWorld();
	_hero = Hero::create();
	_hero->setAbsolutePosition(500, 500);
	_hero->setZOrder(2);

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
//						Code for key event
//==================================================================================

void GameManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
        case KEY_GROUP_UP           : _hero->move(UP); break;
        case KEY_GROUP_LEFT         : _hero->move(LEFT); break;
        case KEY_GROUP_DOWN         : _hero->move(DOWN); break;
        case KEY_GROUP_RIGHT        : _hero->move(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->run(); break;
        case keyCode_t::KEY_1       : _hero->changeWeapon(1); break;
        case keyCode_t::KEY_2       : _hero->changeWeapon(2); break;
        case keyCode_t::KEY_3       : _hero->changeWeapon(3); break;
        case keyCode_t::KEY_ENTER   : _hero->attack(); break;
            
        case KEY_GROUP_M            : _state_layer->react(); break;             // for test
        case keyCode_t::KEY_ESCAPE  : endProgram(); break;
        default: break;
    }
}

void GameManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
        case KEY_GROUP_UP           : _hero->stop(UP); break;
        case KEY_GROUP_DOWN         : _hero->stop(DOWN); break;
        case KEY_GROUP_LEFT         : _hero->stop(LEFT); break;
        case KEY_GROUP_RIGHT        : _hero->stop(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->stopRun(); break;
        case keyCode_t::KEY_ENTER   : _hero->attack(); break;
        default: break;
    }
}

void GameManager::onMouseMove(cocos2d::EventMouse* event) {
    cocos2d::Vec2 pos;
    pos.x = event->getCursorX();
    pos.y = event->getCursorY();
    _hero->updateMouse(pos);
}

//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return _hero;
}
