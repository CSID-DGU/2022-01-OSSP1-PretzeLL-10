#ifndef __KNIFE_H__
#define __KNIFE_H__

#include "BaseWeapon.h"
#include "KnifeProjectile.h"


class Knife : public BaseWeapon {
protected:
    Knife() : BaseWeapon("regular_sword", 1, 0.1f, 0.0f, 0.2f) {}
    virtual ~Knife() {}
    
public:
    CREATE_FUNC(Knife);
    
    void attack(bool flipped, const b2Vec2& direction) final {
        if (!isAttackAble()) return;
        
        auto knife = KnifeProjectile::create();
        if (!knife) return;
        addBullet(knife);
        knife->setParent(this);
        knife->setSpeed(60.0f);
        knife->setRotation(VecToDegree(direction));
        knife->setVelocity(direction);
        knife->PhysicsObject::scale(0.5);
        knife->move();
        knife->setInitialPos();
    }
};

#endif /* __KNIFE_H__ */

