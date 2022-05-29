#include "StaticObject.h"


StaticObject::StaticObject(std::string path, std::string name) {
    __path = path;
    _name = name;
}

StaticObject::~StaticObject() {}


bool StaticObject::init() {
    IF(!Node::init());
    IF(!SpriteObject::init(__path, _name));
    IF(!PhysicsObject::initStatic(C2B(getContentSize()), b2Vec2(0.0f, 0.0f), this));
    addChild(__sprite);
    return true;
}


void StaticObject::setPosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void StaticObject::setPosition(const float x, const float y) {
    Node::setPosition(x, y);
    b2Vec2 __p = C2B(convertToWorldSpace(getPosition()) / PTM_RATIO);
    __body->SetTransform(__p, B2C(__body->GetAngle()));
}

void StaticObject::setAbsolutePosition(const cocos2d::Vec2 &position) {
    setAbsolutePosition(position.x, position.y);
}

void StaticObject::setAbsolutePosition(const float x, const float y) {
    float __x = x/absoluteResolution.width*resolution.width;
    float __y = y/absoluteResolution.height*resolution.height;
    setPosition(__x, __y);
}

cocos2d::Size StaticObject::getContentSize() {
    return __sprite->getContentSize();
}

void StaticObject::syncToSprite() {
    auto position = __sprite->getPosition();
    auto worldPos = convertToWorldSpace(position);
    __body->SetTransform(C2B(worldPos / PTM_RATIO), C2B(getRotation()));
}


void StaticObject::onContact(b2Contact* contact) {
    // Nothing to do with static objects
}
