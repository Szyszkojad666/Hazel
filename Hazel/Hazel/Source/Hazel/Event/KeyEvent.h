#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API KeyEvent : public Event
{
public:

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	
	inline int GetKeyCode() const { return m_KeyCode; }

protected:

	KeyEvent(int keycode) 
		: m_KeyCode(keycode) {}

	int m_KeyCode;
};

class HAZEL_API KeyPressedEvent : public KeyEvent
{
public:

	EVENT_CLASS_TYPE(KeyPressed);

	KeyPressedEvent(int keycode, int repaeatCout)
		: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

	inline int GetRepeatCount { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressed event: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
		return ss.str();
	}

private:
	
	int m_RepeatCount;
};

class HAZEL_API KeyReleasedEvent : publicc KeyEvent
{	
public:

	KeyReleasedEvent(int keycode)
		: m_KeyCode(keycode) {}

	std:string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleased event: " << m_KeyCode;
		return ss.str();
	}
};

}