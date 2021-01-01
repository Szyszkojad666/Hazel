#include <Hazel.h>

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
};

class Sandbox : public Hazel::Application
{
public:

	Sandbox()
	{
		PushLayer(new HExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}