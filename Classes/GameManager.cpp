#include "GameManager.h"
#include "GameSummaryScene.h"
#include <iostream>
#include <format>

GameOverInfo::GameOverInfo()
{

}

void GameOverInfo::clear()
{
	run_time = 0.0f;
	damage = 0;
	all_clear = false;
	stage = 1;
	slot_run = 0;
	gold_earn = 0;
}

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
    isPausedByUser = false;
	monsterVec.clear();
	allocateGameMap();
	makeGameMap();
	runningInfo.clear();
    
#if COCOS2D_DEBUG > 0
	auto __d_l = B2DebugDrawLayer::create(PhysicsObject::getWorld());
	_layer->addChild(__d_l, 2);
#else
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

	__timer = _Timer::create();
	_layer->addChild(__timer, 4);
	__timer->setPosition(500, 130);
    
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
			addStageUpLayer();
		_hero->addCoin(numberMonster);
		numberMonster = 0;
	}
}

void GameManager::addStageUpLayer()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto nextStageLayer = cocos2d::LayerColor::create(cocos2d::Color4B(22, 22, 22, 100));

	nextStageLayer->setContentSize(visibleSize);
	nextStageLayer->runAction(cocos2d::FadeTo::create(2.0f, 100));
	nextStageLayer->setTag(3183);
	_layer->addChild(nextStageLayer);

	cocos2d::Sprite* item[2];
	item[0] = cocos2d::Sprite::create("frames/OkButtonNonClick.png");
	item[1] = cocos2d::Sprite::create("frames/OkButtonOnClick.png");
	item[0]->getTexture()->setTexParameters(TEX_PARA);
	item[1]->getTexture()->setTexParameters(TEX_PARA);

	auto okItem = cocos2d::MenuItemSprite::create(item[0], item[1],
		CC_CALLBACK_1(GameManager::goNextStage, this));

	if (okItem == nullptr ||
		okItem->getContentSize().width <= 0 ||
		okItem->getContentSize().height <= 0)
	{
	}
	else
	{
		float x = visibleSize.width / 2;
		float y = visibleSize.height / 2 - 100;
		okItem->setPosition(cocos2d::Vec2(x, y));
		okItem->setScale(2.5f);
	}

	auto menu = cocos2d::Menu::create(okItem, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);

	nextStageLayer->addChild(menu);
}

void GameManager::goNextStage(cocos2d::Ref* pSender)
{
	if (gameStage >= 3)
	{
		gameOver(true);
	}
	_layer->removeChildByTag(3183);

	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());
	auto wall = _gameMap[currentPosition.first][currentPosition.second]->_wall;
	if (wall) PhysicsObject::getWorld()->DestroyBody(wall);
	removeAllGameMap();
	allocateGameMap();
	currentPosition = std::make_pair(mapWidth / 2, mapHeight / 2);
	gameStage++;
	runningInfo.stage = gameStage;

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
    std::vector<cocos2d::Node*> removal_vec;
    for (auto iter : _layer->getChildren()) {
        int tag = iter->getTag();
        if (tag == TAG_MONSTER_DEAD || (tag >> 12) == 0x2) {
            removal_vec.push_back(iter);
        }
    }
    for (auto iter : removal_vec) {
        iter->removeFromParent();
    }
    
	if (!_gameMap[w][h]->getIsClear())
	{
		monsterManager.createMonster(gameStage, _gameMap[w][h]->getIsBossRoom());
		numberMonster = monsterVec.size();
        if (_hero->getCoin()) {
            for (auto iter : _layer->getChildren()) {
                if (iter->getName() == "state_layer") continue;
                if (iter->getTag() == TAG_MONSTER) {
                    ((BaseMonster*)iter)->stopAllActions();
                    iter->pause();
                }
                _hero->stopAllActions();
                _hero->Node::pause();
                iter->pause();
            }
            
            if (!_layer->getChildByName("state_layer")->getChildByName<SlotMachine*>("slot_machine")->isRunning()) {
                auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
                auto helper = cocos2d::LayerColor::create();
                helper->setContentSize(visibleSize);
                helper->setColor(cocos2d::Color3B(20, 15, 10));
                helper->setOpacity(200);
                helper->setName("helper_layer");
                _layer->addChild(helper, 100);
                
                auto helper_label = Label::createWithTTF("Press 'Space Bar' to continue", "fonts/Marker Felt.ttf", 300);
                helper_label->setScale(0.2f);
                helper_label->setPosition(visibleSize/2);
                helper->addChild(helper_label);
            }
        }
	}
    
    auto black_layer = _layer->getChildByName("black");
    if (black_layer) black_layer->removeFromParent();
    
	TMXTiledMap* temp = doLoadGameMap(w, h);
	temp->setPosition(0, 130);
	_layer->addChild(temp, 0);
    
    auto wall = PhysicsObject::createWall(temp);
    if (wall) {
        _gameMap[w][h]->_wall = wall;
        wall->SetTransform(wall->GetPosition() + b2Vec2(0, 130/PTM_RATIO), 0.0f);
    }
	if (_hero->getCoin()) _hero->disarm(0.0f);
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

void GameManager::gameOver(bool allclear)
{
	if (isGameOver)
		return;
	_layer->removeChildByTag(3183);
	//----------------------------------------------
	runningInfo.run_time = _Timer::getTime();
	runningInfo.all_clear = allclear;
	_layer->removeChild(__timer);
	//----------------------------------------------
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
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
	

	menu->setPosition(cocos2d::Vec2::ZERO);
	auto gameoverSprite = cocos2d::Sprite::create("frames/GameOver.png");
	if (!allclear)
	{
		gameoverSprite->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
		gameoverSprite->setScale(0.3f);
		gameoverSprite->getTexture()->setTexParameters(TEX_PARA);
		gameOverLayer->addChild(gameoverSprite);
		gameOverLayer->addChild(menu);
	}
	else
	{

	}
	_layer->addChild(gameOverLayer, 50);
    _hero->pause(std::numeric_limits<float>::max());
    _hero->stopAllActions();
	isGameOver = true;
}

void GameManager::pauseGame() {
    auto director = cocos2d::Director::getInstance();
    if (isPausedByUser) {
        menuResumeGameCallback(nullptr);
        return;
    }
    
    auto helper = _layer->getChildByName("helper_layer");
    if (helper) helper->removeFromParent();
    
    director->pause();
    auto visibleSize = director->getVisibleSize();
    auto pauseLayer = cocos2d::LayerColor::create();
    pauseLayer->setContentSize(visibleSize);
    pauseLayer->setColor(cocos2d::Color3B(20, 15, 10));
    pauseLayer->setOpacity(200);
    pauseLayer->setName("pause_layer");
    
    cocos2d::Sprite* item[2][2];
    item[0][0] = cocos2d::Sprite::create("frames/ExitNonClick.png");
    item[0][1] = cocos2d::Sprite::create("frames/ExitOnClick.png");
    item[1][0] = cocos2d::Sprite::create("frames/PlayNonClick.png");
    item[1][1] = cocos2d::Sprite::create("frames/PlayOnClick.png");
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            item[i][j]->setScale(0.75f);
            item[i][j]->getTexture()->setTexParameters(TEX_PARA);
        }
    }
    
    auto closeItem = MenuItemSprite::create(item[0][0], item[0][1], CC_CALLBACK_1(GameManager::menuGotoSummarySceneCallback, this));
    auto playItem = MenuItemSprite::create(item[1][0], item[1][1], CC_CALLBACK_1(GameManager::menuResumeGameCallback, this));
    auto menu = Menu::create(closeItem, playItem, NULL);
    
    menu->alignItemsVerticallyWithPadding(-20.0f);
    menu->setPosition(Vec2(visibleSize.width / 2 + 50.0f, visibleSize.height / 2));
    pauseLayer->addChild(menu, 1);
    _layer->addChild(pauseLayer, 10);
    isPausedByUser = true;
    isGameOver = true;
}

void GameManager::menuGotoSummarySceneCallback(cocos2d::Ref* pSender)
{
    PhysicsObject::removeAllMask();
	PhysicsObject::getWorld()->Step(0.0f, 0, 0);
    clearLayer();
    auto director = cocos2d::Director::getInstance();
    if (director->isPaused()) director->resume();
    
	const auto scene = GameSummary::create();
	director->replaceScene(cocos2d::TransitionCrossFade::create(0.5, scene));
	_layer->removeChild(_gameMap[currentPosition.first][currentPosition.second]->getTmxTiledMap());

	auto wall = _gameMap[currentPosition.first][currentPosition.second]->_wall;
	if (wall) PhysicsObject::getWorld()->DestroyBody(wall);
	removeAllGameMap();
}

void GameManager::menuResumeGameCallback(cocos2d::Ref *pSender) {
    if (!isPausedByUser) return;
    isPausedByUser = false;
    auto director = cocos2d::Director::getInstance();
    director->resume();
    _layer->getChildByName("pause_layer")->removeFromParent();
}

void GameManager::update(float dt)
{
	PhysicsObject::getWorld()->Step(dt, 8, 3);
	bool isClear = false;
	if (!isGameOver)
	{
		updateMapClear();
		isClear = _gameMap[currentPosition.first][currentPosition.second]->getIsClear();
		if (_hero->getHP() <= 0 && !_hero->isAnimationRunning())
			gameOver(false);
        _hero->getDirection(isClear, 0.7f);
	}
}

    
//==================================================================================
//						for test
//==================================================================================
Hero* GameManager::getHero() const
{
	return _hero;
}
