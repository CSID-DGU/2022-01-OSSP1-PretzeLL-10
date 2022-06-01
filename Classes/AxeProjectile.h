#ifndef __AxeProjectile_H__
#define __AxeProjectile_H__

#include "BaseBullet.h"



class AxeProjectile : public BaseBullet {
protected:
	cocos2d::Vec2 __initial_pos;
	const float __desired_distance = 500.0f;

	AxeProjectile() : BaseBullet("weapon_AxeProjectile") {}
	virtual ~AxeProjectile() {}

public:
	CREATE_FUNC(AxeProjectile);

	const cocos2d::Vec2 position = getPosition();	
	cocos2d::Vec2 tmp_velocity;

	bool init() final {
		if(!BaseBullet::init());
		PhysicsObject::scale(0.5f);

		__body->SetLinearDamping(1.0f);
		return true;
	}

	void update(float dt) final {
		ProjectileObject::update(dt);
		float len = length(getPosition() - __initial_pos);
		if (len > __desired_distance) {
			//setCategory(CATEGORY_BULLET, MASK_NONE);
			//setRotation(180.0f);			
			tmp_velocity.x = getVelocity().x * -1.0f;
			tmp_velocity.y = getVelocity().y * -1.0f;
			setVelocity(C2B(tmp_velocity));
			move();
		}
		if (len < 1.0f) {
			removeAfter(0.0f);
			unscheduleUpdate();
		}
	}

	void setInitialPos() {
		__initial_pos = getPosition();
	}
};

#endif /* __AxeProjectile_H__ */