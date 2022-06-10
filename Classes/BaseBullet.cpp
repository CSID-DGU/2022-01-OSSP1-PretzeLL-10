#include "BaseBullet.h"


BaseBullet::BaseBullet(std::string name)
: ProjectileObject("frames", name) {
    __weapon = nullptr;
}

BaseBullet::~BaseBullet() {}


bool BaseBullet::init() {
    IF(!ProjectileObject::init());
    IF(!PhysicsObject::initProjectile(C2B(getContentSize()), b2Vec2(0.0f, 0.0f), this));
    setCategory(CATEGORY_BULLET, MASK_BULLET);
    setTag(TAG_BULLET);
    return true;
}

void BaseBullet::setParent(weapon_t* weapon) {
    __weapon = weapon;
}

int BaseBullet::getDamage() {
    if (__weapon == nullptr) {
#if COCOS2D_DEBUG > 0
        std::string err = __name + "::";
        err.append("weapon is not defined on bullet. ");
        err.append("damage will be fixed to ZERO");
        CCLOG("%s", err.data());
#endif
        return 0;
    }
    return __weapon->getDamage();
}

float BaseBullet::getWeight() {
//    b2MassData mass;
//    __body->GetFixtureList()->GetMassData(&mass);
//    return mass.mass;
    return 3.0f;
}


void BaseBullet::onContact(b2Contact* contact) {
    setCategory(CATEGORY_BULLET, MASK_NONE);
    removeAfter(3.0);

    auto delay = cocos2d::DelayTime::create(2.0f);
    auto fadeOut = cocos2d::FadeOut::create(1.0f);
    auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
    runAction(sequence);
}
