#ifndef __SLOT_H__
#define __SLOT_H__

#include "Utility.h"
#include "SpriteManager.h"


class SlotMachine : public cocos2d::Layer {
private:
    std::random_device rand_device;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> rand;
    
    std::vector<cocos2d::Sprite*> weapon;
    std::array<cocos2d::Sprite*, 3> current;
    std::array<cocos2d::Sprite*, 3> next;
    cocos2d::ui::Button* laber;
    
    bool spinning;
    bool moving;
    float timer;
    float spin_time;
    
protected:
    SlotMachine();
    ~SlotMachine();
    
public:
    bool init() final;
    void update(float dt) final;
    void laberCallback(Ref* pSender);
    
    void spin();
    void disappear();
    void appear();
    
    bool createWeapon(const std::string& file);
    void createItem(bool future);
    
    CREATE_FUNC(SlotMachine);
};

#endif /* __SLOT_H__ */
