#ifndef __BASE_WEAPON_H__
#define __BASE_WEAPON_H__

#include "StaticObject.h"
#include "DynamicObject.h"


class BaseWeapon : public StaticObject {
private:
    typedef std::function<BaseWeapon*(void)> create_func_t;
    static std::map<int, create_func_t> __create_func;
    
protected:    
    float __attackTime;
    float __chargeTime;
    
    bool* __fire_key;
    float __angle;
    int __damage;
    
    Timer __attackTimer;
    Timer __chargeTimer;
    
protected:
    BaseWeapon(std::string name,
               int damage = 4,
               float attackTime = 0.2f,
               float chargeTime = 0.0f);
    virtual ~BaseWeapon();
    
public:
//    CREATE_FUNC(BaseWeapon);
    
    bool init() final;
    void update(float dt) final;
    void addBullet(cocos2d::Node* bullet, const b2Vec2& pos = b2Vec2(0.0f, 0.0f));
    
    void activate();
    void deactivate();
    void registerKey(bool* key);
    
    WEAPON getType();
    void setAngle(float angle);
    float getAngle();
    
    void setAttackTime(float time);
    void setChargeTime(float time);
    float getAttackTime();
    
    bool isAttacking();
    bool isAttackAble();
    bool isCharging();
    
    virtual void attack(bool flipped, const b2Vec2& direction);
    void setDamage(int damage);
    int getDamage();
    
    static void insertCreateFunc(int tag, create_func_t func);
    static BaseWeapon* getByTag(int tag);
};

typedef BaseWeapon weapon_t;

#endif /* __BASE_WEAPON_H__ */
