#pragma once

#include "Event.h"
#include "sstream"

namespace Hazel {

class HAZEL_API WindowResizeEvent : public Event
{
public:

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	WindowResizeEvent(unsigned int width, unsigned int height)
		: Width(width), Height(height) {}

	inline unsigned int GetWidth() { return Width; }
	inline unsigned int GetHeight() { return Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResize event: " << Width << ", " << Height;
		return ss.str();
	}

private:

	unsigned int Width, Height;

};

class HAZEL_API WindowCloseEvent : public Event
{
public:

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	WindowCloseEvent() {}
};

class HAZEL_API AppTickEvent : public Event
{
public:

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	AppTickEvent() {}
};

class HAZEL_API AppUpdateEvent : public Event
{
public:

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	AppUpdateEvent() {}
};

class HAZEL_API AppRenderEvent : public Event
{
public:

	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	AppRenderEvent() {}
};
}