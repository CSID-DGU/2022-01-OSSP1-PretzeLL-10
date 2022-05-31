#ifndef __KNIFE_PROJECTILE_H__
#define __KNIFE_PROJECTILE_H__

#include "BaseBullet.h"


class KnifeProjectile : public BaseBullet {
protected:
    cocos2d::Vec2 __initial_pos;
    const float __desired_distance = 500.0f;
    
protected:
    KnifeProjectile() : BaseBullet("weapon_regular_sword") {}
    virtual ~KnifeProjectile() {}
    
public:
    CREATE_FUNC(KnifeProjectile);
    
    void update(float dt) final {
        ProjectileObject::update(dt);
        
        float len = length(getPosition() - __initial_pos);
        if (len > __desired_distance) {
            setCategory(CATEGORY_BULLET, MASK_NONE);
            removeAfter(0.0);
            unscheduleUpdate();
        }
    }
    
    void setInitialPos() {
        __initial_pos = getPosition();
    }
};

#endif /* __KNIFE_PROJECTILE_H__ */
