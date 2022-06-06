#ifndef __BOW_H__
#define __BOW_H__

#include "BaseWeapon.h"
#include "Arrow.h"


class Bow : public BaseWeapon {
protected:
//    Bow() : BaseWeapon("bow", 1, 0.1f, 0.0f, 0.5f) {}
    Bow() : BaseWeapon("bow", 1, 0.1f, 0.0f) {}               // testing
    virtual ~Bow() {}
    
public:
    CREATE_FUNC(Bow);
    
    void attack(bool flipped, const b2Vec2& direction) final {
        if (!isAttackAble()) return;
        
        auto arrow = Arrow::create();
        if(!arrow) return;
        addBullet(arrow, direction);
        arrow->setParent(this);
        arrow->setSpeed(25.0f);
        arrow->setRotation(VecToDegree(direction));
        arrow->setVelocity(direction);
        arrow->PhysicsObject::scale(0.5f);
        arrow->move();
    }
};

#endif /* __BOW_H__ */
