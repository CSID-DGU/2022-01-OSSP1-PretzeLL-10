#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__

#include "Utility.h"
#include "SpriteObject.h"
#include "PhysicsObject.h"


class StaticObject : public cocos2d::Node, public SpriteObject, public PhysicsObject {
protected:
    StaticObject(std::string path, std::string name);
    virtual ~StaticObject();
    
public:
    virtual bool init() override;
    
    void setPosition(const cocos2d::Vec2& position) override;
    void setPosition(const float x, const float y) override;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    cocos2d::Size getContentSize();
    void syncToSprite();
    
    virtual void onContact(b2Contact* contact) override;
};

#endif /* __STATIC_OBJECT_H__ */
