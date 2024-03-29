#include "Hzpch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Hazel {

FSceneData* Renderer::SceneData = new FSceneData;

void Renderer::Init()
{
	RenderCommand::Init();
}

void Renderer::BeginScene(Camera& InCamera)
{
	SceneData->ViewProjectionMatrix = InCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const TRef<VertexArray>& InVertexArray, const TRef<Shader>& InShader, const glm::mat4& Transform /*= glm::mat4(1.0f*/)
{
	InShader->Bind();

	if (const auto OpenGLShaderPtr = std::dynamic_pointer_cast<OpenGLShader>(InShader))
	{
		OpenGLShaderPtr->UploadUniformMat4("u_ViewProjection", SceneData->ViewProjectionMatrix);
		OpenGLShaderPtr->UploadUniformMat4("u_Transform", Transform);
	}
	
	InVertexArray->Bind();
	RenderCommand::DrawIndexed(InVertexArray);
}

}
