#include "PhysicsObject.h"


PhysicsObject::PhysicsObject() {
    __body = nullptr;
}

PhysicsObject::~PhysicsObject() {
    removePhysics();
}


bool PhysicsObject::init(b2BodyDef& body, b2FixtureDef& fixture, void* userData) {
    body.userData = userData;
    fixture.userData = userData;
    __body = __world->CreateBody(&body);
    IF(!__body);
    IF(!__body->CreateFixture(&fixture));
    return true;
}

bool PhysicsObject::initDynamic(const b2Vec2& size, const b2Vec2& center, void* userData) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.linearDamping = 20.0f;
    body.gravityScale = 0.0f;
    body.fixedRotation = true;
    
    b2PolygonShape box;
    float scaleWidth = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    float scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    __size = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    box.SetAsBox(__size.x, __size.y, b2Vec2(__size.x * center.x, __size.y * center.y), 0.0f);
    
    b2FixtureDef fixture;
    fixture.shape = &box;
    fixture.friction = 0.0f;
    fixture.density = 1.0f;
    
    IF(!init(body, fixture, userData));
    return true;
}

bool PhysicsObject::initStatic(const b2Vec2& size, const b2Vec2& center, void* userData) {
    b2BodyDef body;
    body.type = b2_staticBody;
    
    b2PolygonShape shape;
    float scaleWidth = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    float scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    __size = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    shape.SetAsBox(__size.x, __size.y, b2Vec2(center.x * __size.x, center.y * __size.y), 0.0f);
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.isSensor = true;
    
    IF(!init(body, fixture, userData));
    return true;
}

bool PhysicsObject::initProjectile(const b2Vec2 &size, const b2Vec2 &center, void* userData) {
    b2BodyDef body;
    body.type = b2_dynamicBody;
    body.linearDamping = 0.1f;
    body.angularDamping = 0.0f;
    body.gravityScale = 0.0f;
    body.fixedRotation = false;
    
    b2PolygonShape shape;
    float scaleWidth = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    float scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    __size = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    shape.SetAsBox(__size.x, __size.y, b2Vec2(center.x * __size.x, center.y * __size.y), 0.0f);
    
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.friction = 1.0f;
    fixture.density = 0.3f;
    
    IF(!init(body, fixture, userData));
    return true;
}


void PhysicsObject::recreate(const b2Shape* shape) {
    auto __f = __body->GetFixtureList();
    b2FixtureDef __f_n;
    __f_n.shape = shape;
    __f_n.friction = __f->GetFriction();
    __f_n.density = __f->GetDensity();
    __f_n.filter = __f->GetFilterData();
    __body->DestroyFixture(__f);
    __body->CreateFixture(&__f_n);
}

void PhysicsObject::recreate(const b2Vec2& size, const b2Vec2& center) {
    b2PolygonShape shape;
    auto scaleWidth = PHYSICS_BODY_WIDTH/PTM_RATIO;
    auto scaleHeight = PHYSICS_BODY_HEIGHT/PTM_RATIO;
    __size = b2Vec2(size.x * scaleWidth, size.y * scaleHeight);
    shape.SetAsBox(__size.x, __size.y, b2Vec2(center.x * __size.x, center.y * __size.y), 0.0f);
    recreate(&shape);
}

void PhysicsObject::scale(float scaleFactor, const b2Vec2& center) {
    __size.x *= scaleFactor;
    __size.y *= scaleFactor;
    b2PolygonShape shape;
    auto new_center = __body->GetLocalCenter() + center;
    shape.SetAsBox(__size.x, __size.y, new_center, 0.0f);
    recreate(&shape);
}

void PhysicsObject::setType(b2BodyType type) {
    __body->SetType(type);
}

void PhysicsObject::setCategory(const int category, const int mask) {
    if (!__body) return;
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

int PhysicsObject::getCategory(const b2Body* body) {
    return getCategory(body->GetFixtureList());
}

void PhysicsObject::removePhysics() {
    if (!__world || !__body) return;
    __world->DestroyBody(__body);
    __body = nullptr;
}


void PhysicsObject::enablePhysics() {
    __body->SetActive(true);
}

void PhysicsObject::disablePhysics() {
    __body->SetActive(false);
}

void PhysicsObject::sleepPhysics() {
    __body->SetAwake(false);
}


b2ContactEdge* PhysicsObject::getContact() {
    return __body->GetContactList();
}


b2World* PhysicsObject::__world = nullptr;

b2World* PhysicsObject::getWorld() {
    if (!__world) {
        auto gravity = b2Vec2(0.0f, -9.8f);
        __world = new b2World(gravity);
        if(!__world) return NULL;
    }
    
    return __world;
}

b2Body* PhysicsObject::createWall(cocos2d::TMXTiledMap* tmap) {
    auto wall = tmap->getLayer(WALL_LAYER);
    auto door = tmap->getLayer(DOOR_LAYER);
    if(!wall || !door) return nullptr;
    auto size = tmap->getTileSize()/PTM_RATIO*1.6f;
    wall->setVisible(false);
    door->setVisible(false);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(size.width, size.height);
    b2Body* body = PhysicsObject::getWorld()->CreateBody(&bodyDef);
    if(!body) return body;
    
    auto layerSize = wall->getLayerSize();
    for (int i = 0; i < layerSize.width; i++) {
        for (int j = 0; j < layerSize.height; j++) {
            auto gid_wall = wall->getTileGIDAt(cocos2d::Vec2(i, j));
            auto gid_door = door->getTileGIDAt(cocos2d::Vec2(i, j));
            if (gid_wall) {
                auto pos = wall->getPositionAt(cocos2d::Vec2(i, j))/PTM_RATIO;
                if (!createBlock(body, size, pos, CATEGORY_WALL)) return nullptr;
            }
            if (gid_door) {
                auto pos = wall->getPositionAt(cocos2d::Vec2(i, j))/PTM_RATIO;
                if (!createBlock(body, size, pos, CATEGORY_DOOR)) return nullptr;
            }
        }
    }
    
    return body;
}

bool PhysicsObject::createBlock(b2Body *body, cocos2d::Size size, cocos2d::Vec2 pos, int type) {
    b2PolygonShape shape;
    shape.SetAsBox(size.width, size.height, C2B(pos), 0.0f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.0f;
    if (type == CATEGORY_WALL) {
        fixtureDef.filter.categoryBits = CATEGORY_WALL;
        fixtureDef.filter.maskBits = MASK_WALL;
    }
    else if (type == CATEGORY_DOOR) {
        fixtureDef.filter.categoryBits = CATEGORY_DOOR;
        fixtureDef.filter.maskBits = MASK_DOOR;
    }
     
    if(!body->CreateFixture(&fixtureDef)) {
        PhysicsObject::getWorld()->DestroyBody(body);
        return false;
    }
    return true;
}


void PhysicsObject::remove(b2Fixture* fixture) {
    remove(fixture->GetBody());
}

void PhysicsObject::remove(b2Body* body) {
    __world->DestroyBody(body);
}

void PhysicsObject::removeAllMask() {
    b2Body* body = __world->GetBodyList();
    for (int i = 0; i < __world->GetBodyCount(); i++) {
        //auto next = body->GetNext();
        //__world->DestroyBody(body);
        //body = next;

        for (auto __f = body->GetFixtureList(); __f; __f = __f->GetNext()) {
            auto __d = __f->GetFilterData();
            __d.categoryBits = 0;
            __d.maskBits = MASK_NONE;
            __f->SetFilterData(__d);
        }
        body = body->GetNext();
    }
}

void PhysicsObject::onContactEnd(b2Contact* contact) {}
