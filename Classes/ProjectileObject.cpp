#include "ProjectileObject.h"


ProjectileObject::ProjectileObject(std::string path, std::string name) {
    __path = path;
    __name = name;
    __time = Timer(true);
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
    __time.update(dt);
    if (__time.isEnd()) {
        __time.reset();
        restart();
    }
    
    if (__time.isRunning()) syncToSprite();                                     // if object is stopped, position is affected by sprite
    else syncToPhysics();
}


void ProjectileObject::scale(float size) {
    setScale(getScale()*size);
    PhysicsObject::scale(size);
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
    if (!__body) return;
    auto position = B2C(__body->GetPosition()) * PTM_RATIO;
    Node::setPosition(position.x, position.y);
    Node::setRotation(B2C(__body->GetAngle()));
}

void ProjectileObject::syncToSprite() {
    if (!__body) return;
    auto position = C2B(getPosition()/PTM_RATIO);
    __body->SetTransform(position, C2B(getRotation()));
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

void ProjectileObject::stop(float time) {
    __velocity = __body->GetLinearVelocity();
    __body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    __time.set(time);
}

void ProjectileObject::restart() {
    __body->SetLinearVelocity(__velocity);
}

void ProjectileObject::removeAfter(float delay) {
    stop(delay);
    scheduleOnce(schedule_selector(ProjectileObject::removal), delay);
}

void ProjectileObject::removal(float t) {
    removePhysics();
    removeFromParent();
}

cocos2d::Action* ProjectileObject::runAction(cocos2d::Action* action) {
    return __sprite->runAction(action);
}
