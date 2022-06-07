#ifndef __BASE_BULLET_H__
#define __BASE_BULLET_H__

#include "ProjectileObject.h"
#include "BaseWeapon.h"


class BaseBullet : public ProjectileObject {
protected:
    weapon_t* __weapon;
    
protected:
    BaseBullet(std::string name);
    virtual ~BaseBullet();
    
public:
//    CREATE_FUNC(BaseBullet);
    
    virtual bool init() override;
    void setParent(weapon_t* weapon);
    
    virtual void onContact(b2Contact* contact) override;
    int getDamage();
    virtual float getWeight();
};

typedef BaseBullet bullet_t;

#endif /* __BASE_BULLET_H__ */
