#include <Hazel.h>
#include "imgui/imgui.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Input.h"

class HExampleLayer : public Hazel::HLayer
{
public:
	HExampleLayer() : HLayer("Example"), ViewportCamera(-1.6f, 1.6f, -0.9f, 0.9f), CameraPosition(0.0f)
	{

		VertexArrayPtr.reset(Hazel::VertexArray::Create());

		float Verticies[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};

		VertexBufferPtr.reset(Hazel::VertexBuffer::Create(Verticies, sizeof(Verticies)));
		Hazel::BufferLayout Layout = {
			{ Hazel::EShaderDataType::Float3, "a_Position" },
			{ Hazel::EShaderDataType::Float4, "a_Color" }
		};

		VertexBufferPtr->SetLayout(Layout);
		VertexArrayPtr->AddVertexBuffer(VertexBufferPtr);

		uint32_t Indices[3] = { 0, 1, 2 };
		IndexBufferPtr.reset(Hazel::IndexBuffer::Create(Indices, sizeof(Indices) / sizeof(uint32_t)));
		VertexArrayPtr->SetIndexBuffer(IndexBufferPtr);

		SquareVertexArrayPtr.reset(Hazel::VertexArray::Create());

		float SquareVerticies[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Hazel::VertexBuffer> SquareVB;
		SquareVB.reset(Hazel::VertexBuffer::Create(SquareVerticies, sizeof(SquareVerticies)));
		SquareVB->SetLayout({ { Hazel::EShaderDataType::Float3, "a_Position" } });
		SquareVertexArrayPtr->AddVertexBuffer(SquareVB);

		uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Hazel::IndexBuffer> SquareIB;
		SquareIB.reset(Hazel::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
		SquareVertexArrayPtr->SetIndexBuffer(SquareIB);

		// R"() allows writing chars in strings in separate lines
		std::string VertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
		
			out vec3 V_Position;
			out vec4 V_Color;

			void main()
			{
				V_Position = a_Position;
				V_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		std::string BlueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 V_Position;
			
			uniform mat4 u_ViewProjection;

			void main()
			{
				V_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string BlueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 Color;
			 
			in vec3 V_Position;
	
			void main()
			{
				Color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		ShaderPtr.reset(new Hazel::Shader(VertexSrc, FragmentSrc));
		BlueShader.reset(new Hazel::Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc));
	}

	void OnEvent(Hazel::HEvent& Event) override
	{
	
	}

	void OnUpdate() override
	{
		if (Hazel::HInput::IsKeyPressed(HZ_KEY_LEFT)) CameraPosition.x -= CameraMoveSpeed;
		else if (Hazel::HInput::IsKeyPressed(HZ_KEY_RIGHT)) CameraPosition.x += CameraMoveSpeed;
		
		if (Hazel::HInput::IsKeyPressed(HZ_KEY_UP)) CameraPosition.y += CameraMoveSpeed;
		else if (Hazel::HInput::IsKeyPressed(HZ_KEY_DOWN)) 	CameraPosition.y -= CameraMoveSpeed;
		
		if (Hazel::HInput::IsKeyPressed(HZ_KEY_A)) CameraRotation += CameraRotationSpeed;
		else if (Hazel::HInput::IsKeyPressed(HZ_KEY_D)) CameraRotation -= CameraRotationSpeed;

		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Hazel::RenderCommand::Clear();

		ViewportCamera.SetPosition(CameraPosition);
		ViewportCamera.SetRotation(CameraRotation);

		Hazel::Renderer::BeginScene(ViewportCamera);

		Hazel::Renderer::Submit(SquareVertexArrayPtr, BlueShader);
		Hazel::Renderer::Submit(VertexArrayPtr, ShaderPtr);

		Hazel::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

private:
	std::shared_ptr<Hazel::Shader> ShaderPtr;
	std::shared_ptr<Hazel::Shader> BlueShader;
	std::shared_ptr<Hazel::VertexArray> VertexArrayPtr;
	std::shared_ptr<Hazel::VertexBuffer> VertexBufferPtr;
	std::shared_ptr<Hazel::IndexBuffer> IndexBufferPtr;

	std::shared_ptr<Hazel::VertexArray> SquareVertexArrayPtr;

	Hazel::Camera ViewportCamera;
	glm::vec3 CameraPosition;
	float CameraRotation = 0.f;
	float CameraMoveSpeed = 0.1f;
	float CameraRotationSpeed = 2.0f;
};

class Sandbox : public Hazel::Application
{
public:

	Sandbox()
	{
		PushLayer(new HExampleLayer());
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}