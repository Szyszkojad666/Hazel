#include "Hzpch.h"
#include "WindowsWindow.h"
#include "../Hazel/Log.h"

namespace Hazel {

static bool bGLFWInitialized = false;

IWindow* IWindow::Create(const WindowProperties& Props)
{
	return new WindowsWindow(Props);
}

WindowsWindow::WindowsWindow(const WindowProperties& Props)
{
	Init(Props);
}

WindowsWindow::~WindowsWindow()
{

}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(Window);
}

void WindowsWindow::SetVSync(bool bEnable)
{
	glfwSwapInterval(bEnable);
	Data.bVSync = bEnable;
}

bool WindowsWindow::IsVSync() const
{
	return Data.bVSync;
}

void WindowsWindow::Init(const WindowProperties& Props)
{
	Data.Title = Props.Title;
	Data.Width = Props.Width;
	Data.Height = Props.Height;

	HZ_CORE_INFO("Creating window {0} ({1},{2})", Props.Title, Props.Width, Props.Height);

	if (!bGLFWInitialized)
	{
		// TODO: glfwTerminate on system shutdown
		int bSuccess = glfwInit();
		HZ_CORE_ASSERT(bSuccess, "Could not initialize GLFW");

		bGLFWInitialized = true;
	}

	Window = glfwCreateWindow((int)Props.Width, (int)Props.Height, Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(Window);
	glfwSetWindowUserPointer(Window, &Data);
	SetVSync(true);
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(Window);
}

}

