#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "BaseWeapon.h"
#include "KnifeProjectile.h"


class Knife : public BaseWeapon {
protected:
    Knife() : BaseWeapon("regular_sword", 1, 0.2f, 0.1f) {}
    virtual ~Knife() {}
    
public:
    CREATE_FUNC(Knife);
    
    void attack(bool flipped, const b2Vec2& direction) final {
        if (!isAttackAble()) return;
        
        auto knife = KnifeProjectile::create();
        if (!knife) return;
        addBullet(knife);
        knife->setParent(this);
        knife->setSpeed(30.0f);
        knife->setVelocity(direction);                                              // Now rotation is automatically set (in move func)
        knife->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));                 // set angular velocity to rotate, rotates degree per second
        knife->PhysicsObject::scale(0.5);
        knife->move();
        knife->setInitialPos();
        
        float angle = -30.0f;
        if (flipped) angle *= -1;
        auto up = cocos2d::RotateBy::create(0.0f, angle);
        auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
        auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
        auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
        runAction(seq);
        
    }
};

#endif /* __KNIFE_H__ */

