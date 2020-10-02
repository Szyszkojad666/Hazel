#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/AppEvent.h"

namespace Hazel {

class HAZEL_API Application
{
public:

	Application();
	virtual ~Application();

public:

	void Run();

protected:

	void OnEvent(HEvent& Event);

private:

	bool OnWindowClose(HWindowCloseEvent& Event);

	std::unique_ptr<IWindow> MainWindow;
	bool bRunning;
};

// To be defined in CLIENT
Application* CreateApplication();
}