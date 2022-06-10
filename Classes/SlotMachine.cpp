#include "SlotMachine.h"
#include "GameManager.h"


SlotMachine::SlotMachine() {
    running = false;
    result.fill(nullptr);
}

SlotMachine::~SlotMachine() {
    for (auto iter : weapons) iter->release();
}

int SlotMachine::counter = 0;


bool SlotMachine::init() {
    /* Super init */
    IF(!Node::init());
    
    /* Init weapons */
    IF(!createWeapon<Bow>("bow"));
    IF(!createWeapon<Axe>("axe"));
    IF(!createWeapon<FireStaff>("red_magic_staff"));
    IF(!createWeapon<LightningStaff>("green_magic_staff"));
    IF(!createWeapon<Knife>("knife"));
    IF(!createWeapon<Machete>("machete"));
    IF(!createWeapon<BigHammer>("big_hammer"));
    
    /* Deprecated */
    // IF(!createWeapon<BatonWithSpikes>("baton_with_spikes"));
    // IF(!createWeapon<Cleaver>("cleaver"));
    // IF(!createWeapon<DuelSword>("duel_sword"));
    // IF(!createWeapon<Katana>("katana"));
    // IF(!createWeapon<Hammer>("hammer"));
    // IF(!createWeapon<FireStaff>("red_magic_staff"));
    // IF(!createWeapon<AnimeSword>("anime_sword"));
    // IF(!createWeapon("frames/weapon_arrow.png"));
    // IF(!createWeapon("frames/weapon_golden_sword.png"));
    // IF(!createWeapon("frames/weapon_green_magic_staff.png"));
    // IF(!createWeapon("frames/weapon_knight_sword.png"));
    // IF(!createWeapon("frames/weapon_lavish_sword.png"));
    // IF(!createWeapon("frames/weapon_mace.png"));
    // IF(!createWeapon("frames/weapon_red_gem_sword.png"));
    // IF(!createWeapon("frames/weapon_regular_sword.png"));
    // IF(!createWeapon("frames/weapon_rusty_sword.png"));
    // IF(!createWeapon("frames/weapon_saw_sword.png"));
    // IF(!createWeapon("frames/weapon_spear.png"));
    
    /* Init background */
    auto sprite = cocos2d::Sprite::create("sprite/slotmachineStyle.png");
    IF(!sprite);
    addChild(sprite, 0);
    
    /* Init random generator */
    engine = std::mt19937_64(rand_device());
    rand = std::uniform_int_distribution<int>(0, weapons.size()-1);
    
    /* Init clipper */
    auto size = cocos2d::Size(600.0f, 200.0f);
    auto pos = cocos2d::Vec2(-250.0f, -100.0f);
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
    setPosition(640.0f, 100.0f);
    setScale(0.5f);
    setName("slot_machine");
        
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
            stopSpin(i);
            if (i == LayerSize::value - 1) {
                unscheduleUpdate();
                react(_hero);
                _hero->rearm(0);
                running = false;
//                _hero->restoreSpeed();
            }
        }
    }
}

void SlotMachine::spin(Hero* hero) {
    if (running) {
        for (int i = 0; i < 3; i++) {
            stopSpin(i);
            unscheduleUpdate();
        }
    }
    if (!hero->useCoin(1)) return;
    if (GameManager::getInstance()->isPausedByUser) return;
    else cocos2d::Director::getInstance()->resume();
    
    for (int i = 0; i < 3; i++) {
        createLine(i);
        auto pos = cocos2d::Vec2(0.0f, -lineSize[LayerSize::value-1]*200.0f);
        auto action = cocos2d::MoveBy::create(100.0f, pos);
        auto speed = cocos2d::Speed::create(action, 1.0f);
        speed->setTag(SLOT_SPIN);
        layers[i]->runAction(speed);
    }
    scheduleUpdate();
    _hero = hero;
    _hero->disarm();
    running = true;
//    _hero_speed = hero->getSpeed();
//    _hero->setSpeed(_hero_speed*0.25f);
}

void SlotMachine::stopSpin(int line) {
    if (!result[line]) return;
    if (layers[line]->getChildrenCount() != lineSize[line]) return;
    layers[line]->stopAllActions();
    layers[line]->removeAllChildren();
    layers[line]->addChild(result[line]);
    result[line]->release();
    layers[line]->setPosition((line-1)*200.0f, 0.0f);
}

void SlotMachine::stopAllSpin() {
    for (int i = 0; i < LayerSize::value; i++) {
        stopSpin(i);
    }
    unscheduleUpdate();
}

bool SlotMachine::isRunning() const {
    return running;
}


void SlotMachine::createItem() {
    for (int i = 0; i < LayerSize::value; i++) {
        int rand_int = rand(engine);
        auto texture = weapons[rand_int]->getTexture();
        auto sprite = cocos2d::Sprite::createWithTexture(texture);
        
        sprite->setScale(1.75f);
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

template <typename T>
bool SlotMachine::createWeapon(const std::string& file) {
    std::string fullpath = "frames/weapon_" + file + ".png";
    counter++;
    
    auto sprite = cocos2d::Sprite::create(fullpath);
    IF(!sprite);
    sprite->getTexture()->setTexParameters(TEX_PARA);
    sprite->retain();
    sprite->setTag(counter);
    weapons.push_back(sprite);
    
    BaseWeapon::insertCreateFunc(counter, T::create);
    return true;
}


void SlotMachine::react(Hero* hero) {
    hero->setWeapon(getResult());
//    if (running) {
//        disappear();
//        hero->setWeapon(getResult());
//    }
//    else appear();
}

//void SlotMachine::disappear() {
//    float desired_time = 0.3f;
//    float calculated_time = desired_time * (getPositionY() + 500.0f) / 500.0f;
//    auto dig = cocos2d::MoveTo::create(calculated_time, cocos2d::Vec2(640.0f, -500.0f));
//
//    stopAllActions();
//    runAction(dig);
//    laber->setEnabled(false);
//    running = false;
//}

//void SlotMachine::appear() {
//    float desired_time = 0.3f;
//    float calculated_time = desired_time * (0.0f - getPositionY()) / 500.0f;
//    auto pop = cocos2d::MoveTo::create(calculated_time, cocos2d::Vec2(640.0f, 200.0f));
//
//    stopAllSpin();
//    laber->setEnabled(true);
//    stopAllActions();
//    runAction(pop);
//    running = true;
//}


std::vector<weapon_t*> SlotMachine::getResult() {
    std::vector<weapon_t*> ret(LayerSize::value);
    int tag[LayerSize::value];
    
    for (int i = 0; i < LayerSize::value; i++) {
        if (!result[i]) {
            ret[i] = nullptr;
            continue;
        }
        tag[i] = result[i]->getTag();
        ret[i] = BaseWeapon::getByTag(tag[i]);
        ret[i]->deactivate();
    }
    
    if (tag[0] == tag[1] == tag[2]) {
        ret[0]->setLevel(2);
        ret[1]->setLevel(2);
        ret[2]->setLevel(2);
    }
    else if (tag[0] == tag[1]) {
        ret[0]->setLevel(1);
        ret[1]->setLevel(1);
    }
    else if (tag[0] == tag[2]) {
        ret[0]->setLevel(1);
        ret[2]->setLevel(1);
    }
    else if (tag[1] == tag[2]) {
        ret[1]->setLevel(1);
        ret[2]->setLevel(1);
    }
    return ret;
}
