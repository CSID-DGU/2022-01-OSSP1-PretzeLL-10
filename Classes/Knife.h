#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "BaseWeapon.h"


class Knife : public BaseWeapon {
protected:
    Knife() : BaseWeapon("knife") {}
    virtual ~Knife() {}
    
public:
    CREATE_FUNC(Knife);
    
//    void attack() final {
//       
//    }
};

#endif /* __KNIFE_H__ */

