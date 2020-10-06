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
				for (HLayer* Layer : LayerStack)
				{
					Layer->OnUpdate();
				}

				MainWindow->OnUpdate();
			}
		}
	}

	void Application::PushLayer(HLayer* Layer)
	{
		LayerStack.PushLayer(Layer);
	}

	void Application::PushOverlay(HLayer* Layer)
	{
		LayerStack.PushOverlay(Layer);
	}

	void Application::OnEvent(HEvent& Event)
	{
		EventDispatcher Dispatcher(Event);
		Dispatcher.Dispatch<HWindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto It = LayerStack.end(); It != LayerStack.begin();)
		{
			(*--It)->OnEvent(Event);
			if (Event.IsHandled())
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(HWindowCloseEvent& Event)
	{
		bRunning = false;
		return true;
	}

}


