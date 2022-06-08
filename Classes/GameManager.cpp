#include "GameManager.h"
#include "GameSummaryScene.h"
#include "Timer.h"
#include <iostream>
#include <format>

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

void GameManager::allocateGameMap()
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

void GameManager::removeAllGameMap()
{
	for (int i = 0; i < mapWidth; i++)
		for (int j = 0; j < mapHeight; j++)
			if (_gameMap[i][j] != nullptr)
				_gameMap[i][j]->getTmxTiledMap()->release();
	deleteGameMap();
}

GameManager::GameManager()
	: _layer(cocos2d::Layer::create()), gameStage(0), mapWidth(0), mapHeight(0), isGameOver(true), numberMonster(0)
{
	_layer->retain();
}

void GameManager::startNewGame()
{
	numberMonster = 0;
	gameStage = 1;
	mapWidth = 5;
	mapHeight = 5;
	currentPosition = std::make_pair(mapWidth / 2, mapHeight / 2);
	isGameOver = false;
	monsterVec.clear();
	allocateGameMap();
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
    
	//------------------------------------------------- addChild GameStateLayer
	_state_layer = GameStateLayer::create();
	_state_layer->startNewGame(_hero);
	_layer->addChild(_state_layer, 5);

	auto timer = _Timer::create();
	_layer->addChild(timer);
    
    auto event = EventHandler::create();
    event->setup(_layer);
    _layer->addChild(event);
	//--------------------------------------------------
	loadGameMap(currentPosition.first, currentPosition.second);
}

void GameManager::addMonsters2(BaseMonster* monster)
{
	monsterVec.push_back(monster);
	_layer->addChild(monster);
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
	{
		_gameMap[currentPosition.first][currentPosition.second]->setClear();
		if (_gameMap[currentPosition.first][currentPosition.second]->getIsBossRoom())
			goNextStage();
		_hero->addCoin(numberMonster);
		numberMonster = 0;
	}
}

void GameManager::goNextStage()
{
	if (gameStage >= 3)
	{
		// game All clear
	}

	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
	auto wall = _gameMap[currentPosition.first][currentPosition.second]->_wall;
	if (wall) PhysicsObject::getWorld()->DestroyBody(wall);
	removeAllGameMap();
	allocateGameMap();
	currentPosition = std::make_pair(mapWidth / 2, mapHeight / 2);
	gameStage++;

	mapManager.makeGameMap(_gameMap);
	loadGameMap(currentPosition.first, currentPosition.second);

	_hero->setAbsolutePosition(500, 600);
}

void GameManager::clearLayer()
{
	_layer->removeAllChildren();
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
	{
		monsterManager.createMonster(gameStage, _gameMap[w][h]->getIsBossRoom());
		numberMonster = monsterVec.size();
	}

	TMXTiledMap* temp = doLoadGameMap(w, h);
	temp->setPosition(0, 130);
	_layer->addChild(temp, 0);
    
    auto wall = PhysicsObject::createWall(temp);
    if (wall) {
        _gameMap[w][h]->_wall = wall;
        wall->SetTransform(wall->GetPosition() + b2Vec2(0, 130/PTM_RATIO), 0.0f);
    }
	_hero->disarm(0.0f);
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

std::string GameManager::string_format(const std::string& format, int a, int b)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), a, b) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), a, b);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

void GameManager::gameOver()
{
	if (isGameOver)
		return;
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto gameOverLayer = cocos2d::LayerColor::create();
	gameOverLayer->setContentSize(visibleSize);
	gameOverLayer->setColor(cocos2d::Color3B(20, 15, 10));
	gameOverLayer->setOpacity(150);
	gameOverLayer->runAction(cocos2d::FadeTo::create(2.0f, 200));

	// add a "close" icon to exit the progress. it's an autorelease object
    cocos2d::Sprite* item[2];
    item[0] = cocos2d::Sprite::create("frames/OkButtonNonClick.png");
    item[1] = cocos2d::Sprite::create("frames/OkButtonOnClick.png");
    item[0]->getTexture()->setTexParameters(TEX_PARA);
    item[1]->getTexture()->setTexParameters(TEX_PARA);
    
    auto closeItem = cocos2d::MenuItemSprite::create(item[0], item[1],
		CC_CALLBACK_1(GameManager::menuGotoSummarySceneCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2 - 100;
		closeItem->setPosition(cocos2d::Vec2(x, y));
		closeItem->setScale(2.5f);
	}
	// create menu, it's an autorelease object
	auto menu = cocos2d::Menu::create(closeItem, NULL);

	std::string str = string_format("%02d : %02d", int(_Timer::getTime() / 60), int(_Timer::getTime()) % 60);

	auto label = Label::createWithTTF(str, "fonts/Marker Felt.ttf", 60);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - label->getContentSize().height));
	
	gameOverLayer->addChild(label,2);

	menu->setPosition(cocos2d::Vec2::ZERO);
	auto gameoverSprite = cocos2d::Sprite::create("frames/GameOver.png");
	gameoverSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	gameoverSprite->setScale(0.3f);
	gameoverSprite->getTexture()->setTexParameters(TEX_PARA);
	gameOverLayer->addChild(menu);
	gameOverLayer->addChild(gameoverSprite);
	_layer->addChild(gameOverLayer, 50);
    _hero->pause(std::numeric_limits<float>::max());	
	for (auto iter : monsterVec) {
		iter->pause(std::numeric_limits<float>::max());
	}
	PhysicsObject::removeAllMask();
	isGameOver = true;
}

void GameManager::menuGotoSummarySceneCallback(cocos2d::Ref* pSender)
{
	clearLayer();
	const auto scene = GameSummary::create();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionCrossFade::create(0.5, scene));
	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());

	auto wall = _gameMap[currentPosition.first][currentPosition.second]->_wall;
	if (wall) PhysicsObject::getWorld()->DestroyBody(wall);
	removeAllGameMap();
}

void GameManager::update(float dt)
{
	PhysicsObject::getWorld()->Step(dt, 8, 3);
	bool isClear = false;
	if (!isGameOver)
	{
		updateMapClear();
		isClear = _gameMap[currentPosition.first][currentPosition.second]->getIsClear();
		if (_hero->getHP() <= 0)
			gameOver();
		switch (_hero->getDirection(isClear)) {
		case MAP_UP: loadUpMap();    break;
		case MAP_DOWN: loadDownMap();  break;
		case MAP_LEFT: loadLeftMap();  break;
		case MAP_RIGHT: loadRightMap(); break;
		default: break;
		}
	}
}


//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return _hero;
}
