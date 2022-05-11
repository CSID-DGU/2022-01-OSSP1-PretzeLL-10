#ifndef __BIG_DEMON_H__
#define __BIG_DEMON_H__

#include "BaseMonster.h"


class BigDemon : public BaseMonster {
public:
    BigDemon() : BaseMonster("big_demon") {}
    ~BigDemon() {}
    
    CREATE_FUNC(BigDemon);
    
    void attack() override {}
};

#endif /* __BIGDEMON_H__ */
