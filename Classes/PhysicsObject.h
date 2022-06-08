#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Utility.h"


class PhysicsObject {
protected:
    static b2World* __world;
    b2Body* __body;
    b2Vec2 __size;
    
protected:
    PhysicsObject();
    virtual ~PhysicsObject();
    
public:
    bool init(b2BodyDef& body, b2FixtureDef& fixture, void* userData);
    bool initDynamic(const b2Vec2& size, const b2Vec2& center, void* userData);
    bool initStatic(const b2Vec2& size, const b2Vec2& center, void* userData);
    bool initProjectile(const b2Vec2& size, const b2Vec2& center, void* userData);
    
    void scale(float scaleFactor, const b2Vec2& center = b2Vec2(0.0f, 0.0f));
    void recreate(const b2Shape* shape);
    void recreate(const b2Vec2& size, const b2Vec2& center = b2Vec2(0.0f, 0.0f));
    void setType(b2BodyType type);
    void setCategory(const int category, const int mask);
    static int getCategory(const b2Fixture* fixture);
    static int getCategory(const b2Body* body);
    template <typename t> static t getUserData(b2Fixture* fixture);
    template <typename t> static t getUserData(b2Body* body);
    
    void disablePhysics();
    void enablePhysics();
    void sleepPhysics();
    virtual void removePhysics();
    
    virtual void onContact(b2Contact* contact) = 0;
    b2ContactEdge* getContact();

    static b2World* getWorld();
    static b2Body* createWall(cocos2d::TMXTiledMap* tmap);
    static bool createBlock(b2Body* body, cocos2d::Size size, cocos2d::Vec2 pos, int type);
    static void remove(b2Fixture* fixture);
    static void remove(b2Body* body);
    static void removeAllMask();
};


template <typename t>
t PhysicsObject::getUserData(b2Fixture *fixture) {
    auto data = fixture->GetUserData();
    if (!data) {
        return getUserData<t>(fixture->GetBody());
    }
    return static_cast<t>(data);
}

template <typename t>
t PhysicsObject::getUserData(b2Body *body) {
    return static_cast<t>(body->GetUserData());
}

#endif /* __PHYSICS_H__ */
