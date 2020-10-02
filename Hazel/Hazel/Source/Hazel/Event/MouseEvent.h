#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API HMouseMovedEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	HMouseMovedEvent(float x, float y)
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

class HAZEL_API HMouseScrolledEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		HMouseScrolledEvent(float x, float y)
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

class HAZEL_API HMouseButtonEvent : public HEvent
{
public:

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	inline int GetMouseButton() const { return Button; }

protected:
	
	HMouseButtonEvent(int button)
		: Button(Button) {}

	int Button;
};

class HAZEL_API HMousePressedEvent : public HMouseButtonEvent
{
public:

	EVENT_CLASS_TYPE(MouseButtonPressed);

	HMousePressedEvent(int button)
		: HMouseButtonEvent(Button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MousePressed event: " << Button;
		return ss.str();
	}
};

class HAZEL_API HMouseReleasedEvent : public HMouseButtonEvent
{
public:

	EVENT_CLASS_TYPE(MouseButtonReleased);

	HMouseReleasedEvent(int button)
		: HMouseButtonEvent(button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseReleased event: " << Button;
		return ss.str();
	}
};
}