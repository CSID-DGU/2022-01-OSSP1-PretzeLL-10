#ifndef __MAGICSTAFF_H__
#define __MAGICSTAFF_H__

#include "BaseWeapon.h"
#include "FireBall.h"

class MagicStaff : public BaseWeapon
{
protected:
	MagicStaff() : BaseWeapon("red_magic_staff", 1, 0.1f, 0.0f) {}
	virtual ~MagicStaff() {}

public:
	CREATE_FUNC(MagicStaff);

	void attack(bool flipped, const b2Vec2 &direction) final
	{
		if (!isAttackAble())
			return;

		auto fireBall1 = FireBall::create();
		auto fireBall2 = FireBall::create();
		auto fireBall3 = FireBall::create();
		cocos2d::Vec2 vec;

		if (!fireBall1)
			return;
		addBullet(fireBall1);
		fireBall1->setParent(this);
		fireBall1->setSpeed(10.0f);
		vec = cocos2d::Vec2(direction.x - 0.5f, direction.y - 0.5f);
		fireBall1->setRotation(VecToDegree(normalize(vec)));
		fireBall1->setVelocity(C2B(normalize(vec)));
		fireBall1->PhysicsObject::scale(0.5f);
		fireBall1->move();
		fireBall1->setInitialPos();

		if (!fireBall2)
			return;
		addBullet(fireBall2);
		fireBall2->setParent(this);
		fireBall2->setSpeed(10.0f);
		fireBall2->setRotation(VecToDegree(direction));
		fireBall2->setVelocity(direction);
		fireBall2->PhysicsObject::scale(0.5f);
		fireBall2->move();
		fireBall2->setInitialPos();

		if (!fireBall3)
			return;
		addBullet(fireBall3);
		fireBall3->setParent(this);
		fireBall3->setSpeed(10.0f);
		vec = cocos2d::Vec2(direction.x + 0.5f, direction.y + 0.5f);
		fireBall3->setRotation(VecToDegree(normalize(vec)));
		fireBall3->setVelocity(C2B(normalize(vec)));
		fireBall3->PhysicsObject::scale(0.5f);
		fireBall3->move();
		fireBall3->setInitialPos();

		float angle = 30.0f;
		if (flipped)
			angle *= -1;
		auto up = cocos2d::RotateBy::create(0.0f, angle);
		auto down = cocos2d::RotateBy::create(0.1f, angle * -3.0f);
		auto revoke = cocos2d::RotateTo::create(0.1f, getRotation());
		auto seq = cocos2d::Sequence::create(up, down, revoke, nullptr);
		runAction(seq);
	}
};

#endif /* __MAGICSTAFF_H__ */
