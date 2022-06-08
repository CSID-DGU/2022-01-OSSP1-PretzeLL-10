#ifndef __LIGHTNIGSTAFF_H__
#define __LIGHTNIGSTAFF_H__

#include "BaseWeapon.h"
#include "ThunderBolt.h"

class LightningStaff : public BaseWeapon
{
protected:
	LightningStaff() : BaseWeapon("green_magic_staff") {}
	virtual ~LightningStaff() {}

public:
	CREATE_FUNC(LightningStaff);

	bool init() final {
		IF(!BaseWeapon::init());
		setLevelValue(1, 1, 0.1f, 0.1f);
		setLevelValue(2, 1, 0.2f, 0.1f);
		setLevelValue(3, 1, 0.2f, 0.1f);
		return true;
	}

    void attack(bool flipped, const b2Vec2& direction) final {
        if (!isAttackAble()) return;

        auto ThunderBolt = ThunderBolt::create();
        if (!ThunderBolt) return;
        addBullet(ThunderBolt, direction);
        ThunderBolt->setParent(this);
        ThunderBolt->setSpeed(50.0f);
        ThunderBolt->setVelocity(b2Vec2(0.0f, -20.0f));                                              // Now rotation is automatically set (in move func)                // set angular velocity to rotate, rotates degree per second
        ThunderBolt->PhysicsObject::scale(0.5, b2Vec2(0.0f, 0.0f));
        ThunderBolt->move();
        ThunderBolt->setInitialPos();

        float angle = -30.0f;
        if (flipped) angle *= -1;
        auto up = cocos2d::RotateBy::create(0.0f, angle);
        auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
        auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
        auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
        runAction(seq);

    }
};

#endif /* __LIGHTNIGSTAFF_H__ */
