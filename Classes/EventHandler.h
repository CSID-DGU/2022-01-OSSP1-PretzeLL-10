#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "Utility.h"
#include "Object.h"

#define INVOKE_CONTACT(bit, type) \
if      (categoryA == bit) PhysicsObject::getUserData<type*>(fixtureA)->onContact(contact); \
else if (categoryB == bit) PhysicsObject::getUserData<type*>(fixtureB)->onContact(contact);

#define INVOKE_CONTACTEND(bit, type) \
if      (categoryA == bit) PhysicsObject::getUserData<type*>(fixtureA)->onContactEnd(contact); \
else if (categoryB == bit) PhysicsObject::getUserData<type*>(fixtureB)->onContactEnd(contact);

#define PASS_CONTACT(bit) \
if (categoryA | categoryB || bit) return;


class EventHandler : public cocos2d::Node, public b2ContactListener {
private:
    cocos2d::EventDispatcher* _event_dispatcher;
    cocos2d::EventListenerKeyboard* _keyboard_event;
    cocos2d::EventListenerMouse* _mouse_listener;
    
    SlotMachine* _slot;
    Hero* _hero;
    
public:
    EventHandler();
    virtual ~EventHandler();
    
    CREATE_FUNC(EventHandler);
    
    void getHero();
    void setup(cocos2d::Layer* layer);
    
    void onKeyPressed(keyCode_t key, cocos2d::Event* event);
    void onKeyReleased(keyCode_t key, cocos2d::Event* event);
    void onMouseUp(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
    
    void BeginContact(b2Contact* contact) final;
    void EndContact(b2Contact* contact) final;
    
//    void test();
};

#endif /* __EVENT_HANDLER_H__ */
