#ifndef __BOW_H__
#define __BOW_H__

#include "BaseWeapon.h"
#include "Arrow.h"


class Bow : public BaseWeapon {    
protected:
    Bow() : BaseWeapon("bow") {}
    virtual ~Bow() {}
    
public:
    CREATE_FUNC(Bow);
    
    bool init() final {
        IF(!BaseWeapon::init());
        setLevelValue(1, 70, 0.2f, 0.7f);
        setLevelValue(2, 100, 0.2f, 0.5f);
        setLevelValue(3, 120, 0.2f, 0.5f);
        return true;
    }
    
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
