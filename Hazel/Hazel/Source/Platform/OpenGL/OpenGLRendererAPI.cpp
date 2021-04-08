#include "Hzpch.h"
#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace Hazel {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& Color)
	{
		glClearColor(Color.r, Color.g, Color.b, Color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray)
	{
		glDrawElements(GL_TRIANGLES, InVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}