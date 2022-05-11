#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Utility.h"


class SpriteGenerator {
protected:
    typedef std::map<std::string, cocos2d::Animate*> animationMap;      // Action, access by name(string)
    typedef std::vector<cocos2d::RepeatForever*> InfAnimation;          // Infinite Action, access by integer key
    
    std::string __name;
    
    cocos2d::Sprite* __sprite;                                          // Sprite, Actions should run in here
    InfAnimation __inf_animation;                                       // Infinite Action
    animationMap __animation;                                           // Animation
    
protected:
    SpriteGenerator();
    virtual ~SpriteGenerator();
    
public:
    bool init(std::string name, float run_speed);
    bool initWithAnimation(std::string name, float run_speed);
    cocos2d::Animation* createAnimation(std::string state, int count, float delay);   // Create animation
    
    void addAnimation(std::string state, int count, float delay);                     // Add Animation
    int addInfAnimation(std::string state, int count, float delay);                   // Add Infinite animation, return key
    cocos2d::Animate* getAnimation(std::string key);                                  // Get Animation by key
    bool isAnimationRunning();
};

#endif /* __SPRITE_H__ */
