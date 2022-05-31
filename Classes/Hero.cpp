#include "Hero.h"


Hero::Hero()
: DynamicObject("knight_f")
, __weapon(std::make_pair(std::vector<weapon_t*>(3), 0)) {
    BaseMonster::addTarget(this);
    __key.fill(false);
}

Hero::~Hero() {
    BaseMonster::deleteTarget(this);
}


bool Hero::init() {
    IF(!DynamicObject::init());
    
    auto size = C2B(getContentSize());
    size.x *= 0.7f;
    size.y *= 0.5f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -1.0f), this));
    setCategory(CATEGORY_PLAYER, MASK_PLAYER);
    
    runActionByKey(IDLE);
    setHP(6);
    setSpeed(3.0f);
    setRunSpeed(2.0f);
    
    /* For test */
    /* ============================================= */
    __weapon.first[0] = Bow::create();
    addChild(__weapon.first[0]);
    __weapon.first[0]->activate();
    __weapon.first[0]->registerKey(&__key[ATTACK]);
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
    DynamicObject::flip();
    flipWeapon();
}

bool Hero::isFlipNeeded() {
    if (!__is_flippable) return false;
    auto weapon = __weapon.first[__weapon.second];
    if (weapon) {
        if (weapon->isAttacking()) return false;
    }
    
    float x_diff = __mouse.x - getPositionX();
    float sprite_x = __sprite->getScaleX();
    return x_diff * sprite_x < 0.0f;
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
    if (!weapon) return;
    if (weapon->isAttacking()) return;
    
    auto direction = C2B(__mouse - getPosition());
    normalize(direction);
    weapon->attack(isFlipped(), direction);
    
    int type = weapon->getType();
    if (type == IMMEDIATE) {
        schedule(schedule_selector(Hero::testWeapon));
        pause(weapon->getAttackTime());
    }
    else if (type == CHARGE) {
        if (__key[ATTACK]) {
            __speed_bak = getSpeed();
            setSpeed(getSpeed()*0.25f);
        }
        else {
            setSpeed(__speed_bak);
            pause(weapon->getAttackTime());
        }
    }
}

void Hero::testWeapon(float t) {
    auto weapon = __weapon.first[__weapon.second];
    if (!weapon->isAttacking()) {
        unschedule(schedule_selector(Hero::testWeapon));
        return;
    }
    
    auto contact = weapon->getContact();
    for (; contact; contact = contact->next) {
        if (!contact->contact->IsTouching()) continue;
        auto other = contact->other;
        float other_cat = getCategory(other);
        
        if (other_cat == CATEGORY_MONSTER) {
            auto monster = PhysicsObject::getUserData<monster_t*>(other);
            monster->damaged(weapon->getDamage());
            unschedule(schedule_selector(Hero::testWeapon));
            return;
        }
    }
}

void Hero::damaged(int damage) {
    __hp -= damage;
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


void Hero::changeWeapon(int index) {
    int current = __weapon.second;
    if (index-1 == current) return;
    if (!__weapon.first[index-1]) return;
    
    __weapon.first[current]->deactivate();
    current = index - 1;
    __weapon.second = current;
    __weapon.first[current]->activate();
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
    bool changed = false;
    
    for (auto iter : __weapon.first) {
        if (!iter) continue;
        iter->setRotation(20.0f);
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

void Hero::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_PLAYER) {
        other = contact->GetFixtureA();
    }
    
    float other_cat = getCategory(other);
    if (other_cat == CATEGORY_MONSTER) {
        auto monster = PhysicsObject::getUserData<monster_t*>(other);
        damaged(monster->getDamage());
        pause(0.5f);
        auto diff = getPosition() - monster->getPosition();
        normalize(diff);
        __body->ApplyForceToCenter(C2B(diff*500.0f), false);
    }
}
