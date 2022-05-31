#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#define PTM_RATIO                       64
#define PHYSICS_BODY_WIDTH              0.5f
#define PHYSICS_BODY_HEIGHT             0.5f
#define WALL_LAYER                      "MetaInfo"

#define CATEGORY_PLAYER                 0x0001
#define CATEGORY_MONSTER                0x0002
#define CATEGORY_WALL                   0x0004
#define CATEGORY_ITEM                   0x0008
#define CATEGORY_WEAPON                 0x0010
#define CATEGORY_BULLET                 0x0020

#define MASK_NONE                       0x0000
#define MASK_ALL                        0xFFFF
#define MASK_PLAYER                     CATEGORY_MONSTER | CATEGORY_WALL
#define MASK_MONSTER                    CATEGORY_PLAYER  | CATEGORY_WALL | CATEGORY_BULLET | CATEGORY_WEAPON
#define MASK_WALL                       CATEGORY_PLAYER  | CATEGORY_MONSTER | CATEGORY_BULLET
#define MASK_BULLET                     CATEGORY_WALL | CATEGORY_MONSTER
#define MASK_WEAPON                     CATEGORY_MONSTER
#define MASK_ITEM                       MASK_NONE

#define PIXEL_FONT                      "fonts/pixel_font.ttf"
#define FONT_SCALE                      8.0f
#define TEX_PARA                        {GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE}

#define SLOT_SPIN                       1

#define KEY_GROUP_UP                    keyCode_t::KEY_W: case keyCode_t::KEY_CAPITAL_W: case keyCode_t::KEY_UP_ARROW
#define KEY_GROUP_LEFT                  keyCode_t::KEY_A: case keyCode_t::KEY_CAPITAL_A: case keyCode_t::KEY_LEFT_ARROW
#define KEY_GROUP_DOWN                  keyCode_t::KEY_S: case keyCode_t::KEY_CAPITAL_S: case keyCode_t::KEY_DOWN_ARROW
#define KEY_GROUP_RIGHT                 keyCode_t::KEY_D: case keyCode_t::KEY_CAPITAL_D: case keyCode_t::KEY_RIGHT_ARROW
#define KEY_GROUP_SHIFT                 keyCode_t::KEY_SHIFT: case keyCode_t::KEY_RIGHT_SHIFT
#define KEY_GROUP_M                     keyCode_t::KEY_M: case keyCode_t::KEY_CAPITAL_M

#define TAG_PLAYER                      0x1000

#ifndef __KEYCODE_T__
#define __KEYCODE_T__
typedef cocos2d::EventKeyboard::KeyCode keyCode_t;
typedef cocos2d::EventMouse::MouseButton mouseButton_t;
#endif


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
    ATTACK,
    ALL
};

enum WEAPON {
    IMMEDIATE,
    CHARGE
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
