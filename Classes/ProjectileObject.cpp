#include "ProjectileObject.h"


ProjectileObject::ProjectileObject(std::string path, std::string name) {
    __path = path;
    __name = name;
}

ProjectileObject::~ProjectileObject() {}


bool ProjectileObject::init() {
    IF(!Node::init());
    IF(!SpriteObject::init(__path, __name));
    addChild(__sprite, 5);
//    IF(!PhysicsObject::initProjectile(getContentSize(), 0.0f));
    scheduleUpdate();
    return true;
}

void ProjectileObject::update(float dt) {
    if (!isMoveAble()) return;
    syncToPhysics();
}


void ProjectileObject::scale(float size) {
    setScale(getScale()*size);
    auto __s = getContentSize()*size;
    float __s_w = PHYSICS_BODY_WIDTH/PTM_RATIO;
    float __s_h = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    
    b2PolygonShape __p;
    __p.SetAsBox(__s.width * __s_w, __s.height * __s_h,
                 b2Vec2(0.0f, -10.0f*size/PTM_RATIO), 0.0f);
    reCreate(&__p);
}

void ProjectileObject::setPosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void ProjectileObject::setPosition(const float x, const float y) {
    Node::setPosition(x, y);
    b2Vec2 __p(x/PTM_RATIO, y/PTM_RATIO);
    __body->SetTransform(__p, 0.0f);
}

void ProjectileObject::setAbsolutePosition(const cocos2d::Vec2 &position) {
    setAbsolutePosition(position.x, position.y);
}

void ProjectileObject::setAbsolutePosition(const float x, const float y) {
    float __x = x/absoluteResolution.width*resolution.width;
    float __y = y/absoluteResolution.height*resolution.height;
    setPosition(__x, __y);
}

void ProjectileObject::setRotation(float angle) {
    Node::setRotation(angle);
    __body->SetTransform(__body->GetPosition(), C2B(angle));
}

cocos2d::Size ProjectileObject::getContentSize() {
    return __sprite->getContentSize();
}

void ProjectileObject::syncToPhysics() {
    auto position = B2C(__body->GetPosition()) * PTM_RATIO;
    Node::setPosition(position.x, position.y);
    Node::setRotation(B2C(__body->GetAngle()));
}


void ProjectileObject::move() {
    auto __v = __velocity;
    __v.x *= __speed;
    __v.y *= __speed;
    
    float point = getContentSize().height / (-2.0f * PTM_RATIO);
    auto tailPos = __body->GetWorldPoint(b2Vec2(0.0f, point));
    __body->ApplyForce(__v, tailPos, true);
}

void ProjectileObject::setSpeed(float speed) {
    __speed = speed;
}

void ProjectileObject::setVelocity(const b2Vec2 velocity) {
    __velocity = velocity;
}

float ProjectileObject::getSpeed() {
    return __speed;
}

b2Vec2 ProjectileObject::getVelocity() {
    return __velocity;
}

void ProjectileObject::pause(float time) {
    __velocity = __body->GetLinearVelocity();
    __velocity.x /= __speed;
    __velocity.y /= __speed;
    __body->SetType(b2_staticBody);
    
    __time.set(time);
}

bool ProjectileObject::isMoveAble() {
    return __time.isEnd();
}


