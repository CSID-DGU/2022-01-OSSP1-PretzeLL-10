#include "StaticObject.h"


StaticObject::StaticObject(std::string name) {
    _name = name;
}

StaticObject::~StaticObject() {}


bool StaticObject::init() {
    IF(!Node::init());
    IF(!SpriteObject::init("frames", _name));
    IF(!PhysicsObject::initStatic(C2B(getContentSize()), b2Vec2(0.0f, 0.0f)));
    addChild(__sprite);
    return true;
}

void StaticObject::update(float dt) {
    __body->SetTransform(C2B(getPosition()), 0.0f);
}


void StaticObject::setPosition(const cocos2d::Vec2 &position) {
    setPosition(position.x, position.y);
}

void StaticObject::setPosition(const float x, const float y) {
    Node::setPosition(x, y);
    b2Vec2 __p(x/PTM_RATIO, y/PTM_RATIO);
    __body->SetTransform(__p, 0.0f);
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
