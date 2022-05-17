#include "BaseObject.h"


// ========================================================================================================== //
// Constructor, Destructor
// ========================================================================================================== //

BaseObject::BaseObject(std::string name, float speed, float runSpeed) {
    __speed = speed/scaleFactor;
    __run_speed = runSpeed;
    __time = 0.0f;
    __velocity = b2Vec2(0.0f, 0.0f);
    __velocity_mouse = b2Vec2(0.0f, 0.0f);
    __current = IDLE;
    __future = IDLE;
    _name = name;
}

BaseObject::~BaseObject() {}


// ========================================================================================================== //
// Initialize function
// ========================================================================================================== //

bool BaseObject::init() {
    IF(!Node::init());
    IF(!SpriteObject::initWithAnimation(_name, __run_speed));
    addChild(__sprite);
//  IF(!Physics::init(c2b(getContentSize())));                              /* Using custom physics body is recommended */
    scheduleUpdate();
    return true;
}


// ========================================================================================================== //
// Update function
// ========================================================================================================== //

void BaseObject::update(float dt) {
    if (__time > 0.0f) {
        __time -= dt;
        return;
    }
    Node::setPosition(b2c(__body->GetPosition())*PTM_RATIO);
#ifdef DIR_MOUSE
    auto __v = __velocity_mouse;
#else
    auto __v = __velocity;
#endif
    if (__current == MOVE) {
        __v.x *= __speed;
        __v.y *= __speed;
    }
    else if (__current == RUN) {
        __v.x *= __speed * __run_speed;
        __v.y *= __speed * __run_speed;
    }
//    __body->SetLinearVelocity(__v);
    __body->ApplyForceToCenter(__v, true);
}


// ========================================================================================================== //
// Transformation Section
// ========================================================================================================== //

void BaseObject::flip() {
    __sprite->setScaleX(__sprite->getScaleX() * -1);
}

bool BaseObject::isFlipped() {
    return __sprite->getScaleX()*__velocity.x < 0.0f;
}

void BaseObject::scale(float size) {
    setScale(getScale()*size);
    auto __s = getContentSize()*size;
    float __s_w = PHYSICS_BODY_WIDTH/PTM_RATIO;
    float __s_h = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    
    b2PolygonShape __p;
    __p.SetAsBox(__s.width * __s_w, __s.height * __s_h,
                 b2Vec2(0.0f, -10.0f*size/PTM_RATIO), 0.0f);
    reCreate(&__p);
}

cocos2d::Size BaseObject::getContentSize() {
    return __sprite->getContentSize();
}

void BaseObject::setAbsolutePosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void BaseObject::setAbsolutePosition(const float x, const float y) {
    float __x = x/absoluteResolution.width*resolution.width;
    float __y = y/absoluteResolution.height*resolution.height;
    setPosition(__x, __y);
}

void BaseObject::setPosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void BaseObject::setPosition(const float x, const float y) {
    Node::setPosition(x, y);
    b2Vec2 __p(x/PTM_RATIO, y/PTM_RATIO);
    __body->SetTransform(__p, 0.0f);
}


// ========================================================================================================== //
// Move Section
// ========================================================================================================== //

void BaseObject::setVelocity(const b2Vec2 velocity) {
    __velocity = velocity;
}

b2Vec2 BaseObject::getVelocity() {
    return __velocity;
}

void BaseObject::setSpeed(float speed) {
    __speed = speed;
}

void BaseObject::setRunSpeed(float runSpeed) {
    __run_speed = runSpeed;
}

float BaseObject::getRunSpeed() {
    return __run_speed;
}

void BaseObject::pause(float time) {
    __time = time;
}

bool BaseObject::isMoveAble() {
    return !(__time > 0.0f);
}


// ========================================================================================================== //
// Action Section
// ========================================================================================================== //

void BaseObject::setFuture(ACTION action) {
    __future = action;
}

ACTION BaseObject::getCurrent() {
    return __current;
}

void BaseObject::updateAction() {
    if (__current != __future) {
        stopActionByKey(__current);
        __current = __future;
        runActionByKey(__current);
    }
}

// ========================================================================================================== //
