#include "Hero.h"


Hero::Hero()
: DynamicObject("knight_f", 10.0f, 2.0f) {
    __weapon.resize(3);
    __current = 0;
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
    updateAction();
    for (auto contact = __body->GetContactList(); contact; contact = contact->next) {
        auto fixtureA = contact->contact->GetFixtureA();
        auto fixtureB = contact->contact->GetFixtureB();
        float categoryA = PhysicsObject::getCategory(fixtureA);
        float categoryB = PhysicsObject::getCategory(fixtureB);
        if (categoryA != CATEGORY_PLAYER && categoryB != CATEGORY_PLAYER) return;
        
        
    }
    
    if (!isMoveAble()) return;
    if (isFlipped()) flip();
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
    __mouse = mouse;
    __key = key;
}


void Hero::flip() {
    DynamicObject::flip();
    flipWeapon();
}

void Hero::flipWeapon() {
    auto sprite = __weapon[__current];
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
    
}

void Hero::changeWeapon(int index) {
    if (index-1 == __current) return;
    if (!__weapon[index-1]) return;
    
    __weapon[__current]->setVisible(false);
    __current = index - 1;
    __weapon[__current]->setVisible(true);
    flipWeapon();
}

void Hero::setWeapon(std::vector<cocos2d::Sprite*> weapons) {
    for (auto iter : __weapon) {
        if (!iter) continue;
        iter->removeFromParent();
    }
    __weapon = weapons;
    bool changed = false;
    
    for (auto iter : __weapon) {
        if (!iter) continue;
        iter->setRotation(20.0f);
        float x = iter->getContentSize().width;
        iter->setPosition(cocos2d::Vec2(x, 0.0f));
        addChild(iter, 0);
        iter->setScale(0.8f);
        iter->release();
        iter->setVisible(false);
        changed = true;
    }
    
    if (changed) {
        __weapon[__current]->setVisible(true);
        flipWeapon();
    }
}

