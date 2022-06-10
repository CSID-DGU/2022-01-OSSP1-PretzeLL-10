#ifndef __Timer_SCENE_H__
#define __Timer_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

static float save_time = 0;

class _Timer : public cocos2d::Node{
private:
	_Timer();
	~_Timer();

public:
	virtual bool init();

	CREATE_FUNC(_Timer);

	void TimerMethod(float dt);
	static float getTime();
	static std::string getTimeStringFormat(const std::string& format, int a, int b);

	cocos2d::Label* label;
	float time;	

	float laps[3];

	int lapIndex;
};

#endif
