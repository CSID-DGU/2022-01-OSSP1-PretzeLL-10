#ifndef __AxeProjectile_H__
#define __AxeProjectile_H__

//#include "utility.h"
#include "BaseBullet.h"

class AxeProjectile : public BaseBullet {
protected:
	cocos2d::Vec2 __initial_pos;
	float __desired_distance = 500.0f;

	AxeProjectile() : BaseBullet("weapon_AxeProjectile") {}
	virtual ~AxeProjectile() {}

public:
	CREATE_FUNC(AxeProjectile);
	cocos2d::Vec2 tmp_velocity;

	bool init() final {
		if (!BaseBullet::init());
		__body->SetLinearDamping(0.25f);
		return true;
	}

	void update(float dt) final {
		ProjectileObject::update(dt);

		if (!__desired_distance) return;

		auto hero = getParent()->getChildByTag < DynamicObject* >(TAG_PLAYER);
		float len1 = length(getPosition() - __initial_pos);
		float len2 = length(getPosition() - hero->getPosition());

		if (len1 > __desired_distance) {
			tmp_velocity = cocos2d::Vec2(hero->getPosition().x-getPosition().x, hero->getPosition().y-getPosition().y) / PTM_RATIO;
			normalize(tmp_velocity);
			setVelocity(C2B(tmp_velocity));
			move();
		}

		if (len2 < 10.0f) {
			removeAfter(0.0f);
			unscheduleUpdate();
		}
	}

	void setInitialPos() {
		__initial_pos = getPosition();
	}

	void onContact(b2Contact* contact) final {
		__desired_distance = 0.0f;
		setCategory(CATEGORY_BULLET, MASK_NONE);
		removeAfter(3.0);

		auto delay = cocos2d::DelayTime::create(2.0f);
		auto fadeOut = cocos2d::FadeOut::create(1.0f);
		auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
		runAction(sequence);
	}
};

#endif /* __AxeProjectile_H__ */