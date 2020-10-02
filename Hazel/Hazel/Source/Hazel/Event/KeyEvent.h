#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API HKeyEvent : public HEvent
{
public:

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	
	inline int GetKeyCode() const { return KeyCode; }

protected:

	HKeyEvent(int keycode)
		: KeyCode(keycode) {}

	int KeyCode;
};

class HAZEL_API HKeyPressedEvent : public HKeyEvent
{
public:

	EVENT_CLASS_TYPE(KeyPressed);

	HKeyPressedEvent(int keycode, int repeatCount)
		: HKeyEvent(keycode), RepeatCount(repeatCount) {}

	inline int GetRepeatCount() { return RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressed event: " << KeyCode << "(" << RepeatCount << "repeats)";
		return ss.str();
	}

private:
	
	int RepeatCount;
};

class HAZEL_API HKeyReleasedEvent : public HKeyEvent
{	
public:

	EVENT_CLASS_TYPE(KeyReleased);

	HKeyReleasedEvent(int keycode)
		: HKeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleased event: " << KeyCode;
		return ss.str();
	}
};

}