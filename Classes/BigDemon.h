#ifndef __BIG_DEMON_H__
#define __BIG_DEMON_H__

#include "BaseMonster.h"


class BigDemon : public BaseMonster {
public:
    BigDemon() : BaseMonster("big_demon") {}
    ~BigDemon() {}
    
    CREATE_FUNC(BigDemon);
    
    bool init() final {
        IF(!BaseMonster::init());
        setHP(10);
        setDamage(1);
        setSpeed(15.0f);
        return true;
    }
    
    void attack() override {}
};

#endif /* __BIGDEMON_H__ */
