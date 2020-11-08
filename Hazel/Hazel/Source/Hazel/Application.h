#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/AppEvent.h"
#include "LayerStack.h"

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

	std::unique_ptr<IWindow> MainWindow;
	bool bRunning;

	HLayerStack LayerStack;

private:

	static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();
}