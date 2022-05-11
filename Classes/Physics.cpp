#include "Physics.h"


Physics::Physics() {}

Physics::~Physics() {}


bool Physics::init(const b2BodyDef& body, const b2FixtureDef& fixture) {
    __body = __world->CreateBody(&body);
    IF(!__body);
    
    __body->CreateFixture(&fixture);
    
    return true;
}

bool Physics::init(const b2Vec2& size, const b2Vec2& center) {
    b2BodyDef __b;
    __b.type = b2_dynamicBody;
    __b.linearDamping = 20.0f;
    __b.gravityScale = 0.0f;
    __b.fixedRotation = true;
    __b.userData = this;
    
    b2PolygonShape __p;
    float __s_w = PHYSICS_BODY_WIDTH/PTM_RATIO;
    float __s_h = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    auto __s = b2Vec2(size.x * __s_w, size.y * __s_h);
    __p.SetAsBox(__s.x, __s.y, b2Vec2(__s.x*center.x, __s.y*center.y), 0.0f);
    
    b2FixtureDef __f;
    __f.shape = &__p;
    __f.friction = 0.0f;
    __f.density = 1.0f;
    IF(!init(__b, __f));
    
    return true;
}


void Physics::reCreate(const b2Shape* shape) {
    auto __f = __body->GetFixtureList();
    b2FixtureDef __f_n;
    __f_n.shape = shape;
    __f_n.friction = __f->GetFriction();
    __f_n.density = __f->GetDensity();
    __body->DestroyFixture(__f);
    __body->CreateFixture(&__f_n);
}

b2World* Physics::__world = nullptr;

void Physics::setWorld(b2World* world) {
    __world = world;
}

void Physics::setCategory(const int bit) {
    for (auto __f = __body->GetFixtureList(); __f; __f = __f->GetNext()) {
        auto __d = __f->GetFilterData();
        __d.categoryBits = bit;
        __f->SetFilterData(__d);
    }
}
