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

		glGenVertexArrays(1, &VertexArray);
		glBindVertexArray(VertexArray);

		float Verticies[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		VertexBufferPtr.reset(VertexBuffer::Create(Verticies, sizeof(Verticies)));
	
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t Indices[3] = { 0, 1, 2 };
		IndexBufferPtr.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

		// R"() allows writing chars in strings in separate lines
		std::string VertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 OutPosition;

			void main()
			{
				OutPosition = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string FragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 OutColor;

			in vec3 OutPosition;

			void main()
			{
				OutColor = vec4(OutPosition * 0.5 + 0.5, 1.0);
			}
		)";

		ShaderPtr.reset(new Shader(VertexSrc, FragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (bRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			ShaderPtr->Bind();
			glBindVertexArray(VertexArray);
			glDrawElements(GL_TRIANGLES, IndexBufferPtr->GetCount(), GL_UNSIGNED_INT, nullptr);

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


