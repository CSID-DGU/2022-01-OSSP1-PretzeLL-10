#ifndef __BIG_STONE_H__
#define __BIG_STONE_H__

#include "BaseBullet.h"


class BigStone : public BaseBullet {
protected:
    BigStone() : BaseBullet("big_stone") {}
    virtual ~BigStone() {}

public:
    CREATE_FUNC(BigStone);

    void onContact(b2Contact* contact) {
        removeAfter(0.0f);
    }
};

#endif /* __BIG_STONE_H__ */