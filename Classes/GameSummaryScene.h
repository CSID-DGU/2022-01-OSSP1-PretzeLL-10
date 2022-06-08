#ifndef __GAMESUMMARY_SCENE_H__
#define __GAMESUMMARY_SCENE_H__

#include "cocos2d.h"

class GameSummary : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuGotoStartingMenuCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuSettingCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameSummary);
};

#endif // __GAMESUMMARY_SCENE_H__
