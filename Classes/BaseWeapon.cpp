#include "BaseWeapon.h"
#include "BaseMonster.h"


BaseWeapon::BaseWeapon(std::string name)
: StaticObject("frames", "weapon_" + name) {
    __name = name;
    __angle = 20.0f;
    __level = 0;
    __damage.fill(0);
    __attackTime.fill(0.0f);
    __chargeTime.fill(0.0f);
    __chargeTimer = Timer(true);
}

BaseWeapon::BaseWeapon(std::string name, int damage[MAX_LEVEL::value], float attackTime[MAX_LEVEL::value], float chargeTime[MAX_LEVEL::value])
: StaticObject("frames", "weapon_" + name) {
    __name = name;
    __angle = 20.0f;
    __level = 0;
    
    for (int i = 0; i < MAX_LEVEL::value; i++) {
        __damage[i] = damage[i];
        __attackTime[i] = attackTime[i];
        __chargeTime[i] = chargeTime[i];
    }
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
    if (__chargeTime[__level] > 0.0f) return CHARGE;
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
    auto attack = cocos2d::RotateBy::create(__attackTime[__level]/2, angle);
    auto revoke = cocos2d::RotateTo::create(__attackTime[__level]/2, getRotation());
    auto seq = cocos2d::Sequence::createWithTwoActions(attack, revoke);
    runAction(seq);
}

void BaseWeapon::setLevel(int level) {
    __level = level;
}

void BaseWeapon::setLevelValue(int level, int damage, float attackTime, float chargeTime) {
    __damage[level-1] = damage;
    __attackTime[level-1] = attackTime;
    __chargeTime[level-1] = chargeTime;
}

int BaseWeapon::getDamage() {
    return __damage[__level];
}

bool BaseWeapon::isAttacking() {
    return !__attackTimer.isEnd();
}

bool BaseWeapon::isAttackAble() {
    int type = getType();
    if (type == CHARGE) {
        if (*__fire_key) {
            __chargeTimer.set(__chargeTime[__level]);
            return false;
        }
        if (!__chargeTimer.isEnd()) {
            __chargeTimer.reset();
            return false;
        }
    }
    else if (type == IMMEDIATE) {
        if (!*__fire_key) return false;
    }
    
    if (isAttacking()) return false;
    if (getAttackTime()) __attackTimer.set(getAttackTime());
    
    __chargeTimer.reset();
    return true;
}

bool BaseWeapon::isCharging() {
    return __chargeTimer.getLeft() > 0.0f;
}

float BaseWeapon::getAttackTime() {
    return __attackTime[__level];
}

float BaseWeapon::getChargeTime() {
    return __chargeTime[__level];
}

cocos2d::Node* BaseWeapon::chooseTarget() {
    float len = std::numeric_limits<float>::max();
    auto hero_pos = getParent()->getPosition();
    cocos2d:Node* closest_target = nullptr;
    auto candidate = getParent()->getParent()->getChildren();
    
    for (auto iter : candidate) {
        if (iter->getTag() != TAG_MONSTER) continue;
        float cal_len = length(iter->getPosition() - hero_pos);
        if (len > cal_len) {
            len = cal_len;
            closest_target = iter;
        }
    }
    
    return closest_target;
}

void BaseWeapon::scaleChargeTime(float scale) {
    for (int i = 0; i < MAX_LEVEL::value; i++) {
        __chargeTime[i] *= scale;
    }
}


void BaseWeapon::insertCreateFunc(int tag, std::function<BaseWeapon*(void)> func) {
    __create_func.insert(std::make_pair(tag, func));
}

BaseWeapon* BaseWeapon::getByTag(int tag) {
    return __create_func.at(tag)();
}


std::array<BaseWeapon::level_array, 3> BaseWeapon::getLevelValue() {
    std::array<level_array, 3> ret;
    ret[0] = __damage;
    ret[1] = __attackTime;
    ret[2] = __chargeTime;
    return ret;
}
