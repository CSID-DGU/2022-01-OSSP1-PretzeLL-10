#ifndef __MONSTER_AI_H__
#define __MONSTER_AI_H__

#include <cocos2d.h>
#include "DynamicObject.h"
#include "Utility.h"

enum class State
{
	WAIT,
	ROAM,
	ATTACK,
	MOVE,
	DIE
};

class MonsterAI : public cocos2d::Node
{
public:
	State state;
	int stateCount;
	float distance;
	float detectRange;
	float attackRange;
	float delay;
	cocos2d::Vec2 diffVec;
	cocos2d::Vec2 roamVec;

	virtual bool init() override;

	virtual void update(float delta) override;

	void updateAliveState();

	State getState() const;
	void setState(State st, int count);

	CREATE_FUNC(MonsterAI);
public:
	MonsterAI();
	virtual ~MonsterAI();

	void randRoamVec();
	cocos2d::Vec2 getRoamVec();

	void onEnter() override;
	void updateState(float delta);
	void getDistanceDiff();
public:
};

#endif /* __MONSTER_AI__ */
