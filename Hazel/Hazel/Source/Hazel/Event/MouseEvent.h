#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API MouseMovedEvent : public Event
{
public:

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	MouseEvent(float x, float y)
		: MouseX(x), MouseY(y) {}

	inline float GetX() const { return MouseX; }
	inline float GetY() const { return MouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << "Mouse X: " << MouseX << " , Mouse Y: "<< MouseY;
		return ss.str();
	}

private:

	float MouseX, MouseY;
};

class HAZEL_API MouseScrolledEvent : public Event
{
public:

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		MouseEvent(float x, float y)
		: XOffset(x), YOffset(y) {}

	inline float GetXOffset() const { return XOffset; }
	inline float GetYOffset() const { return YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << "Mouse Offset X: " << XOffset << " , Mouse Offset Y: " << YOffset;
		return ss.str();
	}

private:

	float XOffset, YOffset;
};

class HAZEL_API MouseButtonEvent : public Event
{
public:

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	inline int GetMouseButton() const { return Button; }

protected:
	
	MouseButtonEvent(int button)
		: Button(Button) {}

	int Button;
};

class HAZEL_API MousePressedEvent : public MouseButtonEvent
{
public:

	EVENT_CLASS_TYPE(MousePressed);

	MousePressedEvent(int Button)
		: MouseEvent(Button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousePressed event: " << Button;
		return ss.str();
	}
};

class HAZEL_API MouseReleasedEvent : publicc MouseButtonEvent
{
public:

	MouseReleasedEvent(int Button)
		: Button(Button) {}

	std:string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseReleased event: " << Button;
		return ss.str();
	}
};
}