#ifndef __FIREBALL_H__
#define __FIREBALL_H__

#include "BaseBullet.h"


class FireBall : public BaseBullet {
protected:
    cocos2d::Vec2 __initial_pos;
    float __desired_distance = 500.0f;

protected:
    FireBall() : BaseBullet("flame") {}
    virtual ~FireBall() {}

public:
    CREATE_FUNC(FireBall);

    void update(float dt) final {
        ProjectileObject::update(dt);

        if (!__desired_distance) return;
        float len = length(getPosition() - __initial_pos);
        if (len > __desired_distance) {
            removeAfter(0.0);
            unscheduleUpdate();
        }
    }

    void setInitialPos() {
        __initial_pos = getPosition();
    }

    void onContact(b2Contact* contact) final {
        __desired_distance = 0.0f;
        setCategory(CATEGORY_BULLET, MASK_NONE);
        removeAfter(3.0);

        auto delay = cocos2d::DelayTime::create(2.0f);
        auto fadeOut = cocos2d::FadeOut::create(1.0f);
        auto sequence = cocos2d::Sequence::createWithTwoActions(delay, fadeOut);
        runAction(sequence);
    }
};

#endif /* __FIREBALL_H__ */
