#ifndef __CLEAVER_H__
#define __CLEAVER_H__

#include "BaseWeapon.h"
#include "CleaverProjectile.h"

class Cleaver : public BaseWeapon {
protected:
    Cleaver() : BaseWeapon("cleaver") {}
    virtual ~Cleaver() {}
    
public:
    CREATE_FUNC(Cleaver);
    
    bool init() final {
        IF(!BaseWeapon::init());
        setLevelValue(1, 1, 0.2f, 0.1f);
        setLevelValue(2, 1, 0.2f, 0.1f);
        setLevelValue(3, 1, 0.2f, 0.1f);
        return true;
    }
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto Cleaver = CleaverProjectile::create();

		if (!Cleaver) return;
		addBullet(Cleaver, direction);
		Cleaver->setParent(this);
		Cleaver->setSpeed(20.0f);
		Cleaver->setVelocity(direction);
		Cleaver->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		Cleaver->PhysicsObject::scale(0.5f);
		Cleaver->move();
		Cleaver->setInitialPos();
		Cleaver->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __CLEAVER_H__ */
