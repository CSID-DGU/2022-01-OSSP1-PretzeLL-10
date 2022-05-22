#ifndef __BASE_WEAPON_H__
#define __BASE_WEAPON_H__

#include "StaticObject.h"


class BaseWeapon : public StaticObject {
protected:
    BaseWeapon(std::string name);
    virtual ~BaseWeapon();
    
public:
//    CREATE_FUNC(BaseWeapon);
    
    bool init() final;
    
    virtual void attack() = 0;
};

#endif /* __BASE_WEAPON_H__ */
