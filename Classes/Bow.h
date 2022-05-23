#ifndef __BOW_H__
#define __BOW_H__

#include "BaseWeapon.h"


class Bow : public BaseWeapon {
protected:
    Bow() : BaseWeapon("bow", 0.1f, 0.0f, 0.5f) {}
    virtual ~Bow() {}
    
public:
    CREATE_FUNC(Bow);
    
//    void attack() final {
//
//    }
};

#endif /* __BOW_H__ */
