#ifndef __BIG_HAMMER_H__
#define __BIG_HAMMER_H__

#include "BaseWeapon.h"
#include "BigHammerProjectile.h"

class BigHammer : public BaseWeapon {
protected:
    BigHammer() : BaseWeapon("big_hammer") {}
    virtual ~BigHammer() {}
    
public:
    CREATE_FUNC(BigHammer);
    
    bool init() final {
        IF(!BaseWeapon::init());
        setLevelValue(1, 1, 0.2f, 0.1f);
        return true;
    }
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto BigHammer = BigHammerProjectile::create();

		if (!BigHammer) return;
		addBullet(BigHammer, direction);
		BigHammer->setParent(this);
		BigHammer->setSpeed(20.0f);
		BigHammer->setVelocity(direction);
		BigHammer->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		BigHammer->PhysicsObject::scale(0.5f);
		BigHammer->move();
		BigHammer->setInitialPos();
		BigHammer->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}

};

#endif /* __BIG_HAMMER_H__ */

