#ifndef __SKULL_H__
#define __SKULL_H__

#include "BaseBullet.h"


class Skull : public BaseBullet {
protected:
    Skull() : BaseBullet("skull") {}
    virtual ~Skull() {}

public:
    CREATE_FUNC(Skull);

    void onContact(b2Contact* contact) {
        removeAfter(0.0f);
    }
};

#endif /* __SKULL_H__ */