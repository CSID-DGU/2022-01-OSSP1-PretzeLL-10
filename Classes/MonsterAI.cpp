#include "MonsterAI.h"
#include "BaseMonster.h"

MonsterAI::MonsterAI()
	: roamVec(cocos2d::Vec2::ZERO)
{}

bool MonsterAI::init()
{
	if (!Node::init())
		return false;

	state = State::WAIT;
	stateCount = 0;
	delay = 0.1f;

	_running = true;
	this->schedule(schedule_selector(MonsterAI::updateState), delay);
	this->scheduleUpdate();


	return true;
}

void MonsterAI::onEnter()
{
	attackRange = ((BaseMonster*)getParent())->getAttackRange();
	detectRange = ((BaseMonster*)getParent())->getDetectRange();
	delay = ((BaseMonster*)getParent())->getDelay();
}

void MonsterAI::update(float delta)
{
	setPosition(getParent()->getPosition());
	getDistanceDiff();
	updateAliveState();
}

void MonsterAI::updateAliveState()
{
	if (((BaseMonster*)getParent())->getHP() <= 0)
	{
		state = State::DIE;
		return;
	}
}

void MonsterAI::updateState(float delta)
{
	if (((BaseMonster*)getParent())->getHP() <= 0)
	{
		state = State::DIE;
		return;
	}

	if (state == State::WAIT && stateCount > 0)
	{
		stateCount--;
		return;
	}

	if (distance <= attackRange)
	{
		setState(State::ATTACK, 0);
	}
	else if (distance <= detectRange)
	{
		setState(State::MOVE, 0);
	}
	else
	{
		if (state == State::ROAM && stateCount <= 0)
		{
			setState(State::WAIT, 2);
		}
		else if (state == State::ROAM)
		{
			stateCount--;
		}
		else
		{
			setState(State::ROAM, 3);
		}
		randRoamVec();
	}
}

State MonsterAI::getState() const
{
	return state;
}

void MonsterAI::setState(State st, int count)
{
	state = st;
	stateCount = count;
}

void MonsterAI::getDistanceDiff()
{
    float distance = std::numeric_limits<float>::max();
	auto diff = cocos2d::Vec2::ZERO;
	typedef DynamicObject target_t;
	std::list<target_t*> _target = ((BaseMonster*)getParent())->getTarget();

    for (auto iter : _target) {
        diff = iter->getPosition() - getPosition();
        float diff_len = length(diff);
        if (distance > diff_len) distance = diff_len;
    }
	this->distance = distance;
	diffVec = diff;
}

void MonsterAI::randRoamVec()
{
	std::random_device rand_device;
	std::mt19937_64 engine;
	std::uniform_real_distribution<float> rand1;
	std::uniform_real_distribution<float> rand2;
	engine = std::mt19937_64(rand_device());
	rand1 = std::uniform_real_distribution<float>(-1.0, 1.0);
	rand2 = std::uniform_real_distribution<float>(-1.0, 1.0);

	float x = rand1(engine);
	float y = rand2(engine);

	roamVec = cocos2d::Vec2(x, y);
	roamVec = normalize(roamVec);
}

cocos2d::Vec2 MonsterAI::getRoamVec()
{
	return roamVec;
}

MonsterAI::~MonsterAI()
{

}