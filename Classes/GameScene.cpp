/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
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
        CC_CALLBACK_1(GameScene::menuCloseCallback, this));

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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

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

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("sprite/backgroundMenu.png");
    if (sprite == nullptr)
    {
        problemLoading("'sprite/backgroundMenu.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    
    
    auto tmap = TMXTiledMap::create("tmx/samplemap.tmx");
    if (tmap == nullptr)
    {
        problemLoading("'tmx/samplemap.tmx'");
    }
    else
    {
        // add the sprite as a child to this layer
        this->addChild(tmap, 0, 11);
    }

    auto timer = _Timer::create();
    this->addChild(timer);
        

// ================================================================================================================================== //
    
    auto __e_d = cocos2d::Director::getInstance()->getEventDispatcher();
    auto __l_k = cocos2d::EventListenerKeyboard::create();
    __l_k->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    __l_k->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    __e_d->addEventListenerWithSceneGraphPriority(__l_k, this);
    
    auto __g = b2Vec2(0.0f, -98.0f);
    __world = new b2World(__g);
    __world->SetAllowSleeping(true);
    __world->SetContinuousPhysics(true);
    PhysicsObject::setWorld(__world);
#if COCOS2D_DEBUG > 0
    auto __d_l = B2DebugDrawLayer::create(__world);
    addChild(__d_l);
#endif
    scheduleUpdate();
    
    
    b2BodyDef __b_f;
    __b_f.position.Set(0.0f, 0.0f);
    auto __b = __world->CreateBody(&__b_f);
    
    auto __s = cocos2d::Director::getInstance()->getWinSize()/PTM_RATIO;
    __s.width *= 0.85f;
    __s.height *= 0.7f;
    b2EdgeShape __e;
    b2FixtureDef __f;
    __f.shape = &__e;
    __e.Set(b2Vec2(0, 0), b2Vec2(__s.width, 0));
    __b->CreateFixture(&__f);
    __e.Set(b2Vec2(0, 0), b2Vec2(0, __s.height));
    __b->CreateFixture(&__f);
    __e.Set(b2Vec2(0, __s.height), b2Vec2(__s.width, __s.height));
    __b->CreateFixture(&__f);
    __e.Set(b2Vec2(__s.width, __s.height), b2Vec2(__s.width, 0));
    __b->CreateFixture(&__f);
    __b->SetTransform(b2Vec2(1.45f, 1.5f), 0.0f);

    
    __player = Hero::create();
    IF(!__player);
    __player->setInput(NULL, __key.data());
    
    __player->setAbsolutePosition(500, 500);
    __player->retain();
    addChild(__player);
    
    auto __bigDemon = BigDemon::create();
    IF(!__bigDemon);
    __bigDemon->setAbsolutePosition(200, 400);
    __bigDemon->retain();
    addChild(__bigDemon);
    
    auto __goblin = Goblin::create();
    IF(!__goblin);
    __goblin->setAbsolutePosition(800, 600);
    __goblin->retain();
    addChild(__goblin);

    auto __bigZombie = BigZombie::create();
    IF(!__bigZombie);
    __bigZombie->setAbsolutePosition(700, 300);
    addChild(__bigZombie);
    
    __slot_layer = SlotMachine::create();
    IF(!__slot_layer);
    __slot_layer->setScale(0.5f);
    __slot_layer->setAnchorPoint(cocos2d::Vec2(1.0f, 0.5f));
    addChild(__slot_layer);

    return true;
}


void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
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
            __slot_layer->react(__player);
            break;
        case keyCode_t::KEY_1: __player->changeWeapon(1); break;
        case keyCode_t::KEY_2: __player->changeWeapon(2); break;
        case keyCode_t::KEY_3: __player->changeWeapon(3); break;
        case keyCode_t::KEY_ESCAPE: endProgram();
        default: break;
    }
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
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


void GameScene::update(float dt) {
    __world->Step(dt, 8, 3);
}

GameScene::GameScene() {
    __key.fill(false);
    __slot_layer = nullptr;
}

GameScene::~GameScene() {
    //delete __world;
}

// ================================================================================================================================== //


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
