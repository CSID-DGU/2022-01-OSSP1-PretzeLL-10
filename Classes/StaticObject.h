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
    
    void scale(float scaleFactor);
    void setPosition(const cocos2d::Vec2& position) override;
    void setPosition(const float x, const float y) override;
    void setAbsolutePosition(const cocos2d::Vec2& position);
    void setAbsolutePosition(const float x, const float y);
    cocos2d::Size getContentSize();
    void syncToSprite();
    
private:
    void onContact(b2Contact* contact) final;                               // Static object does not recieve contacts
};

#endif /* __STATIC_OBJECT_H__ */
