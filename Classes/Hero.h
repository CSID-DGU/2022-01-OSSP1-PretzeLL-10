#ifndef __PLAYER_H___
#define __PLAYER_H___

#include "BaseObject.h"


class Hero : public BaseObject {
private:
    bool* __key;
    cocos2d::Vec2* __mouse;
    
    std::vector<cocos2d::Sprite*> __weapon;
    int __current;

public:
    Hero();
    virtual ~Hero();                                              
    
    CREATE_FUNC(Hero);                                    // Cocos create function
    
    virtual bool init() override;                           // Initialize
    void update(float dt) final;
    void setInput(cocos2d::Vec2* mouse, bool* key);
    
    void flip() final;
    void flipWeapon();
    void move(KEY state);
    void stop(KEY state);
    void run();
    void stopRun();
    
    void changeWeapon(int index);
    void setWeapon(std::vector<cocos2d::Sprite*> weapons);
    void attack() final;
};

#endif /* __PLAYER_H___ */
