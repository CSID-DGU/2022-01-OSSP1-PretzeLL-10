#include "BaseMonster.h"


BaseMonster::BaseMonster(std::string name)
: DynamicObject(name, 1.0f, 1.0f) {}

BaseMonster::~BaseMonster()
{}


bool BaseMonster::init() {
    IF(!DynamicObject::init());
    IF(!PhysicsObject::initDynamic(C2B(getContentSize()), b2Vec2(0.0f, -0.5f)));
    
    setCategory(CATEGORY_MONSTER, MASK_MONSTER);
    runActionByKey(IDLE);
    
    return true;
}
