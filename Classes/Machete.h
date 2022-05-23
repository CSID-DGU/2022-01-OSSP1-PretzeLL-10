#ifndef __MACHETE_H__
#define __MACHETE_H__

#include "BaseWeapon.h"


class Machete : public BaseWeapon {
protected:
    Machete() : BaseWeapon("machete") {}
    virtual ~Machete() {}
    
public:
    CREATE_FUNC(Machete);
    
//    void attack() final {
//
//    }
};

#endif /* __MACHETE_H__ */

