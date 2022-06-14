#ifndef __POISON_FLASK_H__
#define __POISON_FLASK_H__

#include "BaseBullet.h"


class Poison : public BaseBullet {
protected:
    Poison() : BaseBullet("flask_big_green") {}
    virtual ~Poison() {}

public:
    CREATE_FUNC(Poison);

    void onContact(b2Contact* contact) {
        removeAfter(0.0f);
    }
};

#endif /* __POISON_FLASK_H__ */