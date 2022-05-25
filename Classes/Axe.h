#ifndef __AXE_H__
#define __AXE_H__

#include "BaseWeapon.h"


class Axe : public BaseWeapon {
protected:
    Axe() : BaseWeapon("axe") {}
    virtual ~Axe() {}
    
public:
    CREATE_FUNC(Axe);
    
//    void attack() final {
//        
//    }
};

#endif /* __AXE_H__ */
