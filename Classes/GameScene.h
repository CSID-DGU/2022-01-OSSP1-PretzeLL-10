#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Hero.h"
#include "Monster.h"
#include "SlotMachine.h"
#include "StartingMenuScene.h"


class GameScene : public cocos2d::Scene
{
private:
    b2World* __world;
    SlotMachine* __slot_layer;
    
    Hero* __player;
    std::array<bool, 5> __key;
    
public:
    GameScene();
    virtual ~GameScene();
    
    
    static cocos2d::Scene* createScene();

    bool init() override;
    void update(float dt) override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    void createSlotMachine();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
