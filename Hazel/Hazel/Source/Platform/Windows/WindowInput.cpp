#include "Hzpch.h"
#include "WindowInput.h"
#include "WindowInput.h"

#include "../../GLFW/include/GLFW/glfw3.h"
#include "Hazel/Application.h"

namespace Hazel {

HInput* HInput::InputInstance = new HWindowInput();

bool HWindowInput::IsKeyPressedImpl(int Keycode)
{
	int KeyState = 0;

	if (auto* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()))
	{
		KeyState = glfwGetKey(Window, Keycode);
	}

	return KeyState == GLFW_PRESS || GLFW_REPEAT;
}

bool HWindowInput::IsMouseButtonPressedImpl(int Button)
{
	int ButtonState = 0;

	if (auto* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()))
	{
		ButtonState = glfwGetMouseButton(Window, Button);
	}

	return ButtonState == GLFW_PRESS || GLFW_REPEAT;
}

std::pair<float, float> HWindowInput::GetMousePositionImpl()
{
	double MouseX, MouseY;

	if (auto* Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()))
	{
		glfwGetCursorPos(Window, &MouseX, &MouseY);
	}

	return std::pair<float, float>(MouseX, MouseY);
}


};

