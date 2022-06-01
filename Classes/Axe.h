#ifndef __AXE_H__
#define __AXE_H__

#include "BaseWeapon.h"
#include "AxeProjectile.h"

class Axe : public BaseWeapon {
protected:
	Axe() : BaseWeapon("axe", 1, 0.1f, 0.0f, 0.0f) {}
	virtual ~Axe() {}

public:
	CREATE_FUNC(Axe);

	void attack(bool flipped, const b2Vec2& direction) final {
		if (!isAttackAble()) return;

		auto axe = AxeProjectile::create();

		if (!axe) return;
		addBullet(axe);
		axe->setParent(this);
		axe->setSpeed(25.0f);
		axe->setRotation(VecToDegree(direction));
		axe->setVelocity(direction);
		axe->move();
		axe->setInitialPos();

	}
};

#endif /* __AXE_H__ */
