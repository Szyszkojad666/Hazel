#pragma once

#include "../Hazel/Window.h"
#include "../../GLFW/include/GLFW/glfw3.h"

namespace Hazel {

struct WindowData
{
	std::string Title;
	unsigned int Width, Height;
	bool bVSync;

	EventCallbackFn EventCallback;
};

class WindowsWindow : public IWindow
{

public:

	WindowsWindow(const WindowProperties& Props);
	virtual ~WindowsWindow();

	virtual void OnUpdate() override;

	virtual unsigned int GetWidth() const override { return Data.Width; }
	virtual unsigned int GetHeight() const override { return Data.Height; }

	// Window attributes
	inline void SetEventCallback(const EventCallbackFn& callback) override { Data.EventCallback = callback; }
	virtual void SetVSync(bool bEnable);
	virtual bool IsVSync() const;

private:

	virtual void Init(const WindowProperties& Props);
	virtual void Shutdown();

private:

	GLFWwindow* Window;
	WindowData Data;
};
	



}