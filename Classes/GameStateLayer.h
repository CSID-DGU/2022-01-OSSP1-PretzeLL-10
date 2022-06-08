#ifndef __GAMESTATE_LAYER_H__
#define __GAMESTATE_LAYER_H__

#include "cocos2d.h"
#include "Object.h"

class GameStateLayer : public cocos2d::Layer
{
private:
	Hero* _player;
    std::pair<Coin*, int> _coin;
	std::pair<cocos2d::Sprite*, int> _heroHP;
    
public:
	virtual bool init();
	virtual void update(float delta) override;

	void startNewGame(Hero* hero);

	void updateHeroHP();
	void showHeroHP();
	CREATE_FUNC(GameStateLayer);
};

#endif // __GAMESTATE_LAYER_H__
