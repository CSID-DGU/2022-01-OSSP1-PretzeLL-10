#include "Timer.h"

USING_NS_CC;

_Timer::_Timer() {
	save_time = 0;
}

_Timer::~_Timer() {
	save_time = 0;
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool _Timer::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	label = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24 * 10);
	label->setScale(0.1f);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2 + 100,
			origin.y + visibleSize.height - label->getContentSize().height + 100));

		// add the label as a child to this layer
		this->addChild(label, 1);

		time = save_time;
		lapIndex = 0;
		this->schedule(schedule_selector(_Timer::TimerMethod), 0.01);
	}

	return true;
}

void _Timer::TimerMethod(float dt) {
	time += dt;
	save_time = time;
	__String* timeToDisplay = __String::createWithFormat("%02d : %02d", int(save_time / 60), int(save_time) % 60);

	label->setString(timeToDisplay->getCString());
}

float _Timer::getTime() {
	return save_time;
}

std::string _Timer::getTimeStringFormat(const std::string& format, int a, int b)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), a, b) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), a, b);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
