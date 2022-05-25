#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "Utility.h"
#include "Hero.h"


class EventHandler : public cocos2d::Node {
private:
    Hero* _hero;
    
public:
    CREATE_FUNC(EventHandler);
    
    void setup(cocos2d::Layer* layer, Hero* hero);
    
    void onKeyPressed(keyCode_t key, cocos2d::Event* event);
    void onKeyReleased(keyCode_t key, cocos2d::Event* event);
    void onMouseUp(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
};

#endif /* __EVENT_HANDLER_H__ */
