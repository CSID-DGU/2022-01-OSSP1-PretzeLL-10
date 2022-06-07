#include "SpriteObject.h"


SpriteObject::SpriteObject(std::string path, std::string name)
: __path(path)
, __name(name)
, __sprite(nullptr)
, __inf_anim(InfAnimation(0))
, __anim(AnimationMap()) {}

SpriteObject::~SpriteObject() {
    for (auto i : __inf_anim) i->release();
    for (auto i : __anim) i.second->release();
}


bool SpriteObject::init(std::string path, std::string name) {
    if (path.empty()) return true;
    IF_RF(name.empty(), "name should not be blank");
    __name = name;
    __path = path;
    
    std::string __full_name = path + "/" + name + ".png";
    __sprite = cocos2d::Sprite::create(__full_name);
    IF_RF(!__sprite, "Unable to load image: " + __full_name);
    __sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    __sprite->getTexture()->setTexParameters(TEX_PARA);
    
    return true;
}

bool SpriteObject::initWithAnimation(std::string name, float run_speed, int count) {
    IF(!init("frames", name + "_idle_anim_f0"));
    __name = name;
    
    addInfAnimation("idle", count, 0.1f);
    auto __a = createAnimation("run", count, 0.1f);
    IF(!__a);
    auto __a_ = cocos2d::Animate::create(__a);
    IF(!__a_);
    auto __r = cocos2d::RepeatForever::create(__a_);
    IF(!__r);
    __r->retain();
    __inf_anim.push_back(__r);
    
    auto __a_r = __a->clone();
    IF(!__a_r);
    __a_r->setDelayPerUnit(0.1f/run_speed);
    auto __a_r_ = cocos2d::Animate::create(__a_r);
    IF(!__a_r_);
    auto __r_r = cocos2d::RepeatForever::create(__a_r_);
    IF(!__r_r);
    __r_r->retain();
    __inf_anim.push_back(__r_r);
    
    return true;
}


cocos2d::Animation* SpriteObject::createAnimation(std::string state, int count, float delay) {
    auto __a = cocos2d::Animation::create();
    for (char i = '0'; i < static_cast<char>(count+48); i++) {
        std::string __n = __path+"/"+__name+"_"+state+"_anim_f"+i+".png";
        auto __t = cocos2d::Director::getInstance()->getTextureCache()->addImage(__n);
        IF_RN(!__t, "Unable to load image: " + __n);
        auto __r = cocos2d::Rect::ZERO;
        __r.size = __t->getContentSize();
        __t->setTexParameters(TEX_PARA);
        auto __f = cocos2d::SpriteFrame::createWithTexture(__t, __r);
        __a->addSpriteFrame(__f);
    }
    __a->setDelayPerUnit(delay);
    return __a;
}

cocos2d::Animate* SpriteObject::getAnimation(std::string key) {
    if (__path.empty()) return nullptr;
    IF_RN(__anim.empty(), "animation map is empty");
    AnimationMap::iterator __i = __anim.find(key);
    IF_RN(__i == __anim.end(), "No such animation named: " + key);
    return __i->second;
}

cocos2d::Sprite* SpriteObject::cloneSprite() {
    if (__path.empty()) return nullptr;
    auto sprite = cocos2d::Sprite::createWithTexture(__sprite->getTexture());
    IF_RN(!sprite, "Failed to create sprite");
    sprite->setScale(__sprite->getScale());
    return sprite;
}


void SpriteObject::addAnimation(std::string state, int count, float delay) {
    if (__path.empty()) return;
    auto __a = createAnimation(state, count, delay);
    IF_RV(__a, "Failed to create animation");
    auto __a_ = cocos2d::Animate::create(__a);
    __a_->retain();
    __anim.insert(std::make_pair(state, __a_));
}

int SpriteObject::addInfAnimation(std::string state, int count, float delay) {
    if (__path.empty()) return -1;
    auto __a = createAnimation(state, count, delay);
    IF_RF(!__a, "Failed to create animation");
    auto __a_ = cocos2d::Animate::create(__a);
    auto __r = cocos2d::RepeatForever::create(__a_);
    __r->retain();
    __inf_anim.push_back(__r);
    return __inf_anim.size()-1;
}

bool SpriteObject::isAnimationRunning() {
    if (__path.empty()) return false;
    return __sprite->isRunning();
}

void SpriteObject::runActionByKey(std::string key) {
    if (__path.empty()) return;
    auto __i = __anim.find(key);
    IF_RV(__i == __anim.end(), "No animation named : " + key);
    __sprite->runAction(__anim[key]);
}

void SpriteObject::runActionByKey(ACTION action) {
    if (__path.empty()) return;
    IF_RV(action == ELSE, "key should not be ELSE");
    __sprite->runAction(__inf_anim[action]);
}

void SpriteObject::stopActionByKey(ACTION action) {
    if (__path.empty()) return;
    IF_RV(action == ELSE, "key should not be ELSE");
    __sprite->stopAction(__inf_anim[action]);
}
