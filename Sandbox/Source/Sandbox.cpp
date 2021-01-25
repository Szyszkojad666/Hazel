#include <Hazel.h>
#include "imgui/imgui.h"

class HExampleLayer : public Hazel::HLayer
{
public:
	HExampleLayer()
		: HLayer("Example") {}

	void OnEvent(Hazel::HEvent& Event) override
	{
		// TODO: Causes crashes, fix it!
		/*HZ_CLIENT_TRACE("{0}, {1}", Event);*/
	}

	void OnUpdate() override
	{
		if (Hazel::HInput::IsKeyPressed(HZ_KEY_TAB))
		{
			HZ_CORE_TRACE("Tab is pressed!");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("HelloWorld");
		ImGui::End();
	}
};

class Sandbox : public Hazel::Application
{
public:

	Sandbox()
	{
		PushLayer(new HExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}