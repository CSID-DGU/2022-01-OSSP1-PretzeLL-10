#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Utility.h"


class Physics {
protected:
    static b2World* __world;
    b2Body* __body;
    
protected:
    Physics();
    virtual ~Physics();
    
public:
    bool init(const b2BodyDef& body, const b2FixtureDef& fixture);
    bool init(const b2Vec2& size, const b2Vec2& center);
    
    void reCreate(const b2Shape* shape);
    void setCategory(const int bit);
    
    static void setWorld(b2World* world);
};

#endif /* __PHYSICS_H__ */
