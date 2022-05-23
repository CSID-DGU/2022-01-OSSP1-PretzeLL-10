#include "BaseWeapon.h"


BaseWeapon::BaseWeapon(std::string name, float attackT, float revertT, float chargeT)
: StaticObject("frames", "weapon_" + name) {
    __name = name;
    __attackTime = attackT;
    __revertTime = revertT;
    __chargeTime = chargeT;
}

BaseWeapon::~BaseWeapon() {}


bool BaseWeapon::init() {
    IF(!StaticObject::init());
    setCategory(CATEGORY_WEAPON, MASK_WEAPON);
    __sprite->setPosition(getContentSize()/1.2f);
    return true;
}

void BaseWeapon::update(float dt) {
    auto position = __sprite->getPosition();
    auto worldPos = convertToWorldSpace(position)/PTM_RATIO;
    __body->SetTransform(C2B(worldPos), getRotation()/-30.0f);
    
    __attackTimer.update(dt);
    __chargeTimer.update(dt);
}


void BaseWeapon::activate() {
    scheduleUpdate();
    setVisible(true);
}

void BaseWeapon::deactivate() {
    unscheduleUpdate();
    setVisible(false);
    __body->SetTransform(b2Vec2(0.0f, 0.0f), 0.0f);
}

void BaseWeapon::registerKey(bool* key) {
    __fire_key = key;
}

WEAPON BaseWeapon::getType() {
    if (__chargeTime > 0.0f) return CHARGE;
    return IMMEDIATE;
}


void BaseWeapon::attack(bool flipped) {
    if (!isAttackAble()) return;
    
    float angle = 60.0f;
    if (flipped) angle *= -1.0f;
    auto attack = cocos2d::RotateBy::create(__attackTime, angle);
    auto revoke = cocos2d::RotateBy::create(__revertTime, -angle);
    auto seq = cocos2d::Sequence::createWithTwoActions(attack, revoke);
    runAction(seq);
}

bool BaseWeapon::isAttacking() {
    return !__attackTimer.isEnd();
}

bool BaseWeapon::isAttackAble() {
    if (getType() == CHARGE) {
        if (*__fire_key) {
            __chargeTimer.set(__chargeTime);
            return false;
        }
        if (!__chargeTimer.isEnd()) return false;
    }
    else if (getType() == IMMEDIATE) {
        if (!*__fire_key) return false;
    }
    
    if (isAttacking()) return false;
    __attackTimer.set(getAttackTime());
    
    return true;
}

bool BaseWeapon::isCharging() {
    return __chargeTimer.getLeft() > 0.0f;
}

float BaseWeapon::getAttackTime() {
    return __attackTime + __revertTime + 0.02f;                             // jumping one frame  prevents inverted weapon
}
