#include "SlotMachine.h"


SlotMachine::SlotMachine() {
    spinning = false;
    moving = false;
    timer = 0.0f;
    spin_time = 1.0f;
}

SlotMachine::~SlotMachine() {
    for (auto iter : weapon) iter->release();
    for (int i = 0; i < 3; i++) {
        current[i]->removeFromParent();
        next[i]->removeFromParent();
        post[i]->removeFromParent();
    }
}


bool SlotMachine::init() {
    IF(!Layer::init());
    
    IF(!createWeapon("frames/weapon_anime_sword.png"));
    IF(!createWeapon("frames/weapon_arrow.png"));
    IF(!createWeapon("frames/weapon_axe.png"));
    IF(!createWeapon("frames/weapon_baton_with_spikes.png"))
    IF(!createWeapon("frames/weapon_big_hammer.png"))
    IF(!createWeapon("frames/weapon_bow.png"));
    IF(!createWeapon("frames/weapon_cleaver.png"));
    IF(!createWeapon("frames/weapon_duel_sword.png"));
    IF(!createWeapon("frames/weapon_golden_sword.png"));
    IF(!createWeapon("frames/weapon_green_magic_staff.png"));
    IF(!createWeapon("frames/weapon_hammer.png"));
    IF(!createWeapon("frames/weapon_katana.png"));
    IF(!createWeapon("frames/weapon_knife.png"));
    IF(!createWeapon("frames/weapon_knight_sword.png"));
    IF(!createWeapon("frames/weapon_lavish_sword.png"));
    IF(!createWeapon("frames/weapon_mace.png"));
    IF(!createWeapon("frames/weapon_machete.png"));
    IF(!createWeapon("frames/weapon_red_gem_sword.png"));
    IF(!createWeapon("frames/weapon_red_magic_staff.png"));
    IF(!createWeapon("frames/weapon_regular_sword.png"));
    IF(!createWeapon("frames/weapon_rusty_sword.png"));
    IF(!createWeapon("frames/weapon_saw_sword.png"));
    IF(!createWeapon("frames/weapon_spear.png"));
    
    auto sprite = cocos2d::Sprite::create("sprite/slot_test.png");
    IF(!sprite);
    sprite->setScale(10.0f);
    sprite->setLocalZOrder(0);
    addChild(sprite);
        
#if COCOS2D_DEBUG > 0
    laber = cocos2d::ui::Button::create("sprite/button_debug.png");
    laber->setLocalZOrder(2);
#else
    laber = cocos2d::ui::Button::create();
#endif
    IF(!laber);
    laber->addClickEventListener(CC_CALLBACK_1(SlotMachine::laberCallback, this));
    laber->setScale(0.06f);
    laber->setAnchorPoint(cocos2d::Vec2(-3.8f, -1.8f));
    addChild(laber);
    
    engine = std::mt19937_64(rand_device());
    rand = std::uniform_int_distribution<int>(0, weapon.size()-1);
    
    createItem(0);
    createItem(1);
    createItem(2);
    scheduleUpdate();

    return true;
}

void SlotMachine::update(float dt) {
    if (timer > spin_time) {
        spinning = false;
        laber->setEnabled(true);
        timer = 0.0f;
    }
        
    if (spinning) {
        spin();
        timer += dt;
    }
}

void SlotMachine::laberCallback(Ref* pSender) {
    spinning = true;
    laber->setEnabled(false);
}


void SlotMachine::createItem(int buffer) {
    for (int i = 0; i < 3; i++) {
        int rand_int = rand(engine);
        cocos2d::Vec2 pos((i-1)*200.0f, -30.0f);
        pos.y += 200.0f * buffer;
//       rand_int = current[i]->getTag()+1;                                // this option makes result predictable
//       if (rand_int > 4) rand_int = 0;
        
        auto texture = weapon[rand_int]->getTexture();
        auto sprite = cocos2d::Sprite::createWithTexture(texture);
        sprite->setScale(2.0f);
        sprite->setTag(rand_int);
        sprite->setPosition(pos);
        addChild(sprite);
        
        switch (buffer) {
            case 0: current[i] = sprite; break;
            case 1: next[i] = sprite; break;
            case 2: post[i] = sprite; break;
            default: break;
        }
    }
}


bool SlotMachine::createWeapon(const std::string& file) {
    auto sprite = cocos2d::Sprite::create(file);
    IF(!sprite);
    sprite->getTexture()->setTexParameters(TEX_PARA);
    sprite->retain();
    weapon.push_back(sprite);
    return true;
}


void SlotMachine::disappear() {
    setVisible(false);
    laber->setEnabled(false);
    _running = false;
}

void SlotMachine::appear() {
    setVisible(true);
    laber->setEnabled(true);
    _running = true;
}

void SlotMachine::spin() {
    if (!moving) {
        for (int i = 0; i < 3; i++) {
            auto pos = cocos2d::Vec2(0.0f, -211.0f);
            auto action = cocos2d::MoveBy::create(0.05f, pos);
            current[i]->runAction(action);
            next[i]->runAction(action->clone());
            post[i]->runAction(action->clone());
        }
        moving = true;
    }
    else {
        if (current[0]->getPosition().y < -240.0f) {
            for (int i = 0; i < 3; i++) {
                current[i]->removeFromParent();
                current[i] = next[i];
                next[i] = post[i];
            }
            createItem(2);
            moving = false;
        }
    }
}

std::array<cocos2d::Sprite*, 3> SlotMachine::getItem() {
    if (current[0]->getPosition().y > -100.0f) return current;
    else return next;
}
