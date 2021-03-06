#ifndef __LIGHTNIGSTAFF_H__
#define __LIGHTNIGSTAFF_H__

#include "Bow.h"
#include "Axe.h"
#include "BigHammer.h"
#include "FireStaff.h"
#include "Knife.h"
#include "Machete.h"


class LightningStaff : public BaseWeapon
{
private:
    std::random_device rand_device;
    std::mt19937_64 engine;
    std::uniform_int_distribution<int> rand;
    int __current;
    
protected:
	LightningStaff() : BaseWeapon("green_magic_staff") {}
	virtual ~LightningStaff() {}

public:
	CREATE_FUNC(LightningStaff);
    
    bool init() final {
        IF(!BaseWeapon::init());
        setLevelValue(1, 0, 0.0f, 0.3f);
        setLevelValue(2, 0, 0.0f, 0.3f);
        setLevelValue(3, 0, 0.0f, 0.3f);
        engine = std::mt19937_64(rand_device());
        rand = std::uniform_int_distribution<int>(0, 5);
        return true;
    }

	void attack(bool flipped, const b2Vec2& direction) final {
        if (__fire_key) {
            __current = rand(engine);
            switch (__current) {
                case 0: getLevelValue<Bow>();       break;
                case 1: getLevelValue<Axe>();       break;
                case 2: getLevelValue<Knife>();     break;
                case 3: getLevelValue<Machete>();   break;
                case 4: getLevelValue<BigHammer>(); break;
                case 5: getLevelValue<FireStaff>(); break;
            }
        }
        
        switch (__current) {
            case 0: ((Bow*)      this)->attack(flipped, direction); break;
            case 1: ((Axe*)      this)->attack(flipped, direction); break;
            case 2: ((Knife*)    this)->attack(flipped, direction); break;
            case 3: ((Machete*)  this)->attack(flipped, direction); break;
            case 4: ((BigHammer*)this)->attack(flipped, direction); break;
            case 5: ((FireStaff*)this)->attack(flipped, direction); break;
        }
	}
    
    template <typename weapon_type>
    void getLevelValue() {
        auto weapon = weapon_type::create();
        auto level_value = weapon->getLevelValue();
        __damage = level_value[0];
        __attackTime = level_value[1];
    }
};

#endif /* __LIGHTNIGSTAFF_H__ */
