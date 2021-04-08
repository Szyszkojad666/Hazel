#pragma once

#include "RenderCommand.h"

namespace Hazel {

class Renderer
{

public:

	static void BeginScene();
	static void EndScene();

	static void Submit(const std::shared_ptr<VertexArray>& InVertexArray);

	inline static RendererAPI::ERendererAPI GetRendererAPI() { return RendererAPI::GetAPI(); }
	
};
}