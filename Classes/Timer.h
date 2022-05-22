#ifndef __Timer_SCENE_H__
#define __Timer_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

static float save_time = 0;

class _Timer : public cocos2d::Node{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(_Timer);

	void TimerMethod(float dt);

	cocos2d::Label* label;
	float time;	

	float laps[3];

	int lapIndex;
};

#endif