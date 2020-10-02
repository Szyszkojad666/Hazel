#include "Hzpch.h"
#include "Application.h"
#include "../../GLFW/include/GLFW/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		MainWindow = std::unique_ptr<IWindow>(IWindow::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

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

	void Application::OnEvent(HEvent& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<HWindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		HZ_CORE_TRACE("{0}", Event);
	}

	bool Application::OnWindowClose(HWindowCloseEvent& Event)
	{
		bRunning = false;
		return true;
	}

}


