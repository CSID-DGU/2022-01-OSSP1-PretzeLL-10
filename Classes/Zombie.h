#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__

#include "BaseMonster.h"


class Zombie : public BaseMonster {
public:
    Zombie() : BaseMonster("zombie") {}
    ~Zombie() {}

    CREATE_FUNC(Zombie);

    bool init() final {
        IF(!BaseMonster::init());
        setHP(150);
        setDamage(1);
        setSpeed(0.5f);
        attackRange = 200.0f;
        detectRange = 300.0f;
        setDelay(1.0f);

        PhysicsObject::scale(0.6f, b2Vec2(0.0f, 0.0f));

        return true;
    }
    virtual void followTarget()
    {
        float distance = std::numeric_limits<float>::max();
        auto diff = cocos2d::Vec2::ZERO;

        for (auto iter : __target) {
            diff = iter->getPosition() - getPosition();
            float diff_len = length(diff);
            if (distance > diff_len) distance = diff_len;
        }

        if (diff == cocos2d::Vec2::ZERO) return;
        normalize(diff);
        setVelocity(C2B(diff));
        setFuture(MOVE);
    }
    void roaming()
    {
        cocos2d::Vec2 vec = AI->getRoamVec();
        setVelocity(b2Vec2(vec.x, vec.y));
        setFuture(MOVE);
    }
    virtual void attack() override
    {
        auto hero = getParent()->getChildByTag<cocos2d::Node*>(TAG_PLAYER);
        auto diff = C2B(hero->getPosition() - getPosition());
        auto stone = Stone::create();

        normalize(diff);
        addBullet(stone, diff);
        stone->setParent(getWeapon());
        stone->setPosition(getPosition());
        stone->setSpeed(50.0f);
        stone->setVelocity(diff);
        stone->setAngularVelocity(C2B(180.0f));
        stone->Node::setScale(1.0f);
        stone->PhysicsObject::scale(0.7f);
        stone->move();

        AI->setState(State::WAIT, 1);
    }
};

#endif /* __ZOMBIE_H__ */
