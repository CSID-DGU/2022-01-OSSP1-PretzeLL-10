#include "SpriteManager.h"


SpriteManager::SpriteManager() {}

SpriteManager::~SpriteManager() {
    for (auto i : __inf_anim) i->release();
    for (auto i : __anim) i.second->release();
}


bool SpriteManager::init(std::string name) {
    IF_RF(name.empty(), "name should not be blank");
    __name = name;
    
    std::string __full_name = "frames/" + name + "_idle_anim_f0.png";
    __sprite = cocos2d::Sprite::create(__full_name);
    IF_RF(!__sprite, "Unable to load image: " + __full_name);
    __sprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    __sprite->getTexture()->setTexParameters(TEX_PARA);
    
    return true;
}

bool SpriteManager::initWithAnimation(std::string name, float run_speed) {
    IF(!init(name));
    
    addInfAnimation("idle", 4, 0.1f);
    auto __a = createAnimation("run", 4, 0.1f);
    auto __a_ = cocos2d::Animate::create(__a);
    auto __r = cocos2d::RepeatForever::create(__a_);
    __r->retain();
    __inf_anim.push_back(__r);
    auto __a_r = __a->clone();
    __a_r->setDelayPerUnit(0.1f/run_speed);
    auto __a_r_ = cocos2d::Animate::create(__a_r);
    auto __r_r = cocos2d::RepeatForever::create(__a_r_);
    __r_r->retain();
    __inf_anim.push_back(__r_r);
    
    return true;
}


cocos2d::Animation* SpriteManager::createAnimation(std::string state, int count, float delay) {
    auto __a = cocos2d::Animation::create();
    for (char i = '0'; i < static_cast<char>(count+48); i++) {
        std::string __n = "frames/"+__name+"_"+state+"_anim_f"+i+".png";
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

void SpriteManager::addAnimation(std::string state, int count, float delay) {
    auto __a = createAnimation(state, count, delay);
    auto __a_ = cocos2d::Animate::create(__a);
    __a_->retain();
    __anim.insert(std::make_pair(state, __a_));
}

int SpriteManager::addInfAnimation(std::string state, int count, float delay) {
    auto __a = createAnimation(state, count, delay);
    auto __a_ = cocos2d::Animate::create(__a);
    auto __r = cocos2d::RepeatForever::create(__a_);
    __r->retain();
    __inf_anim.push_back(__r);
    return __inf_anim.size()-1;
}

cocos2d::Animate* SpriteManager::getAnimation(std::string key) {
    IF_RN(__anim.empty(), "animation map is empty");
    AnimationMap::iterator __i = __anim.find(key);
    IF_RN(__i == __anim.end(), "No such animation named: " + key);
    return __i->second;
}

bool SpriteManager::isAnimationRunning() {
    return __sprite->isRunning();
}

void SpriteManager::runActionByKey(std::string key) {
    auto __i = __anim.find(key);
    IF_RV(__i == __anim.end(), "No animation named : " + key);
    __sprite->runAction(__anim[key]);
}

void SpriteManager::runActionByKey(ACTION action) {
    IF_RV(action == ELSE, "key should not be ELSE");
    __sprite->runAction(__inf_anim[action]);
}

void SpriteManager::stopActionByKey(ACTION action) {
    IF_RV(action == ELSE, "key should not be ELSE");
    __sprite->stopAction(__inf_anim[action]);
}
