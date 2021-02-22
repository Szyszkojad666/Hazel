#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/AppEvent.h"
#include "LayerStack.h"
#include "Hazel/ImGui/ImGuiLayer.h"

#include "Hazel/Renderer/Shader.h"

class HLayer;

namespace Hazel {

class HAZEL_API Application
{
public:

	Application();
	virtual ~Application();

	void Run();

	void PushLayer(HLayer* Layer);
	void PushOverlay(HLayer* Layer);

	inline static Application& Get() { return *s_Instance; }
	inline IWindow& GetWindow() { return *MainWindow; }

protected:

	void OnEvent(HEvent& Event);
	bool OnWindowClose(HWindowCloseEvent& Event);

	bool bRunning;

	HLayerStack LayerStack;
	std::unique_ptr<IWindow> MainWindow;
	
private:

	static Application* s_Instance;
	
	ImGuiLayer* ImGuiLayerPtr;

	unsigned int VertexArray, VertexBuffer, IndexBuffer;
	std::unique_ptr<Shader> ShaderPtr;
};

	// To be defined in CLIENT
	Application* CreateApplication();
}