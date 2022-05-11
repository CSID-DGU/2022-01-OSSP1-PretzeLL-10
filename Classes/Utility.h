#ifndef __UTILITY_H__
#define __UTILITY_H__


#define PTM_RATIO                       64
#define PHYSICS_BODY_WIDTH              0.3f
#define PHYSICS_BODY_HEIGHT             0.3f

//#define DIR_MOUSE

#define BITMASK_ALL                     0xff
#define BITMASK_PLAYER                  0x01
#define BITMASK_MONSTER                 0x02
#define BITMASK_WALL                    0x04


#define PIXEL_FONT                      "fonts/pixel_font.ttf"
#define FONT_SCALE                      8.0f

#define TEX_PARA                        {GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE}


#include <memory>
#include <map>
#include <vector>
#include <array>
#include <cmath>

#include "cocos2d.h"
#include "Debug.h"
#include "Box2D/Box2D.h"
#include "B2DebugDrawLayer.h"


static float aspect = 3.0f/4.0f;
static cocos2d::Size absoluteResolution = cocos2d::Size(1000, 1000);
#ifdef __APPLE__
static cocos2d::Size resolution = cocos2d::Size(1280, 1280*aspect);
#else
static cocos2d::Size resolution = cocos2d::Size(1280, 1280*aspect);
#endif
static cocos2d::Size designResolution = cocos2d::Size(640, 640*aspect);
static float scaleFactor = designResolution.width/resolution.width;


static void endProgram() {
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
