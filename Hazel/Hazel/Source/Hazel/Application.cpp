#include "Hzpch.h"
#include "Application.h"
#include "Hazel/Input.h"
#include "../../GLFW/include/GLFW/glfw3.h"

#include <glad/glad.h>

#include <glm/glm.hpp>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(EShaderDataType Type)
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

		HZ_CORE_ASSERT(false, "Unkown EShaderDataType!");
		return 0;
	}

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

		float Verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};

		VertexBufferPtr.reset(VertexBuffer::Create(Verticies, sizeof(Verticies)));

		BufferLayout Layout = {
			{ EShaderDataType::Float3, "a_Position" },
			{ EShaderDataType::Float4, "a_Color" }
		};

		uint32_t index = 0;
		for (const auto& Element : Layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index
			, Element.GetComponentCount()
			, ShaderDataTypeToOpenGLBaseType(Element.Type)
			, Element.bNormalized ? GL_TRUE : GL_FALSE
			, Layout.GetStride()
			, (const void*)Element.Offset);
			
			index++;
		}
	
		uint32_t Indices[3] = { 0, 1, 2 };
		IndexBufferPtr.reset(IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));

		// R"() allows writing chars in strings in separate lines
		std::string VertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
		
			out vec3 V_Position;
			out vec4 V_Color;

			void main()
			{
				V_Position = a_Position;
				V_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string FragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 Color;
			 
			in vec3 V_Position;
			in vec4 V_Color;

			void main()
			{
				Color = vec4(V_Position * 0.5 + 0.5, 1.0);
				Color = V_Color;
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


