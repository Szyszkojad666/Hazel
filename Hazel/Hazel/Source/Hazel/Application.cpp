#include "Hzpch.h"
#include "Application.h"
#include "Hazel/Input.h"

#include "../../GLFW/include/GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "Renderer/Renderer.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	/*static GLenum ShaderDataTypeToOpenGLBaseType(EShaderDataType Type)
	{
		switch (Type)
		{
			case EShaderDataType::Float:	return GL_FLOAT;
			case EShaderDataType::Float2:	return GL_FLOAT;
			case EShaderDataType::Float3:	return GL_FLOAT;
			case EShaderDataType::Float4:	return GL_FLOAT;
			case EShaderDataType::Mat3:		return GL_FLOAT;
			case EShaderDataType::Mat4:		return GL_FLOAT;
			case EShaderDataType::Int:		return GL_INT;
			case EShaderDataType::Int2:		return GL_INT;
			case EShaderDataType::Int3:		return GL_INT;
			case EShaderDataType::Int4:		return GL_INT;
			case EShaderDataType::Bool:		return GL_BOOL;
		}


		HZ_CORE_ASSERT(false, "Unknown EShaderDataType!");
		return 0;
	}*/

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		MainWindow = std::unique_ptr<IWindow>(IWindow::Create());
		MainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();
		
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
			const float Time = glfwGetTime(); // Platform::Seconds()
			FTimeStep TimeStep = Time - LastFrameTime;
			LastFrameTime = Time;

			for (HLayer* Layer : LayerStack)
			{
				Layer->OnUpdate(TimeStep);
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


