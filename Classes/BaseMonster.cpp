#include "BaseMonster.h"
#include "GameManager.h"

BaseMonster::BaseMonster(std::string name)
: DynamicObject(name)
, __hp(0)
, __damage(0) {}

BaseMonster::~BaseMonster()
{}

std::list<DynamicObject*> BaseMonster::__target = std::list<DynamicObject*>();


bool BaseMonster::init() {
    IF(!DynamicObject::init());
    
    AI = MonsterAI::create();

    addChild(AI);
    auto size = C2B(getContentSize());
    size.x *= 1.3f;
    size.y *= 1.4f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -0.3f), this));
    setCategory(CATEGORY_MONSTER, MASK_MONSTER);
    schedule(schedule_selector(BaseMonster::behavior));
    runActionByKey(IDLE);
    
    return true;
}


void BaseMonster::behavior(float dt) {
    State state = AI->getState();
    switch (state)
    {
    case State::ATTACK:
        attack();
        break;
    case State::MOVE:
        followTarget();
        break;
    case State::ROAM:
        roaming();
        break;
    case State::DIE:
        dieing();
        break;
    case State::WAIT:
        doNothing();
        break;
    default:
        setVelocity(b2Vec2(0.0f, 0.0f));
    }
}

void BaseMonster::followTarget() {}

void BaseMonster::doNothing() {
    setVelocity(b2Vec2(0.0f, 0.0f));
    setFuture(IDLE);
}

void BaseMonster::roaming()
{}

void BaseMonster::attack() {
    // Needs override
    std::cout << "Attack" << std::endl;
}

void BaseMonster::damaged(int damage) {
    __hp -= damage;
}

void BaseMonster::dieing()
{
    setCategory(CATEGORY_MONSTER, MASK_NONE);
    stopAllActions();
    removeAfter(1.5f);
    setVelocity(b2Vec2(0.0f, 0.0f));
    GameManager::getInstance()->deleteMonster(this);
    unschedule(schedule_selector(BaseMonster::behavior));

    auto delay = cocos2d::DelayTime::create(0.5f);
    auto fade = cocos2d::FadeOut::create(1.0f);
    auto seq = cocos2d::Sequence::createWithTwoActions(delay, fade);
    runAction(seq);
}


int BaseMonster::getHP() {
    return __hp;
}

void BaseMonster::setHP(int hp) {
    __hp = hp;
}

int BaseMonster::getDamage() {
    return __damage;
}

std::list<DynamicObject*> BaseMonster::getTarget()
{
    return __target;
}

float BaseMonster::getAttackRange()
{
    return attackRange;
}

float BaseMonster::getDetectRange()
{
    return detectRange;
}

void BaseMonster::setDamage(int damage) {
    __damage = damage;
}


void BaseMonster::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_MONSTER) {
        other = contact->GetFixtureA();
    }
    
    float other_cat = getCategory(other);
    if (other_cat == CATEGORY_BULLET) {
        auto bullet = PhysicsObject::getUserData<bullet_t*>(other);
        auto position = convertToNodeSpace(bullet->getPosition());
        
        bullet->retain();
        bullet->removeFromParentAndCleanup(false);
        addChild(bullet);
        bullet->setScale(bullet->getScale() / getScale());
        bullet->Node::setPosition(position.x, position.y);
        bullet->release();
        
        damaged(bullet->getDamage());
    }
}


void BaseMonster::addTarget(target_t *target) {
    __target.push_back(target);
}

void BaseMonster::deleteTarget(target_t *target) {
    __target.remove(target);
}
