#ifndef __COIN_H__
#define __COIN_H__

#include "StaticObject.h"


class Coin : public StaticObject {
private:
    int __coin;
    
protected:
    Coin() : StaticObject("frames", "coin_anim_f0") {}
    virtual ~Coin() {}
    
public:
    CREATE_FUNC(Coin);
    
    bool init() override {
        IF(!StaticObject::init());
        
        SpriteObject::setName("coin");
        addInfAnimation("", 4, 0.1f);
        runActionByKey(IDLE);
        
        return true;
    }
};

#endif /* __COIN_H__ */
