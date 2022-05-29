#include "Hero.h"


Hero::Hero()
: DynamicObject("knight_f", 3.0f, 2.0f) {
    __key.fill(false);
    __weapon = std::make_pair(std::vector<weapon_t*>(3), 0);
}

Hero::~Hero()
{}


bool Hero::init() {
    IF(!DynamicObject::init());
    
    auto size = C2B(getContentSize());
    size.x *= 0.7f;
    size.y *= 0.5f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -1.0f), this));
    setCategory(CATEGORY_PLAYER, MASK_PLAYER);
    
    runActionByKey(IDLE);
    setHP(6);
    
    /* For test */
    /* ============================================= */
    __weapon.first[0] = Bow::create();
    addChild(__weapon.first[0]);
    __weapon.first[0]->activate();
    __weapon.first[0]->registerKey(&__key[ATTACK]);
    /* ============================================= */
    
    return true;
}

void Hero::update(float dt) {
    updateTimer(dt);
    updateAction();
    syncToPhysics();
    if (!isMoveAble()) return;
    if (isFlipNeeded()) flip();
    DynamicObject::move();
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
    float x_diff = __mouse.x - getPositionX();
    float sprite_x = __sprite->getScaleX();
    return x_diff * sprite_x < 0.0f;
}

void Hero::flipWeapon() {
    auto sprite = __weapon.first[__weapon.second];
    if (!sprite) return;
    float hero_scale = __sprite->getScaleX();
    float weapon_scale = sprite->getScaleX();
    if (hero_scale*weapon_scale > 0.0f) return;
    
    sprite->setScaleX(sprite->getScaleX() * -1);
    sprite->setRotation(sprite->getRotation() * -1);
}

void Hero::move(KEY state) {
    __key[state] = true;
    auto __v = getVelocity();
    switch (state) {
        case UP:    __v.y =  1.0f; break;
        case DOWN:  __v.y = -1.0f; break;
        case LEFT:  __v.x = -1.0f; break;
        case RIGHT: __v.x =  1.0f; break;
        default: break;
    }
    setFuture(MOVE);
    normalize(__v);
    if (__key[SHIFT]) {
        setFuture(RUN);
    }
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
    if (__v.x == 0.0f && __v.y == 0.0f) {
        setFuture(IDLE);
    }
    else {
        normalize(__v);
        if (__key[SHIFT]) setFuture(RUN);
        else setFuture(MOVE);
    }
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
    int current = __weapon.second;
    if (!__weapon.first[current]) return;
    if (__weapon.first[current]->isAttacking()) return;
    
    auto direction = C2B(__mouse - getPosition());
    normalize(direction);
    __weapon.first[current]->attack(isFlipped(), direction);
    
    int type = __weapon.first[current]->getType();
    if (type == IMMEDIATE) {
        pause(__weapon.first[current]->getAttackTime());
    }
    else if (type == CHARGE) {
        static float speed_backup = getSpeed();
        if (__key[ATTACK]) setSpeed(getSpeed()*0.25f);
        else {
            setSpeed(speed_backup);
            pause(__weapon.first[current]->getAttackTime());
        }
    }
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

void Hero::damaged(int damage) {
    DynamicObject::damaged(damage);
    pause(0.5f);
    __body->ApplyForceToCenter(b2Vec2(500.0f, 0.0f), false);
}

void Hero::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_PLAYER) {
        other = contact->GetFixtureA();
    }
    
    switch (getCategory(other)) {
        case CATEGORY_MONSTER: damaged(1); break;
        default: break;
    }
}
