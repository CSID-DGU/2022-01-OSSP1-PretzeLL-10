#include "Weapon.h"


weapon_t* getWeapon(const int tag) {
    switch (tag) {
        case WEAPON_ANIMESWORD      : return AnimeSword::create();
        case WEAPON_BOW             : return Bow::create();
        case WEAPON_AXE             : return Axe::create();
        case WEAPON_BATONWITHSPIKES : return BatonWithSpikes::create();
        case WEAPON_BIGHAMMER       : return BigHammer::create();
        case WEAPON_CLEAVER         : return Cleaver::create();
        case WEAPON_DUELSWORD       : return DuelSword::create();
        case WEAPON_KATANA          : return Katana::create();
        case WEAPON_HAMMER          : return Hammer::create();
        case WEAPON_KNIFE           : return Knife::create();
        case WEAPON_MACHETE         : return Machete::create();
        default: return nullptr;
    }
}

