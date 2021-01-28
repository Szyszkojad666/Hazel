#include "Hzpch.h"
#include "WindowsWindow.h"
#include "../Source/Hazel/Log.h"
#include "../Source/Hazel/Event/AppEvent.h"
#include "../Source/Hazel/Event/MouseEvent.h"
#include "../Source/Hazel/Event/KeyEvent.h"

#include "glad/glad.h"


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
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "Failed to initialize GLad!");
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

	glfwSetCharCallback(Window, [](GLFWwindow* window, unsigned int keycode)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HKeyTypedEvent Event(keycode);
		Data.EventCallback(Event);
	});

	glfwSetMouseButtonCallback(Window, [](GLFWwindow* window, int button, int action, int mods)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				HMouseButtonPressedEvent Event(button);
				Data.EventCallback(Event);
				break;
			}

			case GLFW_RELEASE:
			{
				HMouseButtonReleasedEvent Event(button);
				Data.EventCallback(Event);
				break;
			}
		}
	});

	glfwSetScrollCallback(Window, [](GLFWwindow* window, double XOffset, double YOffset)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HMouseScrolledEvent Event((float)XOffset, (float)YOffset);
		Data.EventCallback(Event);
	});

	glfwSetCursorPosCallback(Window, [](GLFWwindow* window, double XOffset, double YOffset)
	{
		FWindowData& Data = *(FWindowData*)glfwGetWindowUserPointer(window);

		HMouseMovedEvent Event((float)XOffset, (float)YOffset);
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

