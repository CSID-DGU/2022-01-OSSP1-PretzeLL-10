#include "BaseMonster.h"


BaseMonster::BaseMonster(std::string name)
: DynamicObject(name, 1.0f, 1.0f) {
    __hp = 0;
    __damage = 0;
}

BaseMonster::~BaseMonster()
{}


bool BaseMonster::init() {
    IF(!DynamicObject::init());
    
    auto size = C2B(getContentSize());
    size.x *= 1.3f;
    size.y *= 1.4f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -0.3f), this));
    setCategory(CATEGORY_MONSTER, MASK_MONSTER);
    
    runActionByKey(IDLE);
    
    return true;
}


void BaseMonster::damaged(int damage) {
    if ((__hp -= damage) <= 0) {
        setCategory(CATEGORY_MONSTER, MASK_NONE);
        stopAllActions();
        removeAfter(1.5f);
        auto delay = cocos2d::DelayTime::create(0.5f);
        auto fade = cocos2d::FadeOut::create(1.0f);
        auto seq = cocos2d::Sequence::createWithTwoActions(delay, fade);
        runAction(seq);
    }
}


void BaseMonster::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_MONSTER) {
        other = contact->GetFixtureA();
    }
    
    float other_cat = getCategory(other);
    if (other_cat == CATEGORY_BULLET) {
        auto bullet = PhysicsObject::getUserData<bullet_t*>(other);
        auto position = convertToNodeSpace(bullet->getPosition());
        
        bullet->retain();
        bullet->removeFromParentAndCleanup(false);
        addChild(bullet);
        bullet->setScale(bullet->getScale() / getScale());
        bullet->Node::setPosition(position.x, position.y);
        bullet->release();
        
        damaged(bullet->getDamage());
    }
}
