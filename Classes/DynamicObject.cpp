#include "DynamicObject.h"


// ========================================================================================================== //
// Constructor, Destructor
// ========================================================================================================== //

DynamicObject::DynamicObject(std::string name, float speed, float runSpeed) {
    __speed = speed/powf(scaleFactor, 3.0f);
    __run_speed = runSpeed;
    __velocity = b2Vec2(0.0f, 0.0f);
    __current = IDLE;
    __future = IDLE;
    __name = name;
    __is_flippable = true;
}

DynamicObject::~DynamicObject() {}


// ========================================================================================================== //
// Initialize function
// ========================================================================================================== //

bool DynamicObject::init() {
    IF(!Node::init());
    IF(!SpriteObject::initWithAnimation(__name, __run_speed));
    addChild(__sprite, 5);
//  IF(!Physics::init(c2b(getContentSize())));                                      /* Using custom physics body is recommended */
    scheduleUpdate();
    return true;
}


// ========================================================================================================== //
// Update function
// ========================================================================================================== //

void DynamicObject::update(float dt) {
    if (!isMoveAble()) return;
    if (isFlipNeeded()) flip();
    move();
    syncToPhysics();
}

void DynamicObject::updateTimer(float dt) {
    __time.update(dt);
}


// ========================================================================================================== //
// Transformation Section
// ========================================================================================================== //

void DynamicObject::flip() {
    __sprite->setScaleX(__sprite->getScaleX() * -1);
}

bool DynamicObject::isFlipNeeded() {
    if (!__is_flippable) return false;
    return __sprite->getScaleX()*__velocity.x < 0.0f;
}

bool DynamicObject::isFlipped() {
    return __sprite->getScaleX() < 0.0f;
}

void DynamicObject::fixFlip() {
    __is_flippable = false;
}

void DynamicObject::releaseFlip() {
    __is_flippable = true;
}

void DynamicObject::scale(float size) {
    setScale(getScale()*size);
    auto __s = getContentSize()*size;
    float __s_w = PHYSICS_BODY_WIDTH/PTM_RATIO;
    float __s_h = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    
    b2PolygonShape __p;
    __p.SetAsBox(__s.width * __s_w, __s.height * __s_h,
                 b2Vec2(0.0f, -10.0f*size/PTM_RATIO), 0.0f);
    reCreate(&__p);
}

cocos2d::Size DynamicObject::getContentSize() {
    return __sprite->getContentSize();
}

void DynamicObject::setAbsolutePosition(const cocos2d::Vec2 &position) {
    setAbsolutePosition(position.x, position.y);
}

void DynamicObject::setAbsolutePosition(const float x, const float y) {
    float __x = x/absoluteResolution.width*resolution.width;
    float __y = y/absoluteResolution.height*resolution.height;
    setPosition(__x, __y);
}

void DynamicObject::setPosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void DynamicObject::setPosition(const float x, const float y) {
    Node::setPosition(x, y);
    b2Vec2 __p(x/PTM_RATIO, y/PTM_RATIO);
    __body->SetTransform(__p, 0.0f);
}

void DynamicObject::syncToPhysics() {
    auto position = B2C(__body->GetPosition()) * PTM_RATIO;
    Node::setPosition(position.x, position.y);
}


// ========================================================================================================== //
// Move Section
// ========================================================================================================== //

void DynamicObject::move() {
    auto __v = __velocity;
    if (__current == MOVE) {
        __v.x *= __speed;
        __v.y *= __speed;
    }
    else if (__current == RUN) {
        __v.x *= __speed * __run_speed;
        __v.y *= __speed * __run_speed;
    }
    __body->ApplyForceToCenter(__v, true);
}

void DynamicObject::setVelocity(const b2Vec2 velocity) {
    __velocity = velocity;
}

b2Vec2 DynamicObject::getVelocity() {
    return __velocity;
}

void DynamicObject::setSpeed(float speed) {
    __speed = speed;
}

void DynamicObject::setRunSpeed(float runSpeed) {
    __run_speed = runSpeed;
}

float DynamicObject::getSpeed() {
    return __speed;
}

float DynamicObject::getRunSpeed() {
    return __run_speed;
}

void DynamicObject::pause(float time) {
    __time.set(time);
}

bool DynamicObject::isMoveAble() {
    return __time.isEnd();
}


// ========================================================================================================== //
// Action Section
// ========================================================================================================== //

void DynamicObject::setFuture(ACTION action) {
    __future = action;
}

ACTION DynamicObject::getCurrent() {
    return __current;
}

void DynamicObject::updateAction() {
    if (__current != __future) {
        stopActionByKey(__current);
        __current = __future;
        runActionByKey(__current);
    }
}

// ========================================================================================================== //
