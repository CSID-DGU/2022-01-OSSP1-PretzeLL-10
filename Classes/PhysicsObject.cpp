#include "PhysicsObject.h"


PhysicsObject::PhysicsObject() {
    __body = nullptr;
}

PhysicsObject::~PhysicsObject() {
    if (__world && __body) __world->DestroyBody(__body);
}


bool PhysicsObject::init(const b2BodyDef& body, const b2FixtureDef& fixture) {
    __body = __world->CreateBody(&body);
    IF(!__body);
    IF(!__body->CreateFixture(&fixture));
    return true;
}

bool PhysicsObject::initDynamic(const b2Vec2& size, const b2Vec2& center) {
    b2BodyDef __b;
    __b.type = b2_dynamicBody;
    __b.linearDamping = 20.0f;
    __b.gravityScale = 0.0f;
    __b.fixedRotation = true;
    __b.userData = this;
    
    b2PolygonShape __p;
    float __s_w = PHYSICS_BODY_HEIGHT/PTM_RATIO;
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

bool PhysicsObject::initStatic(const b2Vec2& size, const b2Vec2& center) {
    b2BodyDef body;
    body.type = b2_staticBody;
    body.userData = this;
    
    b2PolygonShape shape;
    float scaleWidth = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    float scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    auto scaledSize = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    shape.SetAsBox(scaledSize.x, scaledSize.y,
                   b2Vec2(center.x * scaledSize.x, center.y * scaledSize.y), 0.0f);
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.isSensor = true;
    
    IF(!init(body, fixture));
    return true;
}

bool PhysicsObject::initProjectile(const b2Vec2 &size, const b2Vec2 &center) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.linearDamping = 0.1f;
    body.angularDamping = 0.0f;
    body.gravityScale = 0.0f;
    body.fixedRotation = false;
    body.userData = this;
    
    b2PolygonShape shape;
    float scaleWidth = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    float scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    auto scaledSize = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    shape.SetAsBox(scaledSize.x, scaledSize.y,
                   b2Vec2(center.x * scaledSize.x, center.y * scaledSize.y), 0.0f);
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = 1.0f;
    fixture.density = 0.3f;
    
    IF(!init(body, fixture));
    return true;
}


void PhysicsObject::reCreate(const b2Shape* shape) {
    auto __f = __body->GetFixtureList();
    b2FixtureDef __f_n;
    __f_n.shape = shape;
    __f_n.friction = __f->GetFriction();
    __f_n.density = __f->GetDensity();
    __f_n.filter = __f->GetFilterData();
    __body->DestroyFixture(__f);
    __body->CreateFixture(&__f_n);
}

void PhysicsObject::setCategory(const int category, const int mask) {
    for (auto __f = __body->GetFixtureList(); __f; __f = __f->GetNext()) {
        auto __d = __f->GetFilterData();
        __d.categoryBits = category;
        __d.maskBits = mask;
        __f->SetFilterData(__d);
    }
}

int PhysicsObject::getCategory(const b2Fixture* fixture) {
    return fixture->GetFilterData().categoryBits;
}


b2World* PhysicsObject::__world = nullptr;

void PhysicsObject::setWorld(b2World* world) {
    __world = world;
}

b2World* PhysicsObject::getWorld() {
    if (!__world) {
        auto gravity = b2Vec2(0.0f, -9.8f);
        __world = new b2World(gravity);
        if(!__world) return NULL;
    }
    
    return __world;
}

b2Body* PhysicsObject::createWall(cocos2d::TMXTiledMap* tmap) {
    auto metaSet = tmap->getLayer(WALL_LAYER);
    if(!metaSet) return nullptr;
    auto size = tmap->getTileSize()/PTM_RATIO*1.6f;
    metaSet->setVisible(false);
    
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(size.width, size.height);
    b2Body* body = __world->CreateBody(&bodyDef);
    if(!body) return body;
    
    auto layerSize = metaSet->getLayerSize();
    for (int i = 0; i < layerSize.width; i++) {
        for (int j = 0; j < layerSize.height; j++) {
            auto gid = metaSet->getTileGIDAt(cocos2d::Vec2(i, j));
            if (gid) {
                auto pos = metaSet->getPositionAt(cocos2d::Vec2(i, j))/PTM_RATIO;
                shape.SetAsBox(size.width, size.height, C2B(pos), 0.0f);
                fixtureDef.shape = &shape;
                fixtureDef.density = 1.0f;
                fixtureDef.friction = 0.1f;
                fixtureDef.restitution = 0.0f;
                fixtureDef.filter.categoryBits = CATEGORY_WALL;
                fixtureDef.filter.maskBits = MASK_WALL;
                if(!body->CreateFixture(&fixtureDef)) return body;
            }
        }
    }
    
    return body;
}
