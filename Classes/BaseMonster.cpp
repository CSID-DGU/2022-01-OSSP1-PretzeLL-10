#include "BaseMonster.h"


BaseMonster::BaseMonster(std::string name, int hp)
: DynamicObject(name, 1.0f, 1.0f) {
    setHP(hp);
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


void BaseMonster::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_MONSTER) {
        other = contact->GetFixtureA();
    }
    
    switch (getCategory(other)) {
        default: break;
    }
}
