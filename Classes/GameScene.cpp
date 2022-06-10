
#include "GameScene.h"
#include "GameSummaryScene.h"
#include "SimpleAudioEngine.h"
#include "Timer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background_layer = LayerColor::create(Color4B(22, 11, 18, 255));
    addChild(background_layer);

    //============================================================================================
    //                          buttons for test
    //============================================================================================
    auto damage = MenuItemFont::create("Damage", CC_CALLBACK_1(GameScene::heroDamage, this));
    //auto mapTravelPrev = MenuItemFont::create("previous", CC_CALLBACK_1(GameScene::mapTravelPrev, this));
    auto mapMenu = Menu::create(damage, NULL);
    mapMenu->alignItemsVertically();
    mapMenu->setPosition(Vec2(100, 200));
    this->addChild(mapMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    
    _gamemapmanager = GameManager::getInstance();


    addChild(_gamemapmanager->getLayer());

    startNewGame();
    scheduleUpdate();
    return true;
}

void GameScene::update(float delta)

{
    _gamemapmanager->update(delta);
}

void GameScene::startNewGame()
{
    GameManager::getInstance()->startNewGame();
}

//=============================================================== callback for test

void GameScene::heroDamage(Ref* pSender)
{
    auto director = Director::getInstance();
    if (director->isPaused()) director->resume();
    else director->pause();
}
