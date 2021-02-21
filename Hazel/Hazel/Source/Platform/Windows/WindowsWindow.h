#pragma once

#include "../Source/Hazel/Window.h"
#include "../../GLFW/include/GLFW/glfw3.h"

#include "Hazel/Renderer/GraphicsContext.h"

namespace Hazel {

struct FWindowData
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

	inline virtual void* GetNativeWindow() const { return Window; }

private:

	virtual void Init(const WindowProperties& Props);
	virtual void Shutdown();

	static void GLFWErrorCallback(int ErrorCode, const char* Description);

private:

	GLFWwindow* Window;
	GraphicsContext* Context;

	FWindowData Data;
};
	



}