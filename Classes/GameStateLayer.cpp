#include "GameStateLayer.h"

void GameStateLayer::startNewGame(Hero* hero)
{
	_player = hero;
	// hp
	_heroHP.second = _player->getHP();
	showHeroHP();

	// 임시로 여기서 SlotMachine create
	auto _slot = SlotMachine::create();
//	_slot->react(_player);
	addChild(_slot);
    setName("state_layer");
}

bool GameStateLayer::init()
{
	if (!Layer::create())
		return false;

	_heroHP = std::make_pair(cocos2d::Sprite::create(), 0 );
	_heroHP.first->setTextureRect(cocos2d::Rect(0, 0, 240, 50));
	_heroHP.first->setPosition(cocos2d::Vec2(500, 200));
    _heroHP.first->setOpacity(0.0f);
	addChild(_heroHP.first);
	scheduleUpdate();
    
    _coin.first = Coin::create();
    _coin.first->setPosition(750.0f, 200.0f);
    _coin.second = 0;
    addChild(_coin.first);
    
	return true;
}

void GameStateLayer::update(float delta)
{
	updateHeroHP();
}

//==================================================================================
//						Show State of Hero
//==================================================================================

void GameStateLayer::updateHeroHP()
{
	if (_heroHP.second != _player->getHP())
	{
		_heroHP.second = _player->getHP();
		showHeroHP();
	}
    if (_coin.second != _player->getCoin()) {
        _coin.second = _player->getCoin();
        _coin.first->updateLabel(_player->getCoin());
    }
}

void GameStateLayer::showHeroHP()
{
	int i = 0;
	_heroHP.first->removeAllChildren();
	const int full = _heroHP.second / 2;
	const int half = _heroHP.second % 2;
	for (i = 0; i < full; i++)
	{
		auto heart = cocos2d::Sprite::create("frames/ui_heart_full.png");
		heart->setPosition(50*i + 110, 25);
		_heroHP.first->addChild(heart);
	}
	if (half == 1)
	{
		auto heart = cocos2d::Sprite::create("frames/ui_heart_half.png");
		heart->setPosition(50 * i + 110, 25);
		_heroHP.first->addChild(heart);
	}
}
