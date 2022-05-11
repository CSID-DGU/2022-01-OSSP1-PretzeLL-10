#ifndef __BASE_OBJECT_H__
#define __BASE_OBJECT_H__

#include "Utility.h"
#include "SpriteGenerator.h"
#include "Physics.h"


enum ACTION {
    IDLE = 0,
    MOVE,
    RUN,
    ELSE
};

class BaseObject : public cocos2d::Node, protected SpriteGenerator, protected Physics  {
protected:
    typedef std::map<std::string, cocos2d::Animate*> animationMap;      // Action, access by name(string)
    typedef std::vector<cocos2d::RepeatForever*> InfAnimation;          // Infinite Action, access by integer key
    
    float __speed;                                                      // Speed Velocity
    float __run_speed;                                                  // Run velocity
    
    float __time;
    ACTION __current;                                                   // Action status
    ACTION __future;                                                    // Action future
    b2Vec2 __velocity;
    b2Vec2 __velocity_mouse;
    
protected:                                                              // BaseObject should not be generated
    BaseObject(std::string name, float speed, float run_speed);
    virtual ~BaseObject();                                              
    
public:
//    CREATE_FUNC(BaseObject);                                          // Creating BaseObject is invalid!
    
    virtual bool init() override;                                       // Initialize, create idle animation and run it
    virtual void update(float dt) override;
    
    /* Transformation Section */
    void flip();
    bool isFlipped();
    void scale(float size);
    void setPosition(const cocos2d::Vec2& position) override;
    void setPosition(const float x, const float y) override;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    cocos2d::Size getContentSize();
    
    /* Movement Section */
    void setSpeed(float speed);                                         // Set speed velocity
    void setRunSpeed(float runSpeed);
    float getRunSpeed();
    void setVelocity(const b2Vec2 velocity);
    b2Vec2 getVelocity();
    void pause(float time);
    bool isMoveAble();
    
    /* Attack Section */
    virtual void attack() = 0;                                          // Need Overriding!!
    
    /* Action Section */
    void updateAction();
    void runAction(std::string key);                                    // Run Action once
    void runAction(ACTION action);
    void stopAction(ACTION action);
    ACTION getCurrent();
    void setFuture(ACTION action);
};

#endif /* __BASEOBJECT_H__ */
