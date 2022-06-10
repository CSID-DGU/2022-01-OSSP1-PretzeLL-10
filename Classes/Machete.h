#ifndef __MACHETE_H__
#define __MACHETE_H__

#include "BaseWeapon.h"
#include "MacheteProjectile.h"

class Machete : public BaseWeapon {
protected:
	Machete() : BaseWeapon("machete") {}
	virtual ~Machete() {}

public:
	CREATE_FUNC(Machete);

	bool init() final {
		IF(!BaseWeapon::init());
		setLevelValue(1, 5, 0.2f, 0.1f);
		setLevelValue(2, 10, 0.2f, 0.1f);
		setLevelValue(3, 15, 0.2f, 0.1f);
		return true;
	}

	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto Machete = MacheteProjectile::create();
		cocos2d::Vec2 vec;

		if (!Machete) return;
		addBullet(Machete, direction);
		Machete->setParent(this);
		Machete->setSpeed(3.0f);
		vec = cocos2d::Vec2(direction.x + 0.66f, direction.y + 0.66f);
		Machete->setVelocity(C2B(vec));
		Machete->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		Machete->PhysicsObject::scale(0.5f);
		Machete->moveGently();
		Machete->setInitialPos();
		Machete->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __MACHETE_H__ */

