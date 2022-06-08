#ifndef __STONE_H__
#define __STONE_H__

#include "BaseBullet.h"


class Stone : public BaseBullet {
protected:
    Stone() : BaseBullet("stone") {}
    virtual ~Stone() {}
    
public:
    CREATE_FUNC(Stone);
    
    void onContact(b2Contact* contact) {
        removeAfter(0.0f);
    }
};

#endif /* __STONE_H__ */
