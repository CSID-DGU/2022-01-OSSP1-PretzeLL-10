#include "EventHandler.h"


void EventHandler::setup(cocos2d::Layer* layer, Hero* hero) {
    _hero = hero;
    _slot = layer->getChildByName<cocos2d::Layer*>("state_layer")->getChildByName<SlotMachine*>("slot_machine");
    
    auto _event_dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto _keyboard_event = cocos2d::EventListenerKeyboard::create();
    auto _mouse_listener = cocos2d::EventListenerMouse::create();
    
    _keyboard_event->onKeyPressed = CC_CALLBACK_2(EventHandler::onKeyPressed, this);
    _keyboard_event->onKeyReleased = CC_CALLBACK_2(EventHandler::onKeyReleased, this);
    _mouse_listener->onMouseMove = CC_CALLBACK_1(EventHandler::onMouseMove, this);
    _mouse_listener->onMouseUp = CC_CALLBACK_1(EventHandler::onMouseUp, this);
    _mouse_listener->onMouseDown = CC_CALLBACK_1(EventHandler::onMouseDown, this);
    
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_keyboard_event, layer);
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_mouse_listener, layer);
    
    PhysicsObject::getWorld()->SetContactListener(this);
}


void EventHandler::onKeyPressed(keyCode_t key, cocos2d::Event* event) {
    switch (key) {
        case KEY_GROUP_UP           : _hero->move(UP); break;
        case KEY_GROUP_LEFT         : _hero->move(LEFT); break;
        case KEY_GROUP_DOWN         : _hero->move(DOWN); break;
        case KEY_GROUP_RIGHT        : _hero->move(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->run(); break;
        case keyCode_t::KEY_1       : _hero->changeWeapon(1); break;
        case keyCode_t::KEY_2       : _hero->changeWeapon(2); break;
        case keyCode_t::KEY_3       : _hero->changeWeapon(3); break;
                
        case KEY_GROUP_M            : _slot->react(_hero); break;
        case keyCode_t::KEY_ESCAPE  : endProgram(); break;
        case keyCode_t::KEY_N       : test(); break;
        default: _hero->updateKey(ATTACK, true); _hero->attack(); break;
    }
}

void EventHandler::onKeyReleased(keyCode_t key, cocos2d::Event* event) {
    switch (key) {
        case KEY_GROUP_UP           : _hero->stop(UP); break;
        case KEY_GROUP_DOWN         : _hero->stop(DOWN); break;
        case KEY_GROUP_LEFT         : _hero->stop(LEFT); break;
        case KEY_GROUP_RIGHT        : _hero->stop(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->stopRun(); break;
        default: _hero->updateKey(ATTACK, false); _hero->attack(); break;
    }
}

void EventHandler::onMouseUp(cocos2d::EventMouse *event) {
    switch (event->getMouseButton()) {
        case mouseButton_t::BUTTON_LEFT : _hero->updateKey(ATTACK, false); _hero->attack(); break;
        default: break;
    }
}

void EventHandler::onMouseDown(cocos2d::EventMouse *event) {
    switch (event->getMouseButton()) {
        case mouseButton_t::BUTTON_LEFT : _hero->updateKey(ATTACK, true); _hero->attack(); break;
        default: break;
    }
}

void EventHandler::onMouseMove(cocos2d::EventMouse *event) {
    cocos2d::Vec2 pos;
    pos.x = event->getCursorX();
    pos.y = event->getCursorY();
    _hero->updateMouse(pos);
}


void EventHandler::BeginContact(b2Contact* contact) {
    auto fixtureA = contact->GetFixtureA();
    auto fixtureB = contact->GetFixtureB();
    int categoryA = PhysicsObject::getCategory(fixtureA);
    int categoryB = PhysicsObject::getCategory(fixtureB);
  
    INVOKE_CONTACT(CATEGORY_PLAYER, Hero);
    INVOKE_CONTACT(CATEGORY_MONSTER, monster_t);
    INVOKE_CONTACT(CATEGORY_BULLET, bullet_t);
}
    
void EventHandler::EndContact(b2Contact *contact) {
//    auto fixtureA = contact->GetFixtureA();
//    auto fixtureB = contact->GetFixtureB();
//    float categoryA = PhysicsObject::getCategory(fixtureA);
//    float categoryB = PhysicsObject::getCategory(fixtureB);
}


void EventHandler::test() {
    auto monster = BigZombie::create();
    _hero->getParent()->addChild(monster);
    monster->setAbsolutePosition(500, 700);
    monster->setScale(2.0f);
}