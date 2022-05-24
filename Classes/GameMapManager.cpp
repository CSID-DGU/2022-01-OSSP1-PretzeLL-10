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

    auto _event_dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	auto _keyboard_listener = cocos2d::EventListenerKeyboard::create();
	_keyboard_listener->onKeyPressed = CC_CALLBACK_2(GameMapManager::onKeyPressed, this);
	_keyboard_listener->onKeyReleased = CC_CALLBACK_2(GameMapManager::onKeyReleased, this);
	_event_dispatcher->addEventListenerWithSceneGraphPriority(_keyboard_listener, _layer);
    auto _mouse_listener = cocos2d::EventListenerMouse::create();
    _mouse_listener->onMouseMove = CC_CALLBACK_1(GameMapManager::onMouseMove, this);
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_mouse_listener, _layer);

    _world = PhysicsObject::getWorld();
	_hero = Hero::create();
	_hero->setAbsolutePosition(500, 500);
#if COCOS2D_DEBUG > 0
	auto _debug_layer = B2DebugDrawLayer::create(_world);
	_layer->addChild(_debug_layer, 2);
#endif
    _layer->scheduleUpdate();
	_layer->addChild(_hero, 2);
    
    _slot = SlotMachine::create();
    _slot->setScale(0.5f);
    _slot->setAnchorPoint(cocos2d::Vec2(1.0f, 0.5f));
    _layer->addChild(_slot, 3);
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
	temp->setPosition(0, 130);
	_layer->addChild(temp);
    _wall = PhysicsObject::createWall(temp);
    if (_wall) _wall->SetTransform(_wall->GetPosition() + b2Vec2(0, 130/PTM_RATIO), 0.0f);
}

TMXTiledMap* GameMapManager::doLoadGameMap(int w, int h)
{
	//if (!_gameMap[0])
		_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
    if (_wall) PhysicsObject::getWorld()->DestroyBody(_wall);
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
		_hero->setAbsolutePosition(500, 500);
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

void GameMapManager::update(float dt)
{
	_world->Step(dt, 8, 3);
}

// copy and paste
void GameMapManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode) {
        case KEY_GROUP_UP           : _hero->move(UP); break;
        case KEY_GROUP_LEFT         : _hero->move(LEFT); break;
        case KEY_GROUP_DOWN         : _hero->move(DOWN); break;
        case KEY_GROUP_RIGHT        : _hero->move(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->run(); break;
        case KEY_GROUP_M            : _slot->react(_hero); break;
        case keyCode_t::KEY_1       : _hero->changeWeapon(1); break;
        case keyCode_t::KEY_2       : _hero->changeWeapon(2); break;
        case keyCode_t::KEY_3       : _hero->changeWeapon(3); break;
        case keyCode_t::KEY_ESCAPE  : endProgram(); break;
        case keyCode_t::KEY_ENTER   : _hero->attack(); break;
        default: break;
	}
}

void GameMapManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

void GameMapManager::onMouseMove(cocos2d::EventMouse* event) {
    cocos2d::Vec2 pos;
    pos.x = event->getCursorX();
    pos.y = event->getCursorY();
    _hero->updateMouse(pos);
}
