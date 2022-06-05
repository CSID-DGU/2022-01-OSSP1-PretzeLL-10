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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    //============================================================================================
    //                          buttons for test
    //============================================================================================
    auto goRight = MenuItemFont::create("Right", CC_CALLBACK_1(GameScene::mapTravelRight, this));
    auto goLeft = MenuItemFont::create("Left", CC_CALLBACK_1(GameScene::mapTravelLeft, this));
    auto goUp = MenuItemFont::create("Up", CC_CALLBACK_1(GameScene::mapTravelUp, this));
    auto goDown = MenuItemFont::create("Down", CC_CALLBACK_1(GameScene::mapTravelDown, this));
    auto damage = MenuItemFont::create("Damage", CC_CALLBACK_1(GameScene::heroDamage, this));
    auto levelup = MenuItemFont::create("Stage Up", CC_CALLBACK_1(GameScene::levelup, this));
    //auto mapTravelPrev = MenuItemFont::create("previous", CC_CALLBACK_1(GameScene::mapTravelPrev, this));
    auto mapMenu = Menu::create(goUp, goDown, goRight, goLeft, damage, levelup, NULL);
    mapMenu->alignItemsVertically();
    mapMenu->setPosition(Vec2(100, 200));
    this->addChild(mapMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    _gamemapmanager = GameManager::getInstance();


    addChild(_gamemapmanager->getLayer());
    addChild(_Timer::create());

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

void GameScene::mapTravelUp(Ref* pSender)
{
    GameManager::getInstance()->loadUpMap();
}

void GameScene::mapTravelDown(Ref* pSender)
{
    GameManager::getInstance()->loadDownMap();
}

void GameScene::mapTravelRight(Ref* pSender)
{
    GameManager::getInstance()->loadRightMap();
}

void GameScene::mapTravelLeft(Ref* pSender)
{
    GameManager::getInstance()->loadLeftMap();
}

void GameScene::goNextLevel(Ref* pSender)
{

}

void GameScene::levelup(Ref* pSender)
{
    GameManager::getInstance()->goNextStage();
}

void GameScene::heroDamage(Ref* pSender)
{
    GameManager::getInstance()->getHero()->damaged(1);
}
