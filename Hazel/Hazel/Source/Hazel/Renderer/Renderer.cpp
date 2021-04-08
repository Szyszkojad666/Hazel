#include "Hzpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Hazel {



	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& InVertexArray)
	{
		InVertexArray->Bind();
		RenderCommand::DrawIndexed(InVertexArray);
	}

}