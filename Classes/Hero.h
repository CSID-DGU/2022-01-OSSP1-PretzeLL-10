#ifndef __PLAYER_H___
#define __PLAYER_H___

#include "DynamicObject.h"
#include "Monster.h"
#include "Weapon.h"


class Hero : public DynamicObject
{
private:
    typedef std::pair<std::vector<weapon_t *>, int> weapon_info;

private:
    std::array<bool, 6> __key;
    cocos2d::Vec2 __mouse;

    DIRECTION __map_dir;
    weapon_info __weapon;
    cocos2d::Sprite* __charge_bar;

    int __hp;
    int __damage;
    int __coin;
    bool __invincible;
    bool __disarmed;

public:
    Hero();
    virtual ~Hero();

    CREATE_FUNC(Hero); // Cocos create function

    virtual bool init() override; // Initialize
    //static cocos2d::Vec2 getMousePos();
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
    void damaged(int damage, const cocos2d::Vec2& direction, float weight);
    void makeInvincible(float time);
    int getHP();
    void setHP(int hp);
    int getDamage();
    void setDamage(int damage);
    void addCoin(int coin);
    bool useCoin(int coin);
    int getCoin();

    void disarm(float time = 0.0f);
    void rearm(float dt);
    void changeWeapon(int index);
    void setWeapon(std::vector<weapon_t *> weapons);
    DIRECTION getDirection(bool isAbleToMove);
    void onContact(b2Contact *contact) final;

private:
    void invincible(float dt);
    void chargeWeapon(float dt);
};

#endif /* __PLAYER_H___ */
