#ifndef __DEFINITION_H__
#define __DEFINITION_H__

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

#define SLOT_SPIN                       1


enum ACTION {
    IDLE = 0,
    MOVE,
    RUN,
    ELSE
};

enum KEY {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    SHIFT,
    ALL
};


static float aspect = 3.0f/4.0f;
static cocos2d::Size absoluteResolution = cocos2d::Size(1000, 1000);
#ifdef __APPLE__
static cocos2d::Size resolution = cocos2d::Size(1280, 1280*aspect);
#else
static cocos2d::Size resolution = cocos2d::Size(1280, 1280*aspect);
#endif
static cocos2d::Size designResolution = cocos2d::Size(640, 640*aspect);
static float scaleFactor = designResolution.width/resolution.width;

#endif /* __DEFINITION_H__ */
