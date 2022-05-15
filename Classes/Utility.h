#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <memory>
#include <map>
#include <vector>
#include <array>
#include <cmath>
#include <random>

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Debug.h"
#include "Definition.h"
#include "Box2D/Box2D.h"
#include "B2DebugDrawLayer.h"


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

static inline const cocos2d::Vec2 b2c(const b2Vec2 vec) {
    return cocos2d::Vec2(vec.x, vec.y);
}

static inline const b2Vec2 c2b(const cocos2d::Vec2 vec) {
    return b2Vec2(vec.x, vec.y);
}

#endif /* __UTILITY_H__ */
