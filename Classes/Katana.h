#ifndef __KATANA_H__
#define __KATANA_H__

#include "BaseWeapon.h"


class Katana : public BaseWeapon {
protected:
    Katana() : BaseWeapon("katana") {}
    virtual ~Katana() {}
    
public:
    CREATE_FUNC(Katana);
    
//    void attack() final {
//        
//    }
};

#endif /* __KATANA_H__ */
