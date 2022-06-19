#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Hazel {

class RendererAPI
{
public:

	enum class ERendererAPI
	{
		None = 0, OpenGL = 1
	};

public:

	virtual void Init() = 0;
	virtual void SetClearColor(const glm::vec4& Color) = 0;
	virtual void Clear() = 0;

	virtual void DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray) = 0;

	inline static ERendererAPI GetAPI() { return Renderer_API; }

private:

	static ERendererAPI Renderer_API;
};

}