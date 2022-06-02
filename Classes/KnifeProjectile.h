#ifndef __KNIFE_PROJECTILE_H__
#define __KNIFE_PROJECTILE_H__

#include "BaseBullet.h"


class KnifeProjectile : public BaseBullet {
protected:
    cocos2d::Vec2 __initial_pos;
    float __desired_distance = 300.0f;
    
protected:
    KnifeProjectile() : BaseBullet("weapon_regular_sword") {}
    virtual ~KnifeProjectile() {}
    
public:
    CREATE_FUNC(KnifeProjectile);
    
    void update(float dt) final {
        ProjectileObject::update(dt);
                
        if (!__desired_distance) return;
        float len = length(getPosition() - __initial_pos);
        if (len > __desired_distance) {
//            removeAfter(0.0);
//            unscheduleUpdate();
            
            /* Revert direction */
            __desired_distance = 0.0f;
            auto v = getVelocity();
            v.x *= -1;
            v.y *= -1;
            setVelocity(v);
            move();
            /* ================ */
        }
    }
    
    void setInitialPos() {
        __initial_pos = getPosition();
    }
    
    void onContact(b2Contact* contact) final {
        /* For rotation on end */
        auto diff = getPosition() - __initial_pos;
        Node::setRotation(VecToDegree(diff));
        /* =================== */
        
        __desired_distance = 0.0f;
        setCategory(CATEGORY_BULLET, MASK_NONE);
        removeAfter(3.0);

        auto delay = cocos2d::DelayTime::create(2.0f);
        auto fadeOut = cocos2d::FadeOut::create(1.0f);
        auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
        runAction(sequence);
    }
};

#endif /* __KNIFE_PROJECTILE_H__ */
