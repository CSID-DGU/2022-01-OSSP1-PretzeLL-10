#ifndef __HAMMER_H__
#define __HAMMER_H__

#include "BaseWeapon.h"
#include "HammerProjectile.h"

class Hammer : public BaseWeapon {
protected:
    Hammer() : BaseWeapon("hammer") {}
    virtual ~Hammer() {}
    
public:
    CREATE_FUNC(Hammer);
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto Hammer = HammerProjectile::create();

		if (!Hammer) return;
		addBullet(Hammer, direction);
		Hammer->setParent(this);
		Hammer->setSpeed(20.0f);
		Hammer->setVelocity(direction);
		Hammer->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		Hammer->PhysicsObject::scale(0.5f);
		Hammer->move();
		Hammer->setInitialPos();
		Hammer->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __HAMMER_H__ */

