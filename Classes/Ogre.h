#ifndef __OGRE_H__
#define __OGRE_H__

#include "BaseMonster.h"


class Ogre : public BaseMonster {
public:
    Ogre() : BaseMonster("ogre") {}
    ~Ogre() {}

    CREATE_FUNC(Ogre);

    bool init() final {
        IF(!BaseMonster::init());
        setHP(1000);
        setDamage(1);
        setSpeed(15.0f);
        attackRange = 400.0f;
        detectRange = 400.0f;
        setDelay(0.8f);

        PhysicsObject::scale(0.9f, b2Vec2(0.0f, 1.0f));

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
        auto stone = Poison::create();

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

#endif /* __OGRE_H__ */
