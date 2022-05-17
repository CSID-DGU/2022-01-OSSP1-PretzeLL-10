#ifndef __PLAYER_H___
#define __PLAYER_H___

#include "BaseObject.h"


class Hero : public BaseObject {
private:
    bool* __key;
    cocos2d::Vec2* __mouse;

public:
    Hero();
    virtual ~Hero();                                              
    
    CREATE_FUNC(Hero);                                    // Cocos create function
    
    virtual bool init() override;                           // Initialize
    void update(float dt) final;
    void setInput(cocos2d::Vec2* mouse, bool* key);
    
    void move(KEY state);
    void stop(KEY state);
    virtual void run();
    virtual void stopRun();
    
    virtual void attack() override;
};

#endif /* __PLAYER_H___ */
