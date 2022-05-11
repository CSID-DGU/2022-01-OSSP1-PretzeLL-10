#include "BaseMonster.h"


BaseMonster::BaseMonster(std::string name)
: BaseObject(name, 1.0f, 1.0f) {}

BaseMonster::~BaseMonster()
{}


bool BaseMonster::init() {
    IF(!BaseObject::init());
    
    IF(!Physics::init(c2b(getContentSize()), b2Vec2(0.0f, -1.0f)));
    setCategory(BITMASK_MONSTER);

    runAction(IDLE);
    
    return true;
}
