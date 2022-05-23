#ifndef __BIG_HAMMER_H__
#define __BIG_HAMMER_H__

#include "BaseWeapon.h"


class BigHammer : public BaseWeapon {
protected:
    BigHammer() : BaseWeapon("big_hammer") {}
    virtual ~BigHammer() {}
    
public:
    CREATE_FUNC(BigHammer);
    
//    void attack() final {
//        
//    }
};

#endif /* __BIG_HAMMER_H__ */

