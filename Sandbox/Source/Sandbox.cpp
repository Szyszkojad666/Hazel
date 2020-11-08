#include <Hazel.h>

class HExampleLayer : public Hazel::HLayer
{
public:
	HExampleLayer()
		: HLayer("Example") {}

	/*void OnUpdate() override
	{
		HZ_CLIENT_INFO("ExampleLayer::Update");
	}*/

	void OnEvent(Hazel::HEvent& Event) override
	{
		HZ_CLIENT_TRACE("{0}", Event);
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