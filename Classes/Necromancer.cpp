#include "Necromancer.h"
#include "GameManager.h"

void Necromancer::dieing()
{
    setCategory(CATEGORY_MONSTER, MASK_NONE);
    setTag(-1);
    stopAllActions();
    removeAfter(1.5f);
    setVelocity(b2Vec2(0.0f, 0.0f));
    GameManager::getInstance()->deleteMonster(this);
    unschedule(schedule_selector(BaseMonster::behavior));

    auto monster1 = Imp::create();
    monster1->setPosition(this->getPosition().x + 5, this->getPosition().y + 5);
    GameManager::getInstance()->addMonsters2(monster1);

    auto monster2 = Imp::create();
    monster2->setPosition(this->getPosition().x - 5, this->getPosition().y - 5);
    GameManager::getInstance()->addMonsters2(monster2);

    auto delay = cocos2d::DelayTime::create(0.5f);
    auto fade = cocos2d::FadeOut::create(1.0f);
    auto seq = cocos2d::Sequence::createWithTwoActions(delay, fade);
    runAction(seq);
}