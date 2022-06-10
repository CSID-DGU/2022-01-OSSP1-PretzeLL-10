#include "GameSummaryScene.h"
#include "GameScene.h"
#include "MenuSettingScene.h"
#include "SimpleAudioEngine.h"

#include "Utility.h"
#include "SlotMachine.h"
#include "Timer.h"

USING_NS_CC;

Scene* GameSummary::createScene()
{
    return GameSummary::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameSummary::init()
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
        CC_CALLBACK_1(GameSummary::menuGotoStartingMenuCallback, this));

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
    /*auto closeItem = MenuItemFont::create("EXIT", CC_CALLBACK_1(StartingMenu::menuCloseCallback, this));
    auto playItem = MenuItemFont::create("PLAY", CC_CALLBACK_1(StartingMenu::menuPlayCallback, this));
    auto settingItem = MenuItemFont::create("SETTING", CC_CALLBACK_1(StartingMenu::menuSettingCallback, this));

    auto menu = Menu::create(closeItem, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...
    auto label = Label::createWithTTF(std::to_string(_Timer::getTime()), "fonts/Marker Felt.ttf", 600);
    label->setScale(0.1f);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height) );

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}


void GameSummary::menuGotoStartingMenuCallback(Ref* pSender)
{
    const auto scene = StartingMenu::create();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}
