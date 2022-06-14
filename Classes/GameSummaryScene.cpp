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

	/***********************************************************************************/
	cocos2d::Sprite* menu_sprite[3][2];
	menu_sprite[0][0] = cocos2d::Sprite::create("frames/PlayNonClick.png");
	menu_sprite[0][1] = cocos2d::Sprite::create("frames/PlayOnClick.png");
	menu_sprite[1][0] = cocos2d::Sprite::create("frames/ExitNonClick.png");
	menu_sprite[1][1] = cocos2d::Sprite::create("frames/ExitOnClick.png");

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			menu_sprite[i][j]->setScale(0.75f);
			menu_sprite[i][j]->getTexture()->setTexParameters(TEX_PARA);
		}
	}

	auto playItem = MenuItemSprite::create(menu_sprite[0][0], menu_sprite[0][1], CC_CALLBACK_1(GameSummary::menuPlayCallback, this));
	auto closeItem = MenuItemSprite::create(menu_sprite[1][0], menu_sprite[1][1], CC_CALLBACK_1(GameSummary::menuGotoStartingMenuCallback, this));
	/***********************************************************************************/

	// create menu, it's an autorelease object
	auto menu = Menu::create(playItem, closeItem, NULL);
	menu->setScale(0.8f);
	menu->alignItemsVerticallyWithPadding(-30.0f);
	menu->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 - 375));
	this->addChild(menu, 2);

	std::string time_str = _Timer::getTimeStringFormat("%02d : %02d", int(GameManager::getInstance()->runningInfo.run_time / 60), int(GameManager::getInstance()->runningInfo.run_time) % 60);
	std::string damage_str = std::to_string(GameManager::getInstance()->runningInfo.damage);	
	std::string stage_str;
	if (GameManager::getInstance()->runningInfo.all_clear == true)
	{
		stage_str = "All Clear!";
	}
	else
	{
		stage_str = std::to_string(GameManager::getInstance()->runningInfo.stage);
	}
	std::string gold_str = std::to_string(GameManager::getInstance()->runningInfo.gold_earn);

	auto time_label = Label::createWithTTF("play time : " + time_str, "fonts/Marker Felt.ttf", 300);
	auto damage_label = Label::createWithTTF("total damage : " + damage_str, "fonts/Marker Felt.ttf", 300);
	auto stage_label = Label::createWithTTF("stage level : " + stage_str, "fonts/Marker Felt.ttf", 300);
	auto gold_label = Label::createWithTTF("tatol gold : " + gold_str, "fonts/Marker Felt.ttf", 300);

	auto backGroundSprite = Sprite::create("frames/Summary_Scene.png");
	if (backGroundSprite == nullptr)
	{
		problemLoading("'Summary_Scene fault'");
	}
	else
	{
		// position the label on the center of the screen
		backGroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - backGroundSprite->getContentSize().height));

		backGroundSprite->setScale(1.8f);
		backGroundSprite->getTexture()->setTexParameters(TEX_PARA);
		// add the label as a child to this layer
		this->addChild(backGroundSprite, 1);
	}

	// add child time_label
	time_label->setScale(0.1f);
	if (time_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		time_label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45,
			origin.y + visibleSize.height - time_label->getContentSize().height * time_label->getScale() - 330));

		// add the label as a child to this layer
		this->addChild(time_label, 1);
	}

	// add child damage_label
	damage_label->setScale(0.1f);
	if (damage_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		damage_label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45,
			origin.y + visibleSize.height - damage_label->getContentSize().height * time_label->getScale() - 435));

		// add the label as a child to this layer
		this->addChild(damage_label, 1);
	}

	// add child stage_label
	stage_label->setScale(0.1f);
	if (stage_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		stage_label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45,
			origin.y + visibleSize.height - stage_label->getContentSize().height * time_label->getScale() - 545));

		// add the label as a child to this layer
		this->addChild(stage_label, 1);
	}

	// add child gold_label
	gold_label->setScale(0.1f);
	if (gold_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		gold_label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45,
			origin.y + visibleSize.height - gold_label->getContentSize().height * time_label->getScale() - 638));

		// add the label as a child to this layer
		this->addChild(gold_label, 1);
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

void GameSummary::menuPlayCallback(Ref* pSender)
{
	const auto scene = GameScene::createScene();
	IF_RV(!scene, "Failed to create scene");
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void GameSummary::menuSettingCallback(Ref* pSender)
{
	const auto scene = MenuSetting::create();
	IF_RV(!scene, "Failed to create scene");
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}
