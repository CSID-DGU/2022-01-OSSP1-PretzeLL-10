#ifndef __ANIME_SWORD_H__
#define __ANIME_SWORD_H__

#include "BaseWeapon.h"


class AnimeSword : public BaseWeapon {
protected:
    AnimeSword() : BaseWeapon("anime_sword") {}
    virtual ~AnimeSword() {}
    
public:
    CREATE_FUNC(AnimeSword);
    
//    void attack() final {
//
//    }
};

#endif /* __ANIME_SWORD_H__ */
