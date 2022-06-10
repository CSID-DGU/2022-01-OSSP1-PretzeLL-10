#include "BaseMonster.h"
#include "GameManager.h"

BaseMonster::BaseMonster(std::string name)
: DynamicObject(name)
, __hp(0)
, __damage(0)
, __delay(1.0f) {}

BaseMonster::~BaseMonster()
{}

std::list<DynamicObject*> BaseMonster::__target = std::list<DynamicObject*>();


bool BaseMonster::init() {
    IF(!DynamicObject::init());
    
    __health = cocos2d::Sprite::create("sprite/bar_red.png");
    IF(!__health);
    __health->getTexture()->setTexParameters(TEX_PARA);
    __health->setScale(1.0f, 0.7f);
    __health->setPosition(0.0f, __sprite->getContentSize().height/4.0f);
    addChild(__health, 99);
    
    auto health_background = cocos2d::Sprite::create("sprite/bar_black.png");
    IF(!health_background);
    health_background->getTexture()->setTexParameters(TEX_PARA);
    health_background->setScale(1.0f, 0.7f);
    health_background->setPosition(0.0f, __sprite->getContentSize().height/4.0f);
    addChild(health_background, 98);
    
    AI = MonsterAI::create();
    __weapon = VoidWeapon::create();
    __weapon->setDamage(1);
    addChild(__weapon->asNode());

    addChild(AI);
    auto size = C2B(getContentSize());
    size.x *= 1.3f;
    size.y *= 1.4f;
    IF(!PhysicsObject::initDynamic(size, b2Vec2(0.0f, -0.3f), this));
    setCategory(CATEGORY_MONSTER, MASK_MONSTER);
    setTag(TAG_MONSTER);
    schedule(schedule_selector(BaseMonster::behavior));
    runActionByKey(IDLE);
    
    return true;
}

void BaseMonster::addBullet(ProjectileObject *bullet, const b2Vec2& pos) {
    __weapon->addBullet(bullet, pos);
}

weapon_t* BaseMonster::getWeapon() {
    return static_cast<weapon_t*>(__weapon->asNode());
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

void BaseMonster::damaged(int damage, const cocos2d::Vec2& direction, float weight) {
    __hp -= damage;
    if (__hp < 0) __hp = 0;
    float ratio = (float)__hp / (float)__full_hp;
    float adj = __health->getContentSize().width / (__full_hp*2.0f);
    __health->setScale(ratio, 0.7f);
    __health->setPositionX(__health->getPositionX() - adj*damage);
    
    if (direction == cocos2d::Vec2::ZERO) return;
    auto diff = getPosition() - direction;
    normalize(diff);
    __body->ApplyForceToCenter(C2B(diff*weight*200.0f), false);
    if (__hp) pause(0.3f);
}

void BaseMonster::dieing()
{
    setCategory(CATEGORY_MONSTER, MASK_NONE);
    setTag(TAG_MONSTER_DEAD);
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
    __full_hp = hp;
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

float BaseMonster::getDelay()
{
    return __delay;
}

void BaseMonster::setDelay(float delay)
{
    __delay = delay;
}

void BaseMonster::setDamage(int damage) {
    __damage = damage;
}

float BaseMonster::getWeight() {
    return 2.0f;
}


void BaseMonster::onContact(b2Contact* contact) {
    b2Fixture* other = contact->GetFixtureB();
    if (getCategory(other) == CATEGORY_MONSTER) {
        other = contact->GetFixtureA();
    }
    
    float other_cat = getCategory(other);
    if (other_cat == CATEGORY_BULLET) {
        auto bullet = PhysicsObject::getUserData<bullet_t*>(other);
        damaged(bullet->getDamage(), bullet->getPosition(), bullet->getWeight());
        auto position = convertToNodeSpace(bullet->getPosition());
        if (bullet->getTag() == TAG_PENETRATE) return;
        
        bullet->retain();
        bullet->removeFromParentAndCleanup(false);
        addChild(bullet);
        bullet->setScale(bullet->getScale() / getScale());
        bullet->Node::setPosition(position.x, position.y);
        bullet->release();
    }
}


void BaseMonster::addTarget(target_t *target) {
    __target.push_back(target);
}

void BaseMonster::deleteTarget(target_t *target) {
    __target.remove(target);
}
