#include "Player.h"


Player::Player()
: BaseObject("knight_f", 10.0f, 2.0f) {}

Player::~Player()
{}


bool Player::init() {
    IF(!BaseObject::init());
    
    IF(!Physics::init(c2b(getContentSize()), b2Vec2(0.0f, -0.5f)));
    setCategory(BITMASK_PLAYER);
    
    runAction(IDLE);
    
    return true;
}

void Player::update(float dt) {
    updateAction();
    for (auto __e = __body->GetContactList(); __e; __e = __e->next) {
        auto __a = __e->contact->GetFixtureA();
        auto __b = __e->contact->GetFixtureB();
        
        if (__a->GetFilterData().categoryBits == BITMASK_PLAYER) {
            
        }
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
//    auto __v_2 = b2Vec2(-__velocity.x, __velocity.y);
//    normalize(__v_1);
//    float __d = __v_1.x*__v_2.y - __v_1.y*__v_2.x;
//    float __c = __v_1.x*__v_2.x + __v_1.y*__v_2.y;
//    float __s = std::sinf(std::acosf(__c));
//    __s = (__d > 0.0f) ? __s : -__s;
//    __velocity_mouse = b2Vec2(__s, __c);
#endif
    
    BaseObject::update(dt);
}

void Player::setInput(cocos2d::Vec2* mouse, bool* key) {
    __mouse = mouse;
    __key = key;
}


void Player::move(KEY state) {
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

void Player::stop(KEY state) {
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

void Player::run() {
    if (getCurrent() == ACTION::MOVE) setFuture(RUN);
}

void Player::stopRun() {
    if (getCurrent() == ACTION::RUN) setFuture(MOVE);
}
