#ifndef __BIG_ZOMBIE_H__
#define __BIG_ZOMBIE_H__

#include "BaseMonster.h"


class BigZombie : public BaseMonster {
public:
    BigZombie() : BaseMonster("big_zombie") {}
    ~BigZombie() {}
    
    CREATE_FUNC(BigZombie);
    
    void attack() final {}
};

#endif /* __BIG_ZOMBIE_H__ */
