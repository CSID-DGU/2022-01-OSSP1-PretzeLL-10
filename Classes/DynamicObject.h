#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__

#include "Utility.h"
#include "SpriteObject.h"
#include "PhysicsObject.h"


class DynamicObject : public cocos2d::Node, public SpriteObject, public PhysicsObject  {
protected:
    float __speed;                                                      // Speed Velocity
    float __run_speed;                                                  // Run velocity
    
    Timer __time;
    ACTION __current;                                                   // Action status
    ACTION __future;                                                    // Action future
    b2Vec2 __velocity;
#ifdef DIR_MOUSE
    b2Vec2 __velocity_mouse;
#endif
    
protected:                                                              // BaseObject should not be generated
    DynamicObject(std::string name, float speed, float run_speed);
    virtual ~DynamicObject();
    
public:
//    CREATE_FUNC(BaseObject);                                          // Creating BaseObject is invalid!
    
    virtual bool init() override;                                       // Initialize, create idle animation and run it
    virtual void update(float dt) override;
    void updateTimer(float dt);
    
    /* Transformation */
    virtual void flip();
    bool isFlipNeeded();
    bool isFlipped();
    void scale(float size);
    void setPosition(const cocos2d::Vec2& position) override;
    void setPosition(const float x, const float y) override;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    cocos2d::Size getContentSize();
    
    /* Movement */
    void setSpeed(float speed);                                         // Set speed velocity
    void setRunSpeed(float runSpeed);
    float getSpeed();
    float getRunSpeed();
    void setVelocity(const b2Vec2 velocity);
    b2Vec2 getVelocity();
    void pause(float time);
    bool isMoveAble();
    
    /* Attack */
    virtual void attack() = 0;                                          // Need Overriding!!
    
    /* Action */
    void updateAction();
    ACTION getCurrent();
    void setFuture(ACTION action);
};

#endif /* __DYNAMIC_OBJECT_H__ */
