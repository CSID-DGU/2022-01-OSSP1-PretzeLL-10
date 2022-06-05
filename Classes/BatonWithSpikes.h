#ifndef __BATON_WITH_SPIKES_H__
#define __BATON_WITH_SPIKES_H__

#include "BaseWeapon.h"
#include "BatonWithSpikesProjectile.h"

class BatonWithSpikes : public BaseWeapon {
protected:
    BatonWithSpikes() : BaseWeapon("baton_with_spikes", 1, 0.2f, 0.1f) {}
    virtual ~BatonWithSpikes() {}
    
public:
    CREATE_FUNC(BatonWithSpikes);
    
	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto BatonWithSpikes = BatonWithSpikesProjectile::create();

		if (!BatonWithSpikes) return;
		addBullet(BatonWithSpikes);
		BatonWithSpikes->setParent(this);
		BatonWithSpikes->setSpeed(20.0f);
		BatonWithSpikes->setVelocity(direction);
		BatonWithSpikes->setAngularVelocity(C2B(90.0f) * (flipped ? -1 : 1));
		BatonWithSpikes->PhysicsObject::scale(0.5f);
		BatonWithSpikes->move();
		BatonWithSpikes->setInitialPos();
		BatonWithSpikes->getHeroPtr();

		float angle = 30.0f;
		if (flipped) angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}

};

#endif /* __BATON_WITH_SPIKES_H__ */
