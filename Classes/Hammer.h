#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "BaseWeapon.h"


class Hammer : public BaseWeapon {
protected:
    Hammer() : BaseWeapon("hammer") {}
    virtual ~Hammer() {}
    
public:
    CREATE_FUNC(Hammer);
    
//    void attack() final {
//        
//    }
};

#endif /* __HAMMER_H__ */

