#include "Hzpch.h"
#include "Application.h"
#include "Event/AppEvent.h"
#include "../../GLFW/include/GLFW/glfw3.h"


namespace Hazel {

	Application::Application()
	{
		MainWindow = std::unique_ptr<IWindow>(IWindow::Create());
		bRunning = true;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (bRunning)
		{
			if (MainWindow)
			{
				MainWindow->OnUpdate();
			}
		}
	}
}


