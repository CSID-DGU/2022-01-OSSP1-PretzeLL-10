#include "BaseBullet.h"


BaseBullet::BaseBullet(std::string name)
: ProjectileObject("frames", name)
{}

BaseBullet::~BaseBullet() {}


bool BaseBullet::init() {
    IF(!ProjectileObject::init());
    IF(!PhysicsObject::initProjectile(C2B(getContentSize()), b2Vec2(0.0f, 0.0f), this));
    setCategory(CATEGORY_BULLET, MASK_BULLET);
    return true;
}
