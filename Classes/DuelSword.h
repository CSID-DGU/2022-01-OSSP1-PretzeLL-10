#ifndef __DUEL_SWORD_H__
#define __DUEL_SWORD_H__

#include "BaseWeapon.h"
#include "DuelSwordProjectile.h"

class DuelSword : public BaseWeapon {
protected:
    DuelSword() : BaseWeapon("duel_sword") {}
    virtual ~DuelSword() {}
    
public:
    CREATE_FUNC(DuelSword);
    
    bool init() final {
        IF(!BaseWeapon::init());
        setLevelValue(1, 1, 0.2f, 0.1f);
        setLevelValue(2, 1, 0.2f, 0.1f);
        setLevelValue(3, 1, 0.2f, 0.1f);
        return true;
    }
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto DuelSword = DuelSwordProjectile::create();

		if (!DuelSword) return;
		addBullet(DuelSword, direction);
		DuelSword->setParent(this);
		DuelSword->setSpeed(20.0f);
		DuelSword->setVelocity(direction);
		DuelSword->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		DuelSword->PhysicsObject::scale(0.5f);
		DuelSword->move();
		DuelSword->setInitialPos();
		DuelSword->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __DUEL_SWORD_H__ */

