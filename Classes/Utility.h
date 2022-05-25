#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <memory>
#include <map>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <functional>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Debug.h"
#include "Definition.h"
#include "Box2D/Box2D.h"
#include "B2DebugDrawLayer.h"


template <int num> struct Int { enum { value = num }; };


static inline void endProgram() {
    cocos2d::Director::getInstance()->end();
}


inline float length(const b2Vec2& vec) {
    return std::sqrtf(std::powf(vec.x,2)+std::powf(vec.y,2));;
}

inline b2Vec2 normalize(b2Vec2& vec) {
    float __l = length(vec);
    vec = b2Vec2(vec.x/__l, vec.y/__l);
    return vec;
}

static inline const cocos2d::Vec2 B2C(const b2Vec2 vec) {
    return cocos2d::Vec2(vec.x, vec.y);
}

static inline const b2Vec2 C2B(const cocos2d::Vec2 vec) {
    return b2Vec2(vec.x, vec.y);
}

static inline const float B2C(float angle) {
    return -1 * CC_RADIANS_TO_DEGREES(angle);
}

static inline const float C2B(float angle) {
    return -1 * CC_DEGREES_TO_RADIANS(angle);
}

static inline const float VecToDegree(const cocos2d::Vec2& vec) {
    return CC_RADIANS_TO_DEGREES(atan2f(vec.x, vec.y));
}

static inline const float VecToDegree(const b2Vec2& vec) {
    return CC_RADIANS_TO_DEGREES(atan2f(vec.x, vec.y));
}


class Timer {
private:
    float __run_time = 0.0f;
    float __time = 0.0f;
    
    bool __end = true;
    bool __invert = false;
    
public:
    Timer(bool inverted = false) {
        if (inverted) __end = false;
        __invert = inverted;
    }
    
    void update(float dt) {
        if (__time > 0) __time -= dt;
        if (__time < 0) __end = true;
    }
    
    void reset(bool inverted) {
        set(0.0f);
        if (!__invert) __end = true;
    }
    
    void set(float time) {
        __run_time = time;
        __time = time;
        __end = false;
    }
    
    float getSetTime() {
        return __run_time;
    }
    
    float getLeft() {
        return __time;
    }
    
    float getRunTime() {
        return __run_time - __time;
    }
    
    bool isEnd() {
        return __end;
    }
};

#endif /* __UTILITY_H__ */
