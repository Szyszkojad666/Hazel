#include "Hzpch.h"
#include "Application.h"
#include "Hazel/Input.h"
#include "../../GLFW/include/GLFW/glfw3.h"

#include <glad/glad.h>

#include <glm/glm.hpp>



namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		MainWindow = std::unique_ptr<IWindow>(IWindow::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
		bRunning = true;

		ImGuiLayerPtr = new ImGuiLayer();
		PushOverlay(ImGuiLayerPtr);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (bRunning)
		{
			for (HLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}
				
			if (ImGuiLayerPtr)
			{
				ImGuiLayerPtr->Begin();

				for (HLayer* Layer : LayerStack)
				{
					Layer->OnImGuiRender();
				}

				ImGuiLayerPtr->End();
			}

			if (MainWindow)
			{
				MainWindow->OnUpdate();
			}
		}
	}

	void Application::PushLayer(HLayer* Layer)
	{
		LayerStack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void Application::PushOverlay(HLayer* Layer)
	{
		LayerStack.PushOverlay(Layer);
		Layer->OnAttach();
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


