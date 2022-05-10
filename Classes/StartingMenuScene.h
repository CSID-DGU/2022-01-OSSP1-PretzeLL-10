#ifndef __STARTINGMENU_SCENE_H__
#define __STARTINGMENU_SCENE_H__

#include "cocos2d.h"

class StartingMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuSettingCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartingMenu);
};

#endif // __HELLOWORLD_SCENE_H__