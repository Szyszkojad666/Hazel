#include "Hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "Glad/glad.h"

namespace Hazel {

OpenGLContext::OpenGLContext(GLFWwindow* Window)
	: WindowHandle(Window)
{
	HZ_CORE_ASSERT(WindowHandle, "Window is null!")
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "Failed to initialize GLad!");
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(WindowHandle);
}

}

