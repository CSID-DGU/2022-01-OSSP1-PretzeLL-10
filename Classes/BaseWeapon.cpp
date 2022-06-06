#include "BaseWeapon.h"


BaseWeapon::BaseWeapon(std::string name, int damage, float attackT, float chargeT)
: StaticObject("frames", "weapon_" + name) {
    __name = name;
    __angle = 20.0f;
    __damage = damage;
    __attackTime = attackT;
    __chargeTime = chargeT;
}

BaseWeapon::~BaseWeapon() {}

std::map<int, std::function<BaseWeapon*(void)>> BaseWeapon::__create_func;


bool BaseWeapon::init() {
    IF(!StaticObject::init());
    setCategory(CATEGORY_WEAPON, MASK_WEAPON);
    __sprite->setPosition(getContentSize()/1.2f);
    return true;
}

void BaseWeapon::update(float dt) {
    syncToSprite();
    __attackTimer.update(dt);
    __chargeTimer.update(dt);
}

void BaseWeapon::addBullet(cocos2d::Node* bullet, const b2Vec2& pos) {
    auto hero = (DynamicObject*)getParent();
    if (hero) {
        auto world = hero->getParent();
        if (world) {
            world->addChild(bullet);
            auto center_pos = B2C(pos);
            auto size = hero->getContentSize()/2;
            center_pos.x *= size.width;
            center_pos.y *= size.height;
            center_pos.y -= size.height/2;
            auto position = hero->getPosition() + center_pos;
            bullet->setPosition(position);
        }
    }
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

void BaseWeapon::setAngle(float angle) {
    __angle = angle;
    setRotation(angle);
}

float BaseWeapon::getAngle() {
    return __angle;
}


void BaseWeapon::attack(bool flipped, const b2Vec2& direction) {
    if (!isAttackAble()) return;
    
    float angle = 60.0f;
    if (flipped) angle *= -1.0f;
    auto attack = cocos2d::RotateBy::create(__attackTime/2, angle);
    auto revoke = cocos2d::RotateTo::create(__attackTime/2, getRotation());
    auto seq = cocos2d::Sequence::createWithTwoActions(attack, revoke);
    runAction(seq);
}

void BaseWeapon::setDamage(int damage) {
    __damage = damage;
}

int BaseWeapon::getDamage() {
    return __damage;
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
    return __attackTime;
}


void BaseWeapon::insertCreateFunc(int tag, std::function<BaseWeapon*(void)> func) {
    __create_func.insert(std::make_pair(tag, func));
}

BaseWeapon* BaseWeapon::getByTag(int tag) {
    return __create_func.at(tag)();
}
