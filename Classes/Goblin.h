#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "BaseMonster.h"


class Goblin : public BaseMonster {
public:
    Goblin() : BaseMonster("goblin", 1) {}
    ~Goblin() {}
    
    CREATE_FUNC(Goblin);
    
    bool init() final {
        IF(!BaseMonster::init());
        __body->SetGravityScale(0.004f);
        __body->SetLinearDamping(0.004f);
        __body->SetLinearVelocity(b2Vec2(-3.5f, 0.0f));
        return true;
    }
    void attack() final {}
};

#endif /* __GOBLIN_H__ */
