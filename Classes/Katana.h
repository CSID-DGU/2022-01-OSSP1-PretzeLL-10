#ifndef __KATANA_H__
#define __KATANA_H__

#include "BaseWeapon.h"
#include "KatanaProjectile.h"

class Katana : public BaseWeapon {
protected:
    Katana() : BaseWeapon("katana") {}
    virtual ~Katana() {}
    
public:
    CREATE_FUNC(Katana);
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto Katana = KatanaProjectile::create();

		if (!Katana) return;
		addBullet(Katana);
		Katana->setParent(this);
		Katana->setSpeed(20.0f);
		Katana->setVelocity(direction);
		Katana->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		Katana->PhysicsObject::scale(0.5f);
		Katana->move();
		Katana->setInitialPos();
		Katana->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __KATANA_H__ */
