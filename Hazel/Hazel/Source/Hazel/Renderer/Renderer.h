#pragma once

#include "RenderCommand.h"
#include "Camera\Camera.h"
#include "Shader.h"

namespace Hazel {

struct FSceneData
{
	glm::mat4 ViewProjectionMatrix;
};

class Renderer
{

public:

	static void Init();

	static void BeginScene(Camera& InCamera);
	static void EndScene();

	static void Submit(const std::shared_ptr<VertexArray>& InVertexArray, const std::shared_ptr<Shader>& InShader, const glm::mat4& Transform = glm::mat4(1.0f));

	inline static RendererAPI::ERendererAPI GetRendererAPI() { return RendererAPI::GetAPI(); }

private:

	static FSceneData* SceneData;
	
};
}
