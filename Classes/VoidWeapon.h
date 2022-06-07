#ifndef __VOID_WEAPON_H__
#define __VOID_WEAPON_H__

#include "ProjectileObject.h"
#include "BaseWeapon.h"


class VoidWeapon : private BaseWeapon {
protected:
    VoidWeapon() : BaseWeapon("") {}
    VoidWeapon(int damage) : BaseWeapon("") { __damage[0] = damage; }
    virtual ~VoidWeapon() {}
    
public:
    CREATE_FUNC(VoidWeapon);
    
    bool init() final {
        __level = 0;
        return true;
    }
    
    cocos2d::Node* asNode() {
        return static_cast<cocos2d::Node*>(this);
    }
    
    
    void addBullet(ProjectileObject* bullet, const b2Vec2& pos = b2Vec2(0.0f, 0.0f)) {
        BaseWeapon::addBullet(bullet, pos);
        bullet->setCategory(CATEGORY_HBULLET, MASK_HBULLET);
    }
    
    void setDamage(int damage) {
        __damage[0] = damage;
    }
    
    int getDamage() {
        return BaseWeapon::getDamage();
    }
};

#endif /* __VOID_WEAPON_H__ */
