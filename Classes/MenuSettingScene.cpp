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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    cocos2d::Label* label[3];
    label[0] = cocos2d::Label::createWithTTF("resolution", "fonts/Marker Felt.ttf", 300);
    label[1] = cocos2d::Label::createWithTTF("background music", "fonts/Marker Felt.ttf", 300);
    label[2] = cocos2d::Label::createWithTTF("back", "fonts/Marker Felt.ttf", 300);
    auto resolution = MenuItemLabel::create(label[0], CC_CALLBACK_1(MenuSetting::setDisplayResolution, this));
    auto bgm = MenuItemLabel::create(label[1], CC_CALLBACK_1(MenuSetting::setBackgroundMusic, this));
    auto backItem = MenuItemLabel::create(label[2], CC_CALLBACK_1(MenuSetting::menuGoMenuCallback, this));

    // create menu, it's an autorelease object
    auto menu = Menu::create(resolution, bgm, backItem, NULL);
    menu->alignItemsVertically();
//    menu->setPosition(Vec2(visibleSize.width, visibleSize.height)/2);
    menu->setScale(0.2f);
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

void MenuSetting::setDisplayResolution(Ref* pSender)
{
    cocos2d::Label* label[2];
    label[0] = cocos2d::Label::createWithTTF("800x600", "fonts/Marker Felt.ttf", 300);
    label[1] = cocos2d::Label::createWithTTF("1280x960", "fonts/Marker Felt.ttf", 300);
    auto small = cocos2d::MenuItemLabel::create(label[0], [&](Ref* s){
        GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
        view->setWindowed(800, 600);
    });
    auto middle = cocos2d::MenuItemLabel::create(label[1], [&](Ref* s){
        GLViewImpl* view = (GLViewImpl*)Director::getInstance()->getOpenGLView();
        view->setWindowed(1280, 960);
    });
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto menu = Menu::create(small, middle, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    menu->setScale(0.2f);
    addChild(menu, 1);
}

void MenuSetting::setBackgroundMusic(Ref* pSender)
{
    
}

void MenuSetting::menuGoMenuCallback(Ref* pSender)
{
    const auto scene = StartingMenu::create();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}
