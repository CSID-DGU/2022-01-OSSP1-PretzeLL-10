#include "Hero.h"


Hero::Hero()
: DynamicObject("knight_f", 10.0f, 2.0f) {
    __weapon = std::make_pair(std::vector<weapon_t*>(3), 0);
}

Hero::~Hero()
{}


bool Hero::init() {
    IF(!DynamicObject::init());
    IF(!PhysicsObject::initDynamic(C2B(getContentSize()), b2Vec2(0.0f, -0.5f)));
    
    setCategory(CATEGORY_PLAYER, MASK_PLAYER);
    runActionByKey(IDLE);
    
    return true;
}

void Hero::update(float dt) {
    updateTimer(dt);
    updateAction();
    
    Node::setPosition(B2C(__body->GetPosition())*PTM_RATIO);
    
    for (auto contact = __body->GetContactList(); contact; contact = contact->next) {
        auto fixtureA = contact->contact->GetFixtureA();
        auto fixtureB = contact->contact->GetFixtureB();
        float categoryA = PhysicsObject::getCategory(fixtureA);
        float categoryB = PhysicsObject::getCategory(fixtureB);
        if (categoryA != CATEGORY_PLAYER && categoryB != CATEGORY_PLAYER) return;
        
        
    }
    
    if (!isMoveAble()) return;
    if (isFlipNeeded()) flip();
#ifdef DIR_MOUSE
    auto __v_1 = c2b(*__mouse - _position);
    if (length(__v_1) > 15.0f) {
        __velocity_mouse = normalize(__v_1);
        setFuture(MOVE);
        if (__key[SHIFT]) {
            setFuture(RUN);
        }
    }
    else {
        __velocity_mouse = b2Vec2(0.0f, 0.0f);
        setFuture(IDLE);
    }
#endif
    
    DynamicObject::update(dt);
}

void Hero::setInput(cocos2d::Vec2* mouse, bool* key) {
#ifdef DIR_MOUSE
    __mouse = mouse;
#endif
    __key = key;
}


void Hero::flip() {
    DynamicObject::flip();
    flipWeapon();
}

void Hero::flipWeapon() {
    auto sprite = __weapon.first[__weapon.second];
    if (!sprite) return;
    float hero_scale = __sprite->getScaleX();
    float weapon_scale = sprite->getScaleX();
    if (hero_scale*weapon_scale > 0.0f) return;
    
    sprite->setScaleX(sprite->getScaleX() * -1);
    sprite->setPositionX(sprite->getPositionX() * -1);
    sprite->setRotation(sprite->getRotation() * -1);
}

void Hero::move(KEY state) {
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
    if (getCurrent() == ACTION::MOVE) setFuture(RUN);
}

void Hero::stopRun() {
    if (getCurrent() == ACTION::RUN) setFuture(MOVE);
}


void Hero::attack() {
    int current = __weapon.second;
    if (!__weapon.first[current]) return;
    if (__weapon.first[current]->isAttacking()) return;
    
    __weapon.first[current]->attack(isFlipped());
    
    int type = __weapon.first[current]->getType();
    if (type == IMMEDIATE && __key[ATTACK]) {
        pause(__weapon.first[current]->getAttackTime());
    }
    else if (type == CHARGE) {
        if (__key[ATTACK]) setSpeed(getSpeed()*0.25f);
        else {
            setSpeed(getSpeed()*4.0f);
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

