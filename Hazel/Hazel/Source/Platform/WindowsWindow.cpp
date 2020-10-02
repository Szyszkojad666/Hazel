#include "Hzpch.h"
#include "WindowsWindow.h"
#include "../Hazel/Log.h"
#include "../Hazel/Event/AppEvent.h"
#include "../Hazel/Event/MouseEvent.h"
#include "../Hazel/Event/KeyEvent.h"

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
		glfwSetErrorCallback(GLFWErrorCallback);

		bGLFWInitialized = true;
	}

	Window = glfwCreateWindow((int)Props.Width, (int)Props.Height, Data.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(Window);
	glfwSetWindowUserPointer(Window, &Data);
	SetVSync(true);

	// Set GLFW callbacks
	/////////////////////////////////////////////////////////////////////////////////
	glfwSetWindowSizeCallback(Window, [](GLFWwindow* window, int width, int height)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HWindowResizeEvent Event(width, height);
		Data.EventCallback(Event);
	});

	glfwSetWindowCloseCallback(Window, [](GLFWwindow* window)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HWindowCloseEvent Event;
		Data.EventCallback(Event);
	});

	glfwSetKeyCallback(Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				HKeyPressedEvent Event(key, 0);
				Data.EventCallback(Event);
				break;
			}

			case GLFW_RELEASE:
			{
				HKeyReleasedEvent Event(key);
				Data.EventCallback(Event);
				break;
			}
				
			case GLFW_REPEAT:
			{
				HKeyPressedEvent Event(key, 1);
				Data.EventCallback(Event);
				break;
			}
		}
	});

	glfwSetMouseButtonCallback(Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				HMousePressedEvent Event(button);
				Data.EventCallback(Event);
				break;
			}

			case GLFW_RELEASE:
			{
				HMouseReleasedEvent Event(button);
				Data.EventCallback(Event);
				break;
			}
		}
	});

	glfwSetScrollCallback(Window, [](GLFWwindow* window, double XOffset, double YOffset)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HMouseScrolledEvent Event(XOffset, YOffset);
		Data.EventCallback(Event);
	});

	glfwSetCursorPosCallback(Window, [](GLFWwindow* window, double XOffset, double YOffset)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HMouseMovedEvent Event(XOffset, YOffset);
		Data.EventCallback(Event);
	});
	/////////////////////////////////////////////////////////////////////////////////
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(Window);
}

void WindowsWindow::GLFWErrorCallback(int ErrorCode, const char* Description)
{
	HZ_CORE_ERROR("GLFW Error ({0}): {1}", ErrorCode, Description);
}

}

