#ifndef __AXEPROJECTILE_H__
#define __AXEPROJECTILE_H__

//#include "utility.h"
#include "BaseBullet.h"

class AxeProjectile : public BaseBullet
{
protected:
	cocos2d::Vec2 __initial_pos;
	float __desired_distance = 500.0f;

	AxeProjectile() : BaseBullet("weapon_axe") {}
	virtual ~AxeProjectile() {}

public:
	CREATE_FUNC(AxeProjectile);

	const cocos2d::Vec2 position = getPosition();
	cocos2d::Vec2 tmp_velocity;

	bool init() final
	{
		if (!BaseBullet::init())
			;
		PhysicsObject::scale(0.5f);

		__body->SetLinearDamping(1.0f);
		return true;
	}

	void update(float dt) final
	{
		ProjectileObject::update(dt);
		float len = length(getPosition() - __initial_pos);
		if (len > __desired_distance)
		{
			// setCategory(CATEGORY_BULLET, MASK_NONE);
			// setRotation(180.0f);
			tmp_velocity.x = getVelocity().x * -1.0f;
			tmp_velocity.y = getVelocity().y * -1.0f;
			setVelocity(C2B(tmp_velocity));
			move();
		}
		if (len < 1.0f)
		{
			removeAfter(0.0f);
			unscheduleUpdate();
		}
	}

	void setInitialPos()
	{
		__initial_pos = getPosition();
	}

	void onContact(b2Contact *contact) final
	{
		__desired_distance = 0.0f;
		setCategory(CATEGORY_BULLET, MASK_NONE);
		removeAfter(3.0);

		auto delay = cocos2d::DelayTime::create(2.0f);
		auto fadeOut = cocos2d::FadeOut::create(1.0f);
		auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
		runAction(sequence);
	}
};

#endif /* __AXEPROJECTILE_H__ */
