#pragma once

#include "Event.h"

namespace Hazel {

class HAZEL_API HWindowResizeEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	HWindowResizeEvent(unsigned int width, unsigned int height)
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

class HAZEL_API HWindowCloseEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	HWindowCloseEvent() {}
};

class HAZEL_API HAppTickEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	HAppTickEvent() {}
};

class HAZEL_API HAppUpdateEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	HAppUpdateEvent() {}
};

class HAZEL_API HAppRenderEvent : public HEvent
{
public:

	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)

	HAppRenderEvent() {}
};
}