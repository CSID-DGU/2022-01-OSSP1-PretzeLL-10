#ifndef __PLAYER_H___
#define __PLAYER_H___

#include "DynamicObject.h"
#include "Monster.h"
#include "Weapon.h"


class Hero : public DynamicObject {
public:
    typedef std::pair<std::vector<weapon_t*>, int> weapon_info;
    
private:
    std::array<bool, 6>__key;
    cocos2d::Vec2 __mouse;
    DIRECTION __map_dir;

    weapon_info __weapon;
    int __hp;
    int __damage;
    float __speed_bak;

public:
    Hero();
    virtual ~Hero();                                              
    
    CREATE_FUNC(Hero);                                      // Cocos create function
    
    virtual bool init() override;                           // Initialize
    void updateMouse(cocos2d::Vec2 pos);
    void updateKey(KEY key, bool state);
    
    void flip() final;
    bool isFlipNeeded() override;
    void flipWeapon();
    void move(KEY state);
    void stop(KEY state);
    void run();
    void stopRun();
    
    void attack();
    void testWeapon(float t);
    void damaged(int damage);
    int getHP();
    void setHP(int hp);
    int getDamage();
    void setDamage(int damage);
    
    void changeWeapon(int index);
    void setWeapon(std::vector<weapon_t*> weapons);
    DIRECTION getDirection(bool isAbleToMove);
    void onContact(b2Contact* contact) final;
};

#endif /* __PLAYER_H___ */
