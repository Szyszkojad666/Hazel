#include "Hzpch.h"
#include "ImGuiLayer.h"

#include <../Hazel/Hazel/Vendor/imgui/imgui.h>
#include "../Hazel/Hazel/Source/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "../Hazel/Hazel/Vendor/GLFW/include/GLFW/glfw3.h"

#include "Hazel/Application.h"

// TEMP
#include "../../GLFW/include/GLFW/glfw3.h"
#include "../../Glad/include/glad/glad.h"

namespace Hazel {

	ImGuiLayer::ImGuiLayer()
		: HLayer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& IO = ImGui::GetIO();
		Application& App = Application::Get();
		IWindow& Window = App.GetWindow();
		IO.DisplaySize = ImVec2(Window.GetWidth(), Window.GetHeight());

		float CurrentTime = (float)glfwGetTime();
		IO.DeltaTime = PreviousTime > 0.f ? (CurrentTime - PreviousTime) : (1 / 60.f);
		PreviousTime = CurrentTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool bShow = true;
		ImGui::ShowDemoWindow(&bShow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(HEvent& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<HMouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressed));
		Dispatcher.Dispatch<HMouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
		Dispatcher.Dispatch<HMouseMovedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		Dispatcher.Dispatch<HMouseScrolledEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
		Dispatcher.Dispatch<HKeyPressedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		Dispatcher.Dispatch<HKeyReleasedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
		Dispatcher.Dispatch<HKeyTypedEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
		Dispatcher.Dispatch<HWindowResizeEvent>(HZ_BIND_EVENT_FN(ImGuiLayer::OnWindowResised));
	}

	bool ImGuiLayer::OnMouseButtonPressed(HMouseButtonPressedEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.MouseDown[Event.GetMouseButton()] = true;
		
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(HMouseButtonReleasedEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.MouseDown[Event.GetMouseButton()] = false;
		
		return false;
	}

	bool ImGuiLayer::OnMouseMoved(HMouseMovedEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.MousePos = ImVec2(Event.GetX(), Event.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolled(HMouseScrolledEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.MouseWheel += Event.GetYOffset();
		Io.MouseWheelH += Event.GetXOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressed(HKeyPressedEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.KeysDown[Event.GetKeyCode()] = true;
		
		Io.KeyCtrl = Io.KeysDown[GLFW_KEY_LEFT_CONTROL] || Io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		Io.KeyShift = Io.KeysDown[GLFW_KEY_LEFT_SHIFT] || Io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		Io.KeyAlt = Io.KeysDown[GLFW_KEY_LEFT_ALT] || Io.KeysDown[GLFW_KEY_RIGHT_ALT];
		Io.KeySuper = Io.KeysDown[GLFW_KEY_LEFT_SUPER] || Io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleased(HKeyReleasedEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.KeysDown[Event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTyped(HKeyTypedEvent& Event)
	{
		int KeyCode = Event.GetKeyCode();
		if (KeyCode > 0 && KeyCode < 0x10000)
		{
			ImGuiIO& io = ImGui::GetIO();
			io.AddInputCharacter(KeyCode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResised(HWindowResizeEvent& Event)
	{
		ImGuiIO& Io = ImGui::GetIO();
		Io.DisplaySize = ImVec2(Event.GetWidth(), Event.GetHeight());
		Io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, Event.GetWidth(), Event.GetHeight());
		
		return false;
	}

}
