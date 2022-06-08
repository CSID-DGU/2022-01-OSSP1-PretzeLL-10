#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__

#include "Utility.h"
#include "SpriteObject.h"
#include "PhysicsObject.h"


class DynamicObject : public cocos2d::Node, public SpriteObject, public PhysicsObject  {
protected:
    float __speed;                                                      // Speed Velocity
    float __speed_bak;
    float __run_speed;                                                  // Run velocity
    b2Vec2 __velocity;
    
    Timer __time;
    bool __is_flippable;
    ACTION __current;                                                   // Action status
    ACTION __future;                                                    // Action future
    
protected:                                                              // BaseObject should not be generated
    DynamicObject(std::string name);
    virtual ~DynamicObject();
    
public:
//    CREATE_FUNC(BaseObject);                                          // Creating BaseObject is invalid!
    
    virtual bool init() override;                                       // Initialize, create idle animation and run it
    virtual void update(float dt) override;
    void updateTimer(float dt);
    
    /* Transformation */
    virtual void flip();
    virtual bool isFlipNeeded();
    bool isFlipped();
    void fixFlip();
    void releaseFlip();
    void scale(float scaleFactor);
    void setPosition(const cocos2d::Vec2& position) final;
    void setPosition(const float x, const float y) final;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    cocos2d::Vec2 getAbsolutePosition();
    cocos2d::Size getContentSize();
    void syncToPhysics();
    
    /* Movement */
    virtual void move();
    void setSpeed(float speed, bool backUp = false);                    // Set speed velocity
    void restoreSpeed();
    void setRunSpeed(float runSpeed);
    float getSpeed();
    float getRunSpeed();
    void setVelocity(const b2Vec2 velocity);
    b2Vec2 getVelocity();
    void pause(float time);
    bool isMoveAble();
    
    /* Animation */
    void updateAction();
    ACTION getCurrent();
    void setFuture(ACTION action);
    cocos2d::Action* runAction(cocos2d::Action* action) final;
    void stopAction(cocos2d::Action* action);
    void stopAllActions();
    
    void removeAfter(float delay);
    virtual void onContact(b2Contact* contact) override = 0;
    
private:
    void removal(float t);
};

#endif /* __DYNAMIC_OBJECT_H__ */
