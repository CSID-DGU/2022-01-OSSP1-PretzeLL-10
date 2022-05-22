#include "BaseWeapon.h"


BaseWeapon::BaseWeapon(std::string name)
: StaticObject(name)
{}

BaseWeapon::~BaseWeapon() {}


bool BaseWeapon::init() {
    IF(!StaticObject::init());
    setCategory(CATEGORY_WEAPON, MASK_WEAPON);
    scheduleUpdate();
    return true;
}
