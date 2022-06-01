#ifndef __STONE_H__
#define __STONE_H__

#include "BaseBullet.h"


class Stone : public BaseBullet {
protected:
    Stone() : BaseBullet("stone") {}
    virtual ~Stone() {}
    
public:
    CREATE_FUNC(Stone);
};

#endif /* __STONE_H__ */
