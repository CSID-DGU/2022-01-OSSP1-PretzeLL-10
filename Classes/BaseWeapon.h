#ifndef __BASE_WEAPON_H__
#define __BASE_WEAPON_H__

#include "StaticObject.h"
#include "DynamicObject.h"


class BaseWeapon : public StaticObject {
protected:
    typedef std::function<BaseWeapon*(void)> create_func_t;
    static std::map<int, create_func_t> __create_func;
    
    typedef Int<3> MAX_LEVEL;
    typedef std::array<float, MAX_LEVEL::value> level_array;
    
protected:
    level_array __attackTime;
    level_array __chargeTime;
    level_array __damage;
    int __level;
    
    bool* __fire_key;
    float __angle;
    
    Timer __attackTimer;
    Timer __chargeTimer;
    
protected:
    BaseWeapon(std::string name);
    BaseWeapon(std::string name,
               int damage[MAX_LEVEL::value],
               float attactTime[MAX_LEVEL::value],
               float chargeTime[MAX_LEVEL::value]);
    virtual ~BaseWeapon();
    
public:
//    CREATE_FUNC(BaseWeapon);
    
    virtual bool init() override;
    virtual void update(float dt) override;
    void addBullet(cocos2d::Node* bullet, const b2Vec2& pos = b2Vec2(0.0f, 0.0f));
    
    void activate();
    void deactivate();
    void registerKey(bool* key);
    WEAPON getType();
    void setAngle(float angle);
    float getAngle();
    
    virtual void attack(bool flipped, const b2Vec2& direction);
    void setLevel(int level);
    void setLevelValue(int level, int damage, float attactTime, float chargeTime);
    float getAttackTime();
    float getChargeTime();
    int getDamage();
    bool isAttacking();
    bool isAttackAble();
    bool isCharging();
    
    static void insertCreateFunc(int tag, create_func_t func);
    static BaseWeapon* getByTag(int tag);
};

typedef BaseWeapon weapon_t;

#endif /* __BASE_WEAPON_H__ */
