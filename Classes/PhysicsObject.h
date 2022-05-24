#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Utility.h"


class PhysicsObject {
protected:
    static b2World* __world;
    b2Body* __body;
    
protected:
    PhysicsObject();
    virtual ~PhysicsObject();
    
public:
    bool init(const b2BodyDef& body, const b2FixtureDef& fixture);
    bool initDynamic(const b2Vec2& size, const b2Vec2& center);
    bool initStatic(const b2Vec2& size, const b2Vec2& center);
    bool initProjectile(const b2Vec2& size, const b2Vec2& center);
    
    void reCreate(const b2Shape* shape);
    void setCategory(const int category, const int mask);
    static int getCategory(const b2Fixture* fixture);
    
    void destoryPhysics();

    static void setWorld(b2World* world);
    static b2World* getWorld();
    static b2Body* createWall(cocos2d::TMXTiledMap* tmap);
};

#endif /* __PHYSICS_H__ */
