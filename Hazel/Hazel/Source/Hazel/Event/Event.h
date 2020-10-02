#pragma once

#include "Core.h"

namespace Hazel {

enum class EEventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EEventCategory
{
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EEventType GetStaticType() { return EEventType::##type; }\
								virtual EEventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define  EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class HAZEL_API HEvent
{
	friend class EventDispatcher;

public:

	virtual EEventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EEventCategory Category)
	{
		return GetCategoryFlags() & Category;
	}

protected:

	bool bHandled = false;
};

class HAZEL_API EventDispatcher
{
	
	template<typename T>
	using EventFn = std::function<bool(T&)>;

public:

	EventDispatcher(HEvent& event)
		: m_Event(event) {}

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.bHandled = func(*(T*)&m_Event);
			return true;
		}

		return false;
	}

private:

	HEvent& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const HEvent& e)
{
	 return os << e.ToString();
}

}