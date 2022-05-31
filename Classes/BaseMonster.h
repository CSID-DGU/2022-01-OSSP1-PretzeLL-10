#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__

#include "DynamicObject.h"
#include "BaseBullet.h"
#include "BaseWeapon.h"


class BaseMonster : public DynamicObject {
protected:
    typedef DynamicObject target_t;
    
    static std::list<target_t*> __target;
    int __hp;
    int __damage;
    
protected:
    BaseMonster(std::string name);                      // Constructor, initialize variables
    virtual ~BaseMonster();                             // Destructor
    
public:
//    CREATE_FUNC(Monster);                          
    
    virtual bool init() override;                       // Initialize
    
    virtual void behavior(float dt);
    virtual void attack();                              // Need update!
    virtual void damaged(int damage);
    void followTarget();
    void doNothing();
    
    int getHP();
    void setHP(int hp);
    int getDamage();
    void setDamage(int damage);
    
    virtual void onContact(b2Contact* contact) override;
    
    static void addTarget(target_t* target);
    static void deleteTarget(target_t* target);
};

typedef BaseMonster monster_t;

#endif /* __MONSTER_H__ */
