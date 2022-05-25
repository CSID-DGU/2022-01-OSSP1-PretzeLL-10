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
	auto __e_d = cocos2d::Director::getInstance()->getEventDispatcher();
	auto __l_k = cocos2d::EventListenerKeyboard::create();
	__l_k->onKeyPressed = CC_CALLBACK_2(GameManager::onKeyPressed, this);
	__l_k->onKeyReleased = CC_CALLBACK_2(GameManager::onKeyReleased, this);
	__e_d->addEventListenerWithSceneGraphPriority(__l_k, _layer);

	auto __g = b2Vec2(0.0f, -98.0f);
	__world = new b2World(__g);
	__world->SetAllowSleeping(true);
	__world->SetContinuousPhysics(true);
	PhysicsObject::setWorld(__world);
	__player = Hero::create();
	__player->setAbsolutePosition(500, 500);
	__player->setZOrder(2);
	__player->setInput(NULL, __key.data());

#if COCOS2D_DEBUG > 0
	auto __d_l = B2DebugDrawLayer::create(__world);
	_layer->addChild(__d_l, 2);
#endif
	_layer->scheduleUpdate();

	_layer->addChild(__player);

	//------------------------------------------------- addChild GameStateLayer
	auto _state_layer = GameStateLayer::create();
	_state_layer->startNewGame(__player);
	_layer->addChild(_state_layer, 20);
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
		__player->setAbsolutePosition(500, 500);
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
	__world->Step(dt, 8, 3);
}



//==================================================================================
//						Code for key event
//==================================================================================

void GameManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	typedef cocos2d::EventKeyboard::KeyCode keyCode_t;
	switch (keyCode) {
#ifndef DIR_MOUSE
	case keyCode_t::KEY_W:
	case keyCode_t::KEY_CAPITAL_W:
	case keyCode_t::KEY_UP_ARROW:
		__key[UP] = true;
		__player->move(UP);
		break;
	case keyCode_t::KEY_A:
	case keyCode_t::KEY_CAPITAL_A:
	case keyCode_t::KEY_LEFT_ARROW:
		__key[LEFT] = true;
		__player->move(LEFT);
		break;
	case keyCode_t::KEY_S:
	case keyCode_t::KEY_CAPITAL_S:
	case keyCode_t::KEY_DOWN_ARROW:
		__key[DOWN] = true;
		__player->move(DOWN);
		break;
	case keyCode_t::KEY_D:
	case keyCode_t::KEY_CAPITAL_D:
	case keyCode_t::KEY_RIGHT_ARROW:
		__key[RIGHT] = true;
		__player->move(RIGHT);
		break;
#endif
	case keyCode_t::KEY_SHIFT:
	case keyCode_t::KEY_RIGHT_SHIFT:
		__key[SHIFT] = true;
		__player->run();
		break;
	case keyCode_t::KEY_M:
	case keyCode_t::KEY_CAPITAL_M:
		//__slot_layer->react(__player);
		break;
	case keyCode_t::KEY_1: __player->changeWeapon(1); break;
	case keyCode_t::KEY_2: __player->changeWeapon(2); break;
	case keyCode_t::KEY_3: __player->changeWeapon(3); break;
	case keyCode_t::KEY_ESCAPE: endProgram();
	default: break;
	}
}

void GameManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	typedef cocos2d::EventKeyboard::KeyCode keyCode_t;
	switch (keyCode) {
#ifndef DIR_MOUSE
	case keyCode_t::KEY_W:
	case keyCode_t::KEY_CAPITAL_W:
	case keyCode_t::KEY_UP_ARROW:
		__key[UP] = false;
		__player->stop(UP);
		break;
	case keyCode_t::KEY_S:
	case keyCode_t::KEY_CAPITAL_S:
	case keyCode_t::KEY_DOWN_ARROW:
		__key[DOWN] = false;
		__player->stop(DOWN);
		break;
	case keyCode_t::KEY_A:
	case keyCode_t::KEY_CAPITAL_A:
	case keyCode_t::KEY_LEFT_ARROW:
		__key[LEFT] = false;
		__player->stop(LEFT);
		break;
	case keyCode_t::KEY_D:
	case keyCode_t::KEY_CAPITAL_D:
	case keyCode_t::KEY_RIGHT_ARROW:
		__key[RIGHT] = false;
		__player->stop(RIGHT);
		break;
#endif
	case keyCode_t::KEY_SHIFT:
	case keyCode_t::KEY_RIGHT_SHIFT:
		__key[SHIFT] = false;
		__player->stopRun();
		break;
	default: break;
	}
}

//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return __player;
}