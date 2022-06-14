#ifndef __MENUSETTING_SCENE_H__
#define __MENUSETTING_SCENE_H__

#include "cocos2d.h"

class MenuSetting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setSmallDisp(cocos2d::Ref* pSender);
    void setMiddleDisp(cocos2d::Ref* pSender);
    void menuGoMenuCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(MenuSetting);
};

#endif // __MENUSETTING_SCENE_H__
