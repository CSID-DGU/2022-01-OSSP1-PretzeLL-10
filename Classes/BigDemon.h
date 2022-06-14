#ifndef __BIG_DEMON_H__
#define __BIG_DEMON_H__

#include "BaseMonster.h"
#include "Stone.h"


class BigDemon : public BaseMonster {
public:
    BigDemon() : BaseMonster("big_demon") {}
    ~BigDemon() {}

    CREATE_FUNC(BigDemon);

    bool init() final {
        IF(!BaseMonster::init());
        setHP(1500);
        setDamage(1);
        setSpeed(15.0f);
        attackRange = 400.0f;
        detectRange = 500.0f;
        setDelay(0.8f);

        PhysicsObject::scale(1.0f, b2Vec2(0.0f, 0.0f));
        setSpeed(getSpeed()/2.0f);
        
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
        
        
        srand((unsigned int)time(NULL));
        int randPattern = rand();
        randPattern %= 3;

        if (randPattern == 0)
        {
            auto stone = BigStone::create();
            normalize(diff);
            addBullet(stone, diff);
            stone->setParent(getWeapon());
            stone->setPosition(getPosition());
            stone->setSpeed(150.0f);
            stone->setVelocity(diff);
            stone->Node::setScale(1.5f);
            stone->PhysicsObject::scale(1.0f);
            stone->move();

            AI->setState(State::WAIT, 2);
        }
        else if (randPattern == 1)
        {
            auto stone = BigStone::create();
            auto stone2 = BigStone::create();
            auto stone3 = BigStone::create();
            cocos2d::Vec2 vec, vecVari;
            vec = cocos2d::Vec2(diff.x, diff.y);
            if (!stone2)
                return;
            addBullet(stone2, diff);
            stone2->setParent(getWeapon());
            stone2->setPosition(getPosition());
            stone2->setSpeed(50.0f);
            stone2->setRotation(VecToDegree(normalize(vec)) + 60.0f);
            vecVari = DegreeToVec(VecToDegree(normalize(vec)) + 60.0f);
            stone2->setVelocity(C2B(normalize(vecVari)));
            stone2->Node::setScale(1.0f);
            stone2->PhysicsObject::scale(0.65f);
            stone2->move();

            if (!stone)
                return;
            normalize(diff);
            addBullet(stone, diff);
            stone->setParent(getWeapon());
            stone->setPosition(getPosition());
            stone->setSpeed(50.0f);
            stone->setVelocity(diff);
            stone->Node::setScale(1.0f);
            stone->PhysicsObject::scale(0.65f);
            stone->move();

            if (!stone3)
                return;
            addBullet(stone3, diff);
            stone3->setParent(getWeapon());
            stone3->setPosition(getPosition());
            stone3->setSpeed(50.0f);
            stone3->setRotation(VecToDegree(normalize(vec)) - 60.0f);
            vecVari = DegreeToVec(VecToDegree(normalize(vec)) - 60.0f);
            stone3->setVelocity(C2B(normalize(vecVari)));
            stone3->Node::setScale(1.0f);
            stone3->PhysicsObject::scale(0.65f);
            stone3->move();

            AI->setState(State::WAIT, 3);
        }
        else if (randPattern == 2)
        {
            auto stone = BigStone::create();
            normalize(diff);
            addBullet(stone, diff);
            stone->setParent(getWeapon());
            stone->setPosition(getPosition());
            stone->setSpeed(100.0f);
            stone->setVelocity(diff);
            stone->Node::setScale(1.0f);
            stone->PhysicsObject::scale(0.65f);
            stone->move();

            AI->setState(State::WAIT, 1);
        }
        else
        {
            return;
        }

        
    }
};

#endif /* __BIGDEMON_H__ */
