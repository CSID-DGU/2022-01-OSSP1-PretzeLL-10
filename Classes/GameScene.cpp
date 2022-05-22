#include "GameScene.h"
#include "GameSummaryScene.h"
#include "SimpleAudioEngine.h"

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

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(GameScene::menuGotoSummarySceneCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // for test

    auto goRight = MenuItemFont::create("Right", CC_CALLBACK_1(GameScene::mapTravelRight, this));
    auto goLeft = MenuItemFont::create("Left", CC_CALLBACK_1(GameScene::mapTravelLeft, this));
    auto goUp = MenuItemFont::create("Up", CC_CALLBACK_1(GameScene::mapTravelUp, this));
    auto goDown = MenuItemFont::create("Down", CC_CALLBACK_1(GameScene::mapTravelDown, this));
    //auto mapTravelPrev = MenuItemFont::create("previous", CC_CALLBACK_1(GameScene::mapTravelPrev, this));
    auto mapMenu = Menu::create(goUp, goDown, goRight, goLeft, NULL);
    mapMenu->alignItemsVertically();
    mapMenu->setPosition(Vec2(400, 300));
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
    _gamemapmanager = GameMapManager::getInstance();


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
    GameMapManager::getInstance()->startNewGame();
}

void GameScene::menuGotoSummarySceneCallback(Ref* pSender)
{
    const auto scene = GameSummary::create();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    GameMapManager::getInstance()->clearLayer();
}

void GameScene::mapTravelUp(Ref* pSender)
{
    GameMapManager::getInstance()->loadUpMap();
}

void GameScene::mapTravelDown(Ref* pSender)
{
    GameMapManager::getInstance()->loadDownMap();
}

void GameScene::mapTravelRight(Ref* pSender)
{
    GameMapManager::getInstance()->loadRightMap();
}

void GameScene::mapTravelLeft(Ref* pSender)
{
    GameMapManager::getInstance()->loadLeftMap();
}

void GameScene::goNextLevel(Ref* pSender)
{

}
