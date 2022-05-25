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
    
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_keyboard_event, layer);
    _event_dispatcher->addEventListenerWithSceneGraphPriority(_mouse_listener, layer);
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
        case keyCode_t::KEY_ENTER   : _hero->attack(); break;
                
        case KEY_GROUP_M            : _slot->react(_hero); break;
        case keyCode_t::KEY_ESCAPE  : endProgram(); break;
        default: break;
    }
}

void EventHandler::onKeyReleased(keyCode_t key, cocos2d::Event* event) {
    switch (key) {
        case KEY_GROUP_UP           : _hero->stop(UP); break;
        case KEY_GROUP_DOWN         : _hero->stop(DOWN); break;
        case KEY_GROUP_LEFT         : _hero->stop(LEFT); break;
        case KEY_GROUP_RIGHT        : _hero->stop(RIGHT); break;
        case KEY_GROUP_SHIFT        : _hero->stopRun(); break;
        case keyCode_t::KEY_ENTER   : _hero->attack(); break;
        default: break;
    }
}

void EventHandler::onMouseUp(cocos2d::EventMouse *event) {
    
}

void EventHandler::onMouseDown(cocos2d::EventMouse *event) {
    
}

void EventHandler::onMouseMove(cocos2d::EventMouse *event) {
    cocos2d::Vec2 pos;
    pos.x = event->getCursorX();
    pos.y = event->getCursorY();
    _hero->updateMouse(pos);
}
