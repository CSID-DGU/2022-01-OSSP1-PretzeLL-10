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

#include "StartingMenuScene.h"
#include "GameScene.h"
#include "MenuSettingScene.h"
#include "SimpleAudioEngine.h"

#include "Utility.h"
#include "SlotMachine.h"

USING_NS_CC;

Scene* StartingMenu::createScene()
{
	return StartingMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartingMenu::init()
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
	// 2. add menu Item
	auto closeItem = MenuItemFont::create("EXIT", CC_CALLBACK_1(StartingMenu::menuCloseCallback, this));
	auto playItem = MenuItemFont::create("PLAY", CC_CALLBACK_1(StartingMenu::menuPlayCallback, this));
	auto settingItem = MenuItemFont::create("SETTING", CC_CALLBACK_1(StartingMenu::menuSettingCallback, this));

	// create menu, it's an autorelease object
	auto menu = Menu::create(playItem, settingItem, closeItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	this->addChild(menu, 1);

	/////////////////////////////
	// 3.
	auto titleSprite = Sprite::create("frames/MoiraiLabel.png");
	if (titleSprite == nullptr)
	{
		problemLoading("'MoiraiLabel fault'");
	}
	else
	{
		// position the label on the center of the screen
		titleSprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - titleSprite->getContentSize().height - 200));

		titleSprite->setScale(3.0f);
		titleSprite->getTexture()->setTexParameters(TEX_PARA);
		// add the label as a child to this layer
		this->addChild(titleSprite, 2);
	}

	auto logoSprite = Sprite::create("frames/MoiraiLogo.png");
	if (logoSprite == nullptr)
	{
		problemLoading("'Moirailogo fault'");
	}
	else
	{
		// position the label on the center of the screen
		logoSprite->setPosition(Vec2(origin.x + visibleSize.width / 2 + 350,
			origin.y + visibleSize.height - logoSprite->getContentSize().height - 75));

		logoSprite->setScale(1.5f);
		logoSprite->getTexture()->setTexParameters(TEX_PARA);
		// add the label as a child to this layer
		this->addChild(logoSprite, 1);
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

	//auto timer = _Timer::create();
	//this->addChild(timer);

	return true;
}


void StartingMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void StartingMenu::menuPlayCallback(Ref* pSender)
{
	const auto scene = GameScene::createScene();
	IF_RV(!scene, "Failed to create scene");
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void StartingMenu::menuSettingCallback(Ref* pSender)
{
	const auto scene = MenuSetting::create();
	IF_RV(!scene, "Failed to create scene");
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}
