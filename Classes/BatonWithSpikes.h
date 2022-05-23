#ifndef __BATON_WITH_SPIKES_H__
#define __BATON_WITH_SPIKES_H__

#include "BaseWeapon.h"


class BatonWithSpikes : public BaseWeapon {
protected:
    BatonWithSpikes() : BaseWeapon("baton_with_spikes") {}
    virtual ~BatonWithSpikes() {}
    
public:
    CREATE_FUNC(BatonWithSpikes);
    
//    void attack() final {
//        
//    }
};

#endif /* __BATON_WITH_SPIKES_H__ */
