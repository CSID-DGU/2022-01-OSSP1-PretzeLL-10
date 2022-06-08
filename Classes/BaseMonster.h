#ifndef __BASE_MONSTER_H__
#define __BASE_MONSTER_H__

#include "DynamicObject.h"
#include "Bullet.h"
#include "VoidWeapon.h"
#include "MonsterAI.h"


class BaseMonster : public DynamicObject {
protected:
    typedef DynamicObject target_t;

    static std::list<target_t*> __target;
    int __full_hp;
    int __hp;
    int __damage;

    float attackRange;
    float detectRange;

    MonsterAI* AI;
    VoidWeapon* __weapon;
    cocos2d::Sprite* __health;
    
protected:
    BaseMonster(std::string name);                      // Constructor, initialize variables
    virtual ~BaseMonster();                             // Destructor

public:
    //    CREATE_FUNC(Monster);                          

    virtual bool init() override;                       // Initialize

    virtual void behavior(float dt);
    virtual void roaming();
    virtual void attack();                              // Need update!
    void damaged(int damage, const cocos2d::Vec2& position, float weight);
    void dieing();
    virtual void followTarget();
    void doNothing();

    int getHP();
    void setHP(int hp);
    int getDamage();
    void setDamage(int damage);
    void addBullet(ProjectileObject* bullet, const b2Vec2& pos = b2Vec2(0.0f, 0.0f));
    weapon_t* getWeapon();
    virtual float getWeight();
    std::list<target_t*> getTarget();

    virtual void onContact(b2Contact* contact) override;

    static void addTarget(target_t* target);
    static void deleteTarget(target_t* target);

    float getAttackRange();
    float getDetectRange();
};

typedef BaseMonster monster_t;

#endif /* __MONSTER_H__ */
