#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel {

class HAZEL_API Application
{
public:

	Application();
	virtual ~Application();

public:

	void Run();

private:

	std::unique_ptr<IWindow> MainWindow;
	bool bRunning;
};

// To be defined in CLIENT
Application* CreateApplication();
}