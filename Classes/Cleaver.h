#ifndef __CLEAVER_H__
#define __CLEAVER_H__

#include "BaseWeapon.h"


class Cleaver : public BaseWeapon {
protected:
    Cleaver() : BaseWeapon("cleaver") {}
    virtual ~Cleaver() {}
    
public:
    CREATE_FUNC(Cleaver);
    
//    void attack() final {
//        
//    }
};

#endif /* __CLEAVER_H__ */
