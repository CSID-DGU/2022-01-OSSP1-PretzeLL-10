#include "SlotMachine.h"


SlotMachine::SlotMachine() {
    running = false;
    result.fill(nullptr);
}

SlotMachine::~SlotMachine() {
    for (auto iter : weapons) iter->release();
}


bool SlotMachine::init() {
    /* Super init */
    IF(!Layer::init());
    
    /* Init weapons */
    IF(!createWeapon("frames/weapon_anime_sword.png", WEAPON_ANIMESWORD));
    IF(!createWeapon("frames/weapon_bow.png", WEAPON_BOW));
//    IF(!createWeapon("frames/weapon_arrow.png"));
    IF(!createWeapon("frames/weapon_axe.png", WEAPON_AXE));
    IF(!createWeapon("frames/weapon_baton_with_spikes.png", WEAPON_BATONWITHSPIKES))
    IF(!createWeapon("frames/weapon_big_hammer.png", WEAPON_BIGHAMMER))
    IF(!createWeapon("frames/weapon_cleaver.png", WEAPON_CLEAVER));
    IF(!createWeapon("frames/weapon_duel_sword.png", WEAPON_DUELSWORD));
    IF(!createWeapon("frames/weapon_katana.png", WEAPON_KATANA));
    IF(!createWeapon("frames/weapon_hammer.png", WEAPON_HAMMER));
    IF(!createWeapon("frames/weapon_knife.png", WEAPON_KNIFE));
    IF(!createWeapon("frames/weapon_machete.png", WEAPON_MACHETE));
//    IF(!createWeapon("frames/weapon_golden_sword.png"));
//    IF(!createWeapon("frames/weapon_green_magic_staff.png"));
//    IF(!createWeapon("frames/weapon_knight_sword.png"));
//    IF(!createWeapon("frames/weapon_lavish_sword.png"));
//    IF(!createWeapon("frames/weapon_mace.png"));
//    IF(!createWeapon("frames/weapon_red_gem_sword.png"));
//    IF(!createWeapon("frames/weapon_red_magic_staff.png"));
//    IF(!createWeapon("frames/weapon_regular_sword.png"));
//    IF(!createWeapon("frames/weapon_rusty_sword.png"));
//    IF(!createWeapon("frames/weapon_saw_sword.png"));
//    IF(!createWeapon("frames/weapon_spear.png"));
    
    /* Init background */
    auto sprite = cocos2d::Sprite::create("sprite/slot_test.png");
    IF(!sprite);
    sprite->setScale(10.0f);
    addChild(sprite, 0);
        
    /* Init laber */
#if COCOS2D_DEBUG > 0
    laber = cocos2d::ui::Button::create("sprite/button_debug.png");
#else
    laber = cocos2d::ui::Button::create();
#endif
    IF(!laber);
    laber->addClickEventListener(CC_CALLBACK_1(SlotMachine::spin, this));
    laber->setScale(0.06f);
    laber->setAnchorPoint(cocos2d::Vec2(-3.8f, -1.8f));
    addChild(laber, 2);
    
    /* Init random generator */
    engine = std::mt19937_64(rand_device());
    rand = std::uniform_int_distribution<int>(0, weapons.size()-1);
    
    /* Init clipper */
    auto size = cocos2d::Size(600.0f, 250.0f);
    auto pos = cocos2d::Vec2(-250.0f, -150.0f);
    auto rect = cocos2d::Rect(pos, size);
    auto clipper = cocos2d::ClippingRectangleNode::create(rect);
    IF(!clipper);
    addChild(clipper);

    /* Init lines */
    for (int i = 0; i < LayerSize::value; i++) {
        layers[i] = cocos2d::Layer::create();
        IF(!layers[i]);
        layers[i]->setPosition((i-1)*200.0f, 0.0f);
        clipper->addChild(layers[i]);
    }
    
    /* Few things left... */
    createItem();
    setPosition(0.0f, -500.0f);

    return true;
}

void SlotMachine::update(float dt) {
    for (int i = 0; i < LayerSize::value; i++) {
        auto action = (cocos2d::Speed*)layers[i]->getActionByTag(SLOT_SPIN);
        if (action) {
            float speed = action->getSpeed();
            if (speed < 50.0f) action->setSpeed(action->getSpeed()+1.0f);
        }
        
        if (layers[i]->getPositionY() < -(lineSize[i]-1)*200.0f) {
            layers[i]->stopAllActions();
            layers[i]->removeAllChildren();
            layers[i]->addChild(result[i]);
            result[i]->release();
            layers[i]->setPosition((i-1)*200.0f, 0.0f);
            if (i == LayerSize::value - 1) {
                unscheduleUpdate();
                laber->setEnabled(true);
            }
        }
    }
}

void SlotMachine::spin(Ref* pSender) {
    for (int i = 0; i < 3; i++) {
        createLine(i);
        auto pos = cocos2d::Vec2(0.0f, -lineSize[LayerSize::value-1]*200.0f);
        auto action = cocos2d::MoveBy::create(100.0f, pos);
        auto speed = cocos2d::Speed::create(action, 1.0f);
        speed->setTag(SLOT_SPIN);
        layers[i]->runAction(speed);
    }
    scheduleUpdate();
    laber->setEnabled(false);
}

bool SlotMachine::isRunning() const {
    return running;
}


void SlotMachine::createItem() {
    for (int i = 0; i < LayerSize::value; i++) {
        int rand_int = rand(engine);
        auto texture = weapons[rand_int]->getTexture();
        auto sprite = cocos2d::Sprite::createWithTexture(texture);
        
        sprite->setScale(2.0f);
        sprite->setTag(weapons[rand_int]->getTag());
        layers[i]->addChild(sprite);
    }
}

void SlotMachine::createLine(int line) {
    cocos2d::Sprite* sprite;
    for (int i = 1; i < lineSize[line]; i++) {
        int rand_int = rand(engine);
        cocos2d::Vec2 pos(0.0f, i*200.0f);
        auto texture = weapons[rand_int]->getTexture();
        sprite = cocos2d::Sprite::createWithTexture(texture);

        sprite->setScale(2.0f);
        sprite->setTag(weapons[rand_int]->getTag());
        sprite->setPosition(pos);
        layers[line]->addChild(sprite);
    }
    
    result[line] = cocos2d::Sprite::createWithTexture(sprite->getTexture());
    IF_RV(!result[line], "Failed to create Sprite");
    result[line]->setTag(sprite->getTag());
    result[line]->setScale(2.0f);
    result[line]->retain();
}

bool SlotMachine::createWeapon(const std::string& file, int tag) {
    auto sprite = cocos2d::Sprite::create(file);
    IF(!sprite);
    sprite->getTexture()->setTexParameters(TEX_PARA);
    sprite->retain();
    sprite->setTag(tag);
    weapons.push_back(sprite);
    return true;
}


void SlotMachine::react(Hero* hero) {
    if (running) {
        disappear();
        hero->setWeapon(getResult());
    }
    else appear();
}

void SlotMachine::disappear() {
    float desired_time = 0.3f;
    float calculated_time = desired_time * (getPositionY() + 500.0f) / 500.0f;
//    auto jump = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(0.0f, 50.0f));
    auto dig = cocos2d::MoveTo::create(calculated_time, cocos2d::Vec2(0.0f, -500.0f));
//    auto action = cocos2d::Sequence::createWithTwoActions(jump, dig);

    stopAllActions();
    runAction(dig);
    laber->setEnabled(false);
    running = false;
}

void SlotMachine::appear() {
    float desired_time = 0.3f;
    float calculated_time = desired_time * (0.0f - getPositionY()) / 500.0f;
    auto pop = cocos2d::MoveTo::create(calculated_time, cocos2d::Vec2(0.0f, 0.0f));
//    auto ret = cocos2d::MoveBy::create(0.05f, cocos2d::Vec2(0.0f, -50.0f));
//    auto action = cocos2d::Sequence::createWithTwoActions(pop, ret);
    
    laber->setEnabled(true);
    stopAllActions();
    runAction(pop);
    running = true;
}


std::vector<weapon_t*> SlotMachine::getResult() {
    std::vector<weapon_t*> ret(LayerSize::value);
    for (int i = 0; i < LayerSize::value; i++) {
        if (!result[i]) {
            ret[i] = nullptr;
            continue;
        }
        ret[i] = getWeapon(result[i]->getTag());
        ret[i]->deactivate();
    }
    return ret;
}
