#include "BaseMonster.h"


BaseMonster::BaseMonster(std::string name)
: BaseObject(name, 1.0f, 1.0f) {}

BaseMonster::~BaseMonster()
{}


bool BaseMonster::init() {
    IF(!BaseObject::init());
    
    IF(!PhysicsObject::init(C2B(getContentSize()), b2Vec2(0.0f, -1.0f)));
    setCategory(BITMASK_MONSTER);

    runActionByKey(IDLE);
    
    return true;
}
