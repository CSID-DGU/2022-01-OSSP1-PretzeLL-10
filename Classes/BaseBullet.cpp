#include "BaseBullet.h"


BaseBullet::BaseBullet(std::string name, int damage)
: ProjectileObject("frames", name) {
    __damage = damage;
}

BaseBullet::~BaseBullet() {}


bool BaseBullet::init() {
    IF(!ProjectileObject::init());
//    IF(!PhysicsObject::initProjectile(C2B(getContentSize()), b2Vec2(0.0f, 0.0f), this));
//    setCategory(CATEGORY_BULLET, MASK_BULLET);
    return true;
}


void BaseBullet::onContact(b2Contact* contact) {
    removeAfter(1.0);
}
