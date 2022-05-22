#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMapManager.h"
#include "GameMap.h"

#include "Hero.h"
#include "Monster.h"
#include "SlotMachine.h"
#include "StartingMenuScene.h"


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    void update(float dt) override;

    void startNewGame();
    void goNextStage();

    // a selector callback
    void menuGotoSummarySceneCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    GameMapManager* _gamemapmanager;

    //test
    void mapTravelUp(Ref* pSender);
    void mapTravelDown(Ref* pSender);
    void mapTravelRight(Ref* pSender);
    void mapTravelLeft(Ref* pSender);
    void goNextLevel(Ref* pSender);
};

#endif // __GAME_SCENE_H__
