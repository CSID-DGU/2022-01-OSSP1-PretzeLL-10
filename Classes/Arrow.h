#ifndef __ARROW_H__
#define __ARROW_H__

#include "BaseBullet.h"


class Arrow : public BaseBullet {
protected:
    Arrow() : BaseBullet("weapon_arrow") {}
    virtual ~Arrow() {}
    
public:
    CREATE_FUNC(Arrow);
    
//    bool init() final {
//        IF(!BaseBullet::init());
//        return true;
//    }
};

#endif /* __ARROW_H__ */
