#ifndef __BOW_H__
#define __BOW_H__

#include "BaseWeapon.h"


class Bow : public BaseWeapon {
protected:
    Bow() : BaseWeapon("bow", 0.1f, 0.0f, 0.5f) {}
    virtual ~Bow() {}
    
public:
    CREATE_FUNC(Bow);
    
    void attack(bool flipped, const b2Vec2& direction) final {
        if (!isAttackAble()) return;
        
        auto arrow = Arrow::create();
        if(!arrow) return;
        addBullet(arrow);
        arrow->setSpeed(100.0f);
        arrow->setRotation(VecToDegree(direction));
        arrow->setVelocity(direction);
        arrow->move();
    }
};

#endif /* __BOW_H__ */
