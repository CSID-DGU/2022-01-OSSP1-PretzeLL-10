#include "MenuSettingScene.h"
#include "StartingMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuSetting::createScene()
{
    return MenuSetting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuSetting::init()
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
    auto smallDispItem = MenuItemFont::create("800x600", CC_CALLBACK_1(MenuSetting::setSmallDisp, this));
    auto MiddleDispItem = MenuItemFont::create("1280x960", CC_CALLBACK_1(MenuSetting::setMiddleDisp, this));
    auto backItem = MenuItemFont::create("BACK", CC_CALLBACK_1(MenuSetting::menuGoMenuCallback, this));

    // create menu, it's an autorelease object
    auto menu = Menu::create(smallDispItem, MiddleDispItem, backItem, NULL);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(400, 300));
    this->addChild(menu, 1);
    return true;
}


void MenuSetting::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MenuSetting::setSmallDisp(Ref* pSender)
{
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setWindowed(800, 600);
}

void MenuSetting::setMiddleDisp(Ref* pSender)
{
    GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
    view->setWindowed(1280, 960);
}

void MenuSetting::menuGoMenuCallback(Ref* pSender)
{
    const auto scene = StartingMenu::create();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}