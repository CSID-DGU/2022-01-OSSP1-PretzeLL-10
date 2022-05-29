#ifndef __PROJECTILE_OBJECT_H__
#define __PROJECTILE_OBJECT_H__

#include "Utility.h"
#include "SpriteObject.h"
#include "PhysicsObject.h"


class ProjectileObject : public cocos2d::Node, public SpriteObject, public PhysicsObject {
protected:
    bool __end;
    float __speed;
    b2Vec2 __velocity;
    
    Timer __time;
    
protected:
    ProjectileObject(std::string path, std::string name);
    virtual ~ProjectileObject();
    
public:
//    CREATE_FUNC(ProjectileObject);
    
    virtual bool init() override;
    virtual void update(float dt) override;
    
    void scale(float size);
    void setPosition(const cocos2d::Vec2& position) override;
    void setPosition(const float x, const float y) override;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    void setRotation(float angle) override;
    cocos2d::Size getContentSize();
    
    virtual void move();
    void setSpeed(float speed);
    void setVelocity(const b2Vec2 velocity);
    float getSpeed();
    b2Vec2 getVelocity();
    void pause(float time);

    void syncToPhysics();
    void removeAfter(float delay);
    virtual void onContact(b2Contact* contact) override = 0;
};

#endif /* __PROJECTILE_OBJECT_H__ */
