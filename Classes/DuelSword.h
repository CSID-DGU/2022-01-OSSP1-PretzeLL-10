#ifndef __DEUL_SWORD_H__
#define __DEUL_SWORD_H__

#include "BaseWeapon.h"


class DuelSword : public BaseWeapon {
protected:
    DuelSword() : BaseWeapon("duel_sword") {}
    virtual ~DuelSword() {}
    
public:
    CREATE_FUNC(DuelSword);
    
//    void attack() final {
//        
//    }
};

#endif /* __DEUL_SWORD_H__ */

