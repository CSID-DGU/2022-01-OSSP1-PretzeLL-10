#ifndef __ARROW_H__
#define __ARROW_H__

#include "BaseBullet.h"


class Arrow : public BaseBullet {
protected:
    Arrow() : BaseBullet("weapon_arrow", 1) {}
    virtual ~Arrow() {}
    
public:
    CREATE_FUNC(Arrow);
    
    bool init() final {
        IF(!BaseBullet::init());
        
        auto size = C2B(getContentSize());
        size.x *= 0.5f;
        size.y *= 0.5f;
        IF(!PhysicsObject::initProjectile(size, b2Vec2(0.0f, 0.0f), this));
        setCategory(CATEGORY_BULLET, MASK_BULLET);
        return true;
    }
};

#endif /* __ARROW_H__ */
