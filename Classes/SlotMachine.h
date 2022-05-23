#ifndef __SLOT_H__
#define __SLOT_H__

#include "Utility.h"
#include "Hero.h"
#include "Weapon.h"


class SlotMachine : public cocos2d::Layer {
private:
    typedef Int<3> LayerSize;
    
    std::random_device rand_device;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> rand;
    
    std::vector<cocos2d::Sprite*> weapons;
    cocos2d::ui::Button* laber;
    std::array<cocos2d::Layer*, LayerSize::value> layers;
    std::array<cocos2d::Sprite*, LayerSize::value> result;
    
    int lineSize[LayerSize::value] = { 20, 30, 40 };
    bool running;
    
private:
    SlotMachine();
    ~SlotMachine();
    
public:
    bool init() final;
    void update(float dt) final;
    bool isRunning() const final;
    void spin(Ref* pSender);
    
    void react(Hero* hero);
    void disappear();
    void appear();
    
    bool createWeapon(const std::string& name, int tag);
    void createLine(int line);
    void createItem();
    
    std::vector<weapon_t*> getResult();
    
    CREATE_FUNC(SlotMachine);
};

#endif /* __SLOT_H__ */
