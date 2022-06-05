#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <memory>
#include <map>
#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <functional>
#include <limits>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Debug.h"
#include "Definition.h"
#include "Box2D/Box2D.h"
#include "B2DebugDrawLayer.h"


template <int num> struct Int { enum { value = num }; };


inline void endProgram() {
    cocos2d::Director::getInstance()->end();
}


inline float length(const b2Vec2& vec) {
    return std::sqrtf(std::powf(vec.x,2)+std::powf(vec.y,2));;
}

inline float length(const cocos2d::Vec2& vec) {
    return std::sqrtf(std::powf(vec.x,2)+std::powf(vec.y,2));;
}

inline b2Vec2 normalize(b2Vec2& vec) {
    float __l = length(vec);
    if (__l == 0 || __l == 1) return vec;
    vec = b2Vec2(vec.x/__l, vec.y/__l);
    return vec;
}

inline cocos2d::Vec2 normalize(cocos2d::Vec2& vec) {
    float __l = length(vec);
    if (__l == 0 || __l == 1) return vec;
    vec = cocos2d::Vec2(vec.x/__l, vec.y/__l);
    return vec;
}

inline const cocos2d::Vec2 B2C(const b2Vec2 vec) {
    return cocos2d::Vec2(vec.x, vec.y);
}

inline b2Vec2 C2B(const cocos2d::Vec2 vec) {
    return b2Vec2(vec.x, vec.y);
}

inline const float B2C(float angle) {
    return -1 * CC_RADIANS_TO_DEGREES(angle);
}

inline float C2B(float angle) {
    return -1 * CC_DEGREES_TO_RADIANS(angle);
}

inline float VecToDegree(const cocos2d::Vec2& vec) {
    return CC_RADIANS_TO_DEGREES(atan2f(vec.x, vec.y));
}

inline float VecToDegree(const b2Vec2& vec) {
    return CC_RADIANS_TO_DEGREES(atan2f(vec.x, vec.y));
}

template <typename t>
inline void swap(t* first, t* second) {
    t* temp = first;
    first = second;
    second = temp;
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
    
    inline void update(float dt) {
        if (__end) return;
        if (__time > 0) __time -= dt;
        if (__time < 0) __end = true;
    }
    
    inline void reset() {
        set(0.0f);
        if (!__invert) __end = true;
    }
    
    inline void set(float time) {
        __run_time = time;
        __time = time;
        __end = false;
    }
    
    inline float getSetTime() {
        return __run_time;
    }
    
    inline float getLeft() {
        return __time;
    }
    
    inline float getRunTime() {
        return __run_time - __time;
    }
    
    inline bool isEnd() {
        return __end;
    }
    
    inline bool isRunning() {
        return __time > 0;
    }
};

#endif /* __UTILITY_H__ */
