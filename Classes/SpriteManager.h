#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Utility.h"


class SpriteManager {
protected:
    typedef std::map<std::string, cocos2d::Animate*> AnimationMap;      // Action, access by name(string)
    typedef std::vector<cocos2d::RepeatForever*> InfAnimation;          // Infinite Action, access by integer key
    
    std::string __name;
    
    cocos2d::Sprite* __sprite;                                          // Sprite, Actions should run in here
    InfAnimation __inf_anim;                                            // Infinite Action
    AnimationMap __anim;                                                // Animation
    
protected:
    SpriteManager();
    virtual ~SpriteManager();
    
public:
    /* Init */
    bool init(std::string name);
    bool initWithAnimation(std::string name, float run_speed);
    cocos2d::Animation* createAnimation(std::string state, int count, float delay); // Create animation
    cocos2d::Animate* getAnimation(std::string key);                                // Get Animation by key
    
    /* Add */
    void addAnimation(std::string state, int count = 4, float delay = 0.1f);        // Add Animation
    int addInfAnimation(std::string state, int count = 4, float delay = 0.1f);      // Add Infinite animation, return key
    
    /* Util */
    bool isAnimationRunning();
    
    /* Action */
    void runActionByKey(std::string key);                                           // Run Action once
    void runActionByKey(ACTION action);
    void stopActionByKey(ACTION action);
};

#endif /* __SPRITE_H__ */
