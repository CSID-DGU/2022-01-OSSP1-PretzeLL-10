#ifndef __SLOT_H__
#define __SLOT_H__

#include "Utility.h"
#include "Hero.h"
#include "Weapon.h"


class SlotMachine : public cocos2d::Node {
private:
    typedef Int<3> LayerSize;
    
    std::random_device rand_device;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> rand;
    
    std::vector<cocos2d::Sprite*> weapons;
    std::array<cocos2d::Layer*, LayerSize::value> layers;
    std::array<cocos2d::Sprite*, LayerSize::value> result;
    
    Hero* _hero;
    float _hero_speed;
    
    static int counter;
    int lineSize[LayerSize::value] = { 15, 20, 25 };
    bool running;
    
private:
    SlotMachine();
    ~SlotMachine();
    
public:
    bool init() final;
    void update(float dt) final;
    bool isRunning() const final;
    void spin(Hero* hero);
    void stopSpin(int line);
    void stopAllSpin();
    
    void react(Hero* hero);
//    void disappear();                                                     // deprecated
//    void appear();
    
    template <typename T>
    bool createWeapon(const std::string& name);
    void createLine(int line);
    void createItem();
    
    std::vector<weapon_t*> getResult();
    
    CREATE_FUNC(SlotMachine);
};

#endif /* __SLOT_H__ */
