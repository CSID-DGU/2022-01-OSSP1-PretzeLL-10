#ifndef __RED_SHIEDL_H__
#define __RED_SHIEDL_H__

#include "BaseBullet.h"


class RedShield : public BaseBullet {
protected:
    RedShield() : BaseBullet("red_shield") {}
    virtual ~RedShield() {}

public:
    CREATE_FUNC(RedShield);

    void onContact(b2Contact* contact) {
        removeAfter(0.0f);
    }
};

#endif /* __RED_SHIEDL_H__ */