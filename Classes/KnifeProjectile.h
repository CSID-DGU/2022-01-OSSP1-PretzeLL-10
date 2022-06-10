#ifndef __KNIFE_PROJECTILE_H__
#define __KNIFE_PROJECTILE_H__

#include "BaseBullet.h"


class KnifeProjectile : public BaseBullet {
protected:
    cocos2d::Node* __hero;
    cocos2d::Vec2 __initial_pos;
    float __desired_distance = 500.0f;
        
protected:
    KnifeProjectile() : BaseBullet("weapon_regular_sword") {}
    virtual ~KnifeProjectile() {}
    
public:
    CREATE_FUNC(KnifeProjectile);
    
//    void setTarget(cocos2d::Node* target) {
//        __target = target;
//        schedule(schedule_selector(KnifeProjectile::followTarget));
//    }
    
    void update(float dt) {
        ProjectileObject::update(dt);
        
        if (!__desired_distance) return;
        float len = length(getPosition() - __initial_pos);
        if (len > __desired_distance) {
            /* Remove Example */
            removeAfter(0.0);
            unscheduleUpdate();
            /* ================ */
        }
    }
    
    void setInitialPos() {
        __initial_pos = getPosition();
    }

    void getHeroPtr() {
        __hero = getParent()->getChildByTag(TAG_PLAYER);
    }
    
    void onContact(b2Contact* contact) final {
        __desired_distance = 0.0f;
        setCategory(CATEGORY_BULLET, MASK_NONE);
        removeAfter(3.0);

        auto delay = cocos2d::DelayTime::create(2.0f);
        auto fadeOut = cocos2d::FadeOut::create(1.0f);
        auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
        runAction(sequence);
    }

//    void followTarget(float dt) {
//        if (!__target) {
//            removeAfter(3.0f);
//            unschedule(schedule_selector(KnifeProjectile::followTarget));
//            auto delay = cocos2d::DelayTime::create(1.0f);
//            auto fadeOut = cocos2d::FadeOut::create(0.5f);
//            auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
//            runAction(sequence);
//            return;
//        }
//        if (__target->getTag() != TAG_MONSTER) {
//            __target = nullptr;
//            return;
//        }
//
//        auto target_pos = __target->getPosition();
//        moveTo(target_pos);
//        setRotation(VecToDegree(target_pos - getPosition()));
//        __body->SetAngularVelocity(__angular_velocity*10.0f);
//    }
};

#endif /* __KNIFE_PROJECTILE_H__ */
