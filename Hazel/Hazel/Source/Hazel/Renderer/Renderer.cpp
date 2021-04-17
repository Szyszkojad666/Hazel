#include "Hzpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Hazel {

FSceneData* Renderer::SceneData = new FSceneData;

void Renderer::BeginScene(Camera& InCamera)
{
	SceneData->ViewProjectionMatrix = InCamera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{

}

void Renderer::Submit(const std::shared_ptr<VertexArray>& InVertexArray, const std::shared_ptr<Shader>& InShader)
{
	InShader->Bind();
	InShader->UploadUniformMat4("u_ViewProjection", SceneData->ViewProjectionMatrix);

	InVertexArray->Bind();
	RenderCommand::DrawIndexed(InVertexArray);
}

}