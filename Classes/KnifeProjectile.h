#ifndef __KNIFE_PROJECTILE_H__
#define __KNIFE_PROJECTILE_H__

#include "BaseBullet.h"


class KnifeProjectile : public BaseBullet {
protected:
    cocos2d::Node* __target;
    cocos2d::Vec2 __initial_pos;
    float __desired_distance = 500.0f;
        
protected:
    KnifeProjectile() : BaseBullet("weapon_regular_sword") {}
    virtual ~KnifeProjectile() {}
    
public:
    CREATE_FUNC(KnifeProjectile);
    
    void setTarget(cocos2d::Node* target) {
        __target = target;
        schedule(schedule_selector(KnifeProjectile::followTarget));
    }
    
    void onContact(b2Contact* contact) final {
        setCategory(CATEGORY_BULLET, MASK_NONE);
        unschedule(schedule_selector(KnifeProjectile::followTarget));
        stop(std::numeric_limits<float>::max());
        auto delay = cocos2d::DelayTime::create(1.0f);
        auto fadeOut = cocos2d::FadeOut::create(0.5f);
        auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
        runAction(sequence);
    }
    
    void followTarget(float dt) {\
        if (!__target) {
            removeAfter(3.0f);
            unschedule(schedule_selector(KnifeProjectile::followTarget));
            auto delay = cocos2d::DelayTime::create(1.0f);
            auto fadeOut = cocos2d::FadeOut::create(0.5f);
            auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
            runAction(sequence);
            return;
        }
        if (__target->getTag() != TAG_MONSTER) {
            __target = nullptr;
            return;
        }
        
        auto target_pos = __target->getPosition();
        moveTo(target_pos);
        setRotation(VecToDegree(target_pos - getPosition()));
        __body->SetAngularVelocity(__angular_velocity*10.0f);
    }
};

#endif /* __KNIFE_PROJECTILE_H__ */
