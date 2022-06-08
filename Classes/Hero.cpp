#include "Hero.h"


Hero::Hero()
: DynamicObject("knight_f")
, __weapon(std::make_pair(std::vector<weapon_t*>(3), 0))
, __map_dir(MAP_NONE)
, __invincible(false)
, __disarmed(false) {
    BaseMonster::addTarget(this);
    __key.fill(false);
}

Hero::~Hero() {
    BaseMonster::deleteTarget(this);
}


bool Hero::init() {
    IF(!DynamicObject::init());
    
    __charge_bar = cocos2d::Sprite::create("sprite/bar_white.png");
    IF(!__charge_bar);
    __charge_bar->setScale(1.0f, 0.7f);
    __charge_bar->setPosition(0.0f, 20.0f);
    __charge_bar->getTexture()->setTexParameters(TEX_PARA);
    __charge_bar->setLocalZOrder(98);
    addChild(__charge_bar);
    
    auto gauge = cocos2d::Sprite::create("sprite/gauge_white.png");
    IF(!gauge);
    gauge->setScale(0.7f, 0.5f);
    gauge->setPosition(0.0f, 50.0f);
    gauge->getTexture()->setTexParameters(TEX_PARA);
    gauge->setLocalZOrder(99);
    __charge_bar->addChild(gauge);
    __charge_bar->setVisible(false);
    
    auto size = C2B(getContentSize());
    size.x *= 0.7f;
    size.y *= 0.5f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -1.0f), this));
    setCategory(CATEGORY_PLAYER, MASK_PLAYER);
    
    addAnimation("hit", 1, 0.3f);
    runActionByKey(IDLE);
    setHP(6);
    setSpeed(5.0f, true);
    setRunSpeed(2.0f);
    setTag(TAG_PLAYER);
    
    /* For test */
    /* ============================================= */
    __weapon.first[0] = Knife::create();
    addChild(__weapon.first[0]);
    __weapon.first[0]->activate();
    __weapon.first[0]->registerKey(&__key[ATTACK]);
    __weapon.first[0]->setRotation(__weapon.first[0]->getAngle());
    float y = getContentSize().width/-2.0f;
    __weapon.first[0]->setPosition(0.0f, y);
    __weapon.first[0]->setScale(0.8f);
    /* ============================================= */
    
    return true;
}

void Hero::updateMouse(cocos2d::Vec2 pos) {
    __mouse = pos;
}

void Hero::updateKey(KEY key, bool state) {
    __key[key] = state;
}


void Hero::flip() {
    float x_diff = __mouse.x - getPositionX();
    float sprite_x = __sprite->getScaleX();
    if (x_diff * sprite_x < 0.0f) DynamicObject::flip();
    flipWeapon();
}

bool Hero::isFlipNeeded() {
    if (!__is_flippable) return false;
    auto weapon = __weapon.first[__weapon.second];
    if (weapon) {
        if (weapon->isAttacking()) return false;
    }
    return true;
}

void Hero::flipWeapon() {
    auto sprite = __weapon.first[__weapon.second];
    if (!sprite) return;
    if (__sprite->getScaleX() * sprite->getScaleX() < 0.0f) {
        sprite->setScaleX(sprite->getScaleX() * -1);
    }
    if (__sprite->getScaleX() * sprite->getRotation() < 0.0f) {
        sprite->setRotation(sprite->getRotation() * -1);
    }
}

void Hero::move(KEY state) {
    if (state != ALL) __key[state] = true;
    auto __v = getVelocity();
    switch (state) {
        case UP:    __v.y =  1.0f; break;
        case DOWN:  __v.y = -1.0f; break;
        case LEFT:  __v.x = -1.0f; break;
        case RIGHT: __v.x =  1.0f; break;
        default: break;
    }
    if (!__v.x && !__v.y) return;
    setFuture(MOVE);
    if (__key[SHIFT]) {
        setFuture(RUN);
    }
    normalize(__v);
    setVelocity(__v);
}

void Hero::stop(KEY state) {
    __key[state] = false;
    auto __v = getVelocity();
    switch (state) {
        case UP:    if (__key[DOWN ]) __v.y = -1.0f; else __v.y = 0.0f; break;
        case DOWN:  if (__key[UP   ]) __v.y =  1.0f; else __v.y = 0.0f; break;
        case LEFT:  if (__key[RIGHT]) __v.x =  1.0f; else __v.x = 0.0f; break;
        case RIGHT: if (__key[LEFT ]) __v.x = -1.0f; else __v.x = 0.0f; break;
        default: break;
    }
    if (!__v.x && !__v.y) setFuture(IDLE);
    else {
        if (__key[SHIFT]) setFuture(RUN);
        else setFuture(MOVE);
    }
    normalize(__v);
    setVelocity(__v);
}

void Hero::run() {
    __key[RUN] = true;
    if (getCurrent() == ACTION::MOVE) setFuture(RUN);
}

void Hero::stopRun() {
    __key[RUN] = false;
    if (getCurrent() == ACTION::RUN) setFuture(MOVE);
}


void Hero::attack() {
    auto weapon = __weapon.first[__weapon.second];
    if (!weapon || !isMoveAble() || weapon->isAttacking()) return;
    
    auto direction = C2B(__mouse - getPosition());
    normalize(direction);
    weapon->attack(isFlipped(), direction);
    
    int type = weapon->getType();
    if (type == CHARGE) {
        if (__key[ATTACK]) {
            setSpeed(getSpeed()*0.25f);
            __charge_bar->setVisible(true);
            auto gauge = *(__charge_bar->getChildren().begin());
            gauge->setPositionX(0.0f);
            if (!isScheduled(schedule_selector(Hero::chargeWeapon))) {
                schedule(schedule_selector(Hero::chargeWeapon));
            }
        }
        else {
            restoreSpeed();
            __charge_bar->setVisible(false);
            unschedule(schedule_selector(Hero::chargeWeapon));
        }
    }
}

void Hero::chargeWeapon(float dt) {
    auto weapon = __weapon.first[__weapon.second];
    auto gauge = *(__charge_bar->getChildren().begin());
    
    if (!gauge) return;
    float ratio = dt / weapon->getChargeTime() * 51.0f;
    gauge->setPositionX(gauge->getPositionX() + ratio);
    if (gauge->getPositionX() > 50.0f) {
        gauge->setPositionX(51.0f);
    }
}

void Hero::testWeapon(float t) {
//    auto weapon = __weapon.first[__weapon.second];
//    if (!weapon || !weapon->isAttacking()) {
//        unschedule(schedule_selector(Hero::testWeapon));
//        return;
//    }
//
//    auto contact = weapon->getContact();
//    for (; contact; contact = contact->next) {
//        if (!contact->contact->IsTouching()) continue;
//        auto other = contact->other;
//        float other_cat = getCategory(other);
//
//        if (other_cat == CATEGORY_MONSTER) {
//            auto monster = PhysicsObject::getUserData<monster_t*>(other);
//            monster->damaged(weapon->getDamage());
//            unschedule(schedule_selector(Hero::testWeapon));
//            return;
//        }
//    }
}

void Hero::makeInvincible(float time) {
    __invincible = true;
    stopAllActions();
    cocos2d::ActionInterval* action;
    action = cocos2d::Blink::create(1, 3);
    runAction(cocos2d::Repeat::create(action, (unsigned int)time));
    setCategory(CATEGORY_PLAYER, CATEGORY_WALL | CATEGORY_DOOR);
    scheduleOnce(schedule_selector(Hero::invincible), time);
    runActionByKey("hit");
}

void Hero::invincible(float dt) {
    __invincible = false;
    stopAllActions();
    runActionByKey(__current);
    setCategory(CATEGORY_PLAYER, MASK_PLAYER);
}

void Hero::damaged(int damage, const cocos2d::Vec2& direction, float weight) {
    __hp -= damage;
    if (__hp < 0) return;
    if (direction == cocos2d::Vec2::ZERO) return;
    auto diff = getPosition() - direction;
    normalize(diff);
    __body->ApplyForceToCenter(C2B(diff*weight*200.0f), false);
    makeInvincible(1.0f);
    pause(0.3f);
}

int Hero::getHP() {
    return __hp;
}

void Hero::setHP(int hp) {
    __hp = hp;
}

int Hero::getDamage() {
    return __damage;
}

void Hero::setDamage(int damage) {
    __damage = damage;
}


void Hero::disarm(float time) {
    changeWeapon(__weapon.first.size());
    __disarmed = true;
    if (time) scheduleOnce(schedule_selector(Hero::rearm), time);
}

void Hero::rearm(float dt) {
    __disarmed = false;
    changeWeapon(1);
}

void Hero::changeWeapon(int index) {
    if (__disarmed) return;
    int current = __weapon.second;
    if (index-1 == current) return;
    
    if (__weapon.first[current]) {
        __weapon.first[current]->deactivate();
    }
    current = index - 1;
    __weapon.second = current;
    if (__weapon.first[current]) {
        __weapon.first[current]->activate();
    }
    flipWeapon();
}

void Hero::setWeapon(std::vector<weapon_t*> weapons) {
    int current = __weapon.second;
    for (auto iter : __weapon.first) {
        if (!iter) continue;
        iter->deactivate();
        iter->removeFromParent();
    }
    __weapon.first.clear();
    __weapon.first = weapons;
    __weapon.first.push_back(nullptr);
    bool changed = false;
    
    for (auto iter : __weapon.first) {
        if (!iter) continue;
        iter->setRotation(iter->getAngle());
        float y = getContentSize().width/-2.0f;
        iter->setPosition(0.0f, y);
        addChild(iter, 0);
        iter->setScale(0.8f);
        iter->registerKey(&__key[ATTACK]);
        changed = true;
    }
    
    if (changed) {
        if (!__weapon.first[current]) return;
        __weapon.first[current]->activate();
        flipWeapon();
    }
}

DIRECTION Hero::getDirection(bool isAbleToMove) {
    auto dir = __map_dir;
    if (dir) {
        if (!isAbleToMove) return MAP_NONE;
        __map_dir = MAP_NONE;
        pause(0.5f);
    }
    switch (dir) {
        case MAP_UP     : setAbsolutePosition(525.0f, 375.0f); break;
        case MAP_DOWN   : setAbsolutePosition(525.0f, 850.0f); break;
        case MAP_LEFT   : setAbsolutePosition(850.0f, 650.0f); break;
        case MAP_RIGHT  : setAbsolutePosition(150.0f, 650.0f); break;
        default: break;
    }
    return dir;
}

void Hero::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_PLAYER) {
        other = contact->GetFixtureA();
    }
    
    float other_cat = getCategory(other);
    if (other_cat == CATEGORY_MONSTER) {
        if (__invincible) return;
        auto monster = PhysicsObject::getUserData<monster_t*>(other);
        damaged(monster->getDamage(), monster->getPosition(), monster->getWeight());
    }
    else if (other_cat == CATEGORY_HBULLET) {
        if (__invincible) return;
        auto bullet = PhysicsObject::getUserData<bullet_t*>(other);
        damaged(bullet->getDamage(), bullet->getPosition(), bullet->getWeight());
    }
    else if (other_cat == CATEGORY_DOOR) {
        auto pos = getAbsolutePosition();
        if      (pos.x < 300.0f) __map_dir = MAP_LEFT;
        else if (pos.x > 700.0f) __map_dir = MAP_RIGHT;
        else if (pos.y > 700.0f) __map_dir = MAP_UP;
        else if (pos.y < 500.0f) __map_dir = MAP_DOWN;
    }
}
