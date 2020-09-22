#pragma once

#include "../Hzpch.h"

#include "../Hazel/Core.h"
#include "../Hazel/Event/Event.h"

namespace Hazel {

using EventCallbackFn = std::function<void(Event&)>;

struct WindowProperties
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProperties(const std::string& InTitle = "Hazel Engine", unsigned int InWidth = 1280, unsigned int InHeight = 720)
		: Title(InTitle), Width(InWidth), Height(InHeight)
	{
	}
};

// Interface representing a desktop system based Window
class HAZEL_API IWindow
{

public:

	virtual ~IWindow() {}

	virtual void OnUpdate() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	// Window attributes
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool bEnable) = 0;
	virtual bool IsVSync() const = 0;

	static IWindow* Create(const WindowProperties& InProps = WindowProperties());
};






































}