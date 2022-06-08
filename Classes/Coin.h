#ifndef __COIN_H__
#define __COIN_H__

#include "StaticObject.h"


class Coin : public StaticObject {
private:
    int __coin;
    cocos2d::Label* __label;
    
protected:
    Coin() : StaticObject("frames", "coin_anim_f0") {}
    virtual ~Coin() {}
    
public:
    CREATE_FUNC(Coin);
    
    bool init() override {
        IF(!StaticObject::init());
        
        SpriteObject::setName("coin");
        addInfAnimation("", 4, 0.1f);
        
        __label = cocos2d::Label::createWithTTF("x", PIXEL_FONT, 300);
        __label->setScale(1/15.0f);
        __label->setPosition(30.0f, -5.0f);
        __label->setColor(cocos2d::Color3B(255, 255, 255));
        addChild(__label);
        
        runActionByKey(IDLE);
        scheduleUpdate();
        
        return true;
    }
    
    void updateLabel(int value) {
        if (value > 9) __label->setString("x" + std::to_string(value));
        else __label->setString("x0" + std::to_string(value));
    }
};

#endif /* __COIN_H__ */
