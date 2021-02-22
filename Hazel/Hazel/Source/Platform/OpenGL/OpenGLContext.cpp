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

	HZ_CORE_INFO("OpenGL Vendor : {0}", glGetString(GL_VENDOR));
	HZ_CORE_INFO("OpenGL Renderer : {0}", glGetString(GL_RENDERER));
	HZ_CORE_INFO("OpenGL Version : {0}", glGetString(GL_VERSION) );
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(WindowHandle);
}

}

