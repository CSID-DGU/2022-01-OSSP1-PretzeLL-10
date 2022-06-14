#ifndef __FIRESTAFF_H__
#define __FIRESTAFF_H__

#include "BaseWeapon.h"
#include "FireBall.h"

class FireStaff : public BaseWeapon
{
protected:
	FireStaff() : BaseWeapon("red_magic_staff") {}
	virtual ~FireStaff() {}

public:
	CREATE_FUNC(FireStaff);

	bool init() final {
		IF(!BaseWeapon::init());
		setLevelValue(1, 30, 0.1f, 1.0f);
		setLevelValue(2, 80, 0.2f, 0.3f);
		setLevelValue(3, 100, 0.2f, 0.3f);
		return true;
	}

	void attack(bool flipped, const b2Vec2& direction) final
	{
		if (!isAttackAble())
			return;

		auto fireBall1 = FireBall::create();
		auto fireBall2 = FireBall::create();
		auto fireBall3 = FireBall::create();
		cocos2d::Vec2 vec, vecVari;
		vec = cocos2d::Vec2(direction.x, direction.y);

		if (!fireBall1)
			return;
		addBullet(fireBall1, direction);
		fireBall1->setParent(this);
		fireBall1->setSpeed(18.0f);
		fireBall1->setRotation(VecToDegree(normalize(vec)) + 15.0f);
		vecVari = DegreeToVec(VecToDegree(normalize(vec)) + 15.0f);
		fireBall1->setVelocity(C2B(normalize(vecVari)));
		fireBall1->PhysicsObject::scale(0.5f);
		fireBall1->move();
		fireBall1->setInitialPos();

		if (!fireBall2)
			return;
		addBullet(fireBall2, direction);
		fireBall2->setParent(this);
		fireBall2->setSpeed(18.0f);
		fireBall2->setRotation(VecToDegree(direction));
		fireBall2->setVelocity(direction);
		fireBall2->PhysicsObject::scale(0.5f);
		fireBall2->move();
		fireBall2->setInitialPos();

		if (!fireBall3)
			return;
		addBullet(fireBall3, direction);
		fireBall3->setParent(this);
		fireBall3->setSpeed(18.0f);
		fireBall3->setRotation(VecToDegree(normalize(vec)) - 15.0f);
		vecVari = DegreeToVec(VecToDegree(normalize(vec)) - 15.0f);
		fireBall3->setVelocity(C2B(normalize(vecVari)));
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

#endif /* __FIRESTAFF_H__ */
