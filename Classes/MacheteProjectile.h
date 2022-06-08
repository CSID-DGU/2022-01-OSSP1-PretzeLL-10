#ifndef __MACHETE_PROJECTILE_H__
#define __MACHETE_PROJECTILE_H__

#include "BaseBullet.h"

class MacheteProjectile : public BaseBullet {
protected:
	cocos2d::Node* __hero;
	cocos2d::Vec2 __initial_pos;
	float __desired_distance = 250.0f;

	MacheteProjectile() : BaseBullet("weapon_machete") {}
	virtual ~MacheteProjectile() {}

public:
	CREATE_FUNC(MacheteProjectile);
	cocos2d::Vec2 tmp_velocity;

	void update(float dt) final {
		ProjectileObject::update(dt);

		if (!__desired_distance) return;

		float len = length(getPosition() - __initial_pos);

		auto v = getVelocity();                                             // revert direction
		v.y -= 0.066f;
		setVelocity(v);                                                     // apply reverted direction

		moveGently();

		if (len > __desired_distance) {
			/* Remove Example */
//            removeAfter(0.0);
//            unscheduleUpdate();
			/* ================ */

			/* Revert Example */
//            __desired_distance = 0.0f;
//            auto v = getVelocity();                                             // revert direction
//            v.x *= -1;
//            v.y *= -1;
//            setVelocity(v);                                                     // apply reverted direction
//            move();                                                             // move to apply force
			/* ================ */

			/* Follow Hero */
			__desired_distance = 0.0f;											  // move desired distance   
			schedule(schedule_selector(MacheteProjectile::followTarget));         // schedule follow function
		}
	}

	void setInitialPos() {
		__initial_pos = getPosition();
	}

	void getHeroPtr() {
		__hero = getParent()->getChildByTag(TAG_PLAYER);
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

	void followTarget(float dt) {
		if (!__hero) return;
		
		auto len = moveToGently(__hero->getPosition());                                   // move to hero, returns length(float)
		if (len < 20.0f) {
			unschedule(schedule_selector(MacheteProjectile::followTarget));           // if length is close enough, remove this
			removeAfter(0.0f);
		}
	}
};

#endif /* __MACHETE_PROJECTILE_H__ */